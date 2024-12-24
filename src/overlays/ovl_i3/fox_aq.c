/*
 * File: fox_aq.c
 * System: Aquas
 * Description: Level: Aquas
 */

#include "global.h"
#include "assets/ast_blue_marine.h"
#include "assets/ast_aquas.h"
// #include "prevent_bss_reordering2.h"

const char D_i3_801C1A30[] = "プレイヤーのすべてをクリア \n"; // Clear of all players
const char D_i3_801C1A50[] = "i %d\n";

typedef enum AqBacoonLimbs {
    /*  0 */ AQ_LIMB_0,
    /*  1 */ AQ_LIMB_1,
    /*  2 */ AQ_LIMB_2,
    /*  3 */ AQ_LIMB_3,
    /*  4 */ AQ_LIMB_4,
    /*  5 */ AQ_LIMB_5,
    /*  6 */ AQ_LIMB_6,
    /*  7 */ AQ_LIMB_7,
    /*  8 */ AQ_LIMB_8,
    /*  9 */ AQ_LIMB_9,
    /* 10 */ AQ_LIMB_10,
    /* 11 */ AQ_LIMB_11,
    /* 12 */ AQ_LIMB_12,
    /* 13 */ AQ_LIMB_13,
    /* 14 */ AQ_LIMB_14,
    /* 15 */ AQ_LIMB_15,
    /* 16 */ AQ_LIMB_16,
    /* 17 */ AQ_LIMB_17,
    /* 18 */ AQ_LIMB_18,
    /* 19 */ AQ_LIMB_19,
    /* 20 */ AQ_LIMB_20,
    /* 21 */ AQ_LIMB_21,
    /* 22 */ AQ_LIMB_22,
    /* 23 */ AQ_LIMB_23,
    /* 24 */ AQ_LIMB_24,
    /* 25 */ AQ_LIMB_25,
    /* 26 */ AQ_LIMB_26,
    /* 27 */ AQ_LIMB_27,
    /* 28 */ AQ_LIMB_MAX,
} AqBacoonLimbs;

typedef enum AqBacoonswork {
    /*  0 */ AQ_SWK_0,
    /*  1 */ AQ_SWK_1,
    /*  2 */ AQ_SWK_2,
    /*  3 */ AQ_SWK_3,
    /*  4 */ AQ_SWK_4,
    /*  5 */ AQ_SWK_5,
    /*  6 */ AQ_SWK_6,
    /*  7 */ AQ_SWK_7,
    /*  8 */ AQ_SWK_8,
    /*  9 */ AQ_SWK_9,
    /* 10 */ AQ_SWK_10,
    /* 11 */ AQ_SWK_11,
    /* 12 */ AQ_SWK_12,
    /* 13 */ AQ_SWK_13,
    /* 14 */ AQ_SWK_14,
    /* 15 */ AQ_SWK_15,
    /* 16 */ AQ_SWK_16,
    /* 17 */ AQ_SWK_17,
    /* 18 */ AQ_SWK_18,
    /* 19 */ AQ_SWK_19,
    /* 20 */ AQ_SWK_20,
    /* 21 */ AQ_SWK_21,
    /* 22 */ AQ_SWK_22,
    /* 23 */ AQ_SWK_23,
    /* 24 */ AQ_SWK_24,
    /* 25 */ AQ_SWK_25,
    /* 26 */ AQ_SWK_26,
    /* 27 */ AQ_SWK_27,
    /* 28 */ AQ_SWK_28,
    /* 29 */ AQ_SWK_29,
    /* 30 */ AQ_SWK_30,
    /* 31 */ AQ_SWK_31,
    /* 32 */ AQ_SWK_32,
    /* 33 */ AQ_SWK_33,
    /* 34 */ AQ_SWK_34,
    /* 35 */ AQ_SWK_35,
    /* 36 */ AQ_SWK_36,
    /* 37 */ AQ_SWK_37,
    /* 38 */ AQ_SWK_38,
    /* 39 */ AQ_SWK_39,
    /* 40 */ AQ_SWK_MAX,
} AqBacoonswork;

typedef enum AqBacoonfwork {
    /*  0 */ AQ_FWK_0,
    /*  1 */ AQ_FWK_1,
    /*  2 */ AQ_FWK_2,
    /*  3 */ AQ_FWK_3,
    /*  4 */ AQ_FWK_4,
    /*  5 */ AQ_FWK_5,
    /*  6 */ AQ_FWK_6,
    /*  7 */ AQ_FWK_7,
    /*  8 */ AQ_FWK_8,
    /*  9 */ AQ_FWK_9,
    /* 10 */ AQ_FWK_10,
    /* 11 */ AQ_FWK_11,
    /* 12 */ AQ_FWK_12,
    /* 13 */ AQ_FWK_13,
    /* 14 */ AQ_FWK_14,
    /* 15 */ AQ_FWK_15,
    /* 16 */ AQ_FWK_16,
    /* 17 */ AQ_FWK_17,
    /* 18 */ AQ_FWK_18,
    /* 19 */ AQ_FWK_19,
    /* 20 */ AQ_FWK_20,
    /* 21 */ AQ_FWK_21,
    /* 22 */ AQ_FWK_22,
    /* 23 */ AQ_FWK_23,
    /* 24 */ AQ_FWK_24,
    /* 25 */ AQ_FWK_25,
    /* 26 */ AQ_FWK_26,
    /* 27 */ AQ_FWK_27,
    /* 28 */ AQ_FWK_28,
    /* 29 */ AQ_FWK_29,
    /* 30 */ AQ_FWK_30,
    /* 31 */ AQ_FWK_31,
    /* 32 */ AQ_FWK_32,
    /* 33 */ AQ_FWK_33,
    /* 34 */ AQ_FWK_34,
    /* 35 */ AQ_FWK_35,
    /* 36 */ AQ_FWK_36,
    /* 37 */ AQ_FWK_37,
    /* 38 */ AQ_FWK_38,
    /* 39 */ AQ_FWK_39,
    /* 40 */ AQ_FWK_40,
    /* 41 */ AQ_FWK_41,
    /* 42 */ AQ_FWK_42,
    /* 43 */ AQ_FWK_43,
    /* 44 */ AQ_FWK_44,
    /* 45 */ AQ_FWK_45,
    /* 46 */ AQ_FWK_46,
    /* 47 */ AQ_FWK_47,
    /* 48 */ AQ_FWK_48,
    /* 49 */ AQ_FWK_49,
    /* 50 */ AQ_FWK_MAX,
} AqBacoonfwork;

typedef enum AqBacoonvwork {
    /*  0 */ AQ_VWK_0,
    /*  1 */ AQ_VWK_1,
    /*  2 */ AQ_VWK_2,
    /*  3 */ AQ_VWK_3,
    /*  4 */ AQ_VWK_4,
    /*  5 */ AQ_VWK_5,
    /*  6 */ AQ_VWK_6,
    /*  7 */ AQ_VWK_7,
    /*  8 */ AQ_VWK_8,
    /*  9 */ AQ_VWK_9,
    /* 10 */ AQ_VWK_10,
    /* 11 */ AQ_VWK_11,
    /* 12 */ AQ_VWK_12,
    /* 13 */ AQ_VWK_13,
    /* 14 */ AQ_VWK_14,
    /* 15 */ AQ_VWK_15,
    /* 16 */ AQ_VWK_16,
    /* 17 */ AQ_VWK_17,
    /* 18 */ AQ_VWK_18,
    /* 19 */ AQ_VWK_19,
    /* 20 */ AQ_VWK_20,
    /* 21 */ AQ_VWK_21,
    /* 22 */ AQ_VWK_22,
    /* 23 */ AQ_VWK_23,
    /* 24 */ AQ_VWK_24,
    /* 25 */ AQ_VWK_25,
    /* 26 */ AQ_VWK_26,
    /* 27 */ AQ_VWK_27,
    /* 28 */ AQ_VWK_28,
    /* 29 */ AQ_VWK_29,
    /* 30 */ AQ_VWK_30,
    /* 31 */ AQ_VWK_31,
    /* 32 */ AQ_VWK_32,
    /* 33 */ AQ_VWK_33,
    /* 34 */ AQ_VWK_34,
    /* 35 */ AQ_VWK_35,
    /* 36 */ AQ_VWK_36,
    /* 37 */ AQ_VWK_37,
    /* 38 */ AQ_VWK_38,
    /* 39 */ AQ_VWK_39,
    /* 40 */ AQ_VWK_40,
    /* 41 */ AQ_VWK_41,
    /* 42 */ AQ_VWK_42,
    /* 43 */ AQ_VWK_43,
    /* 44 */ AQ_VWK_44,
    /* 45 */ AQ_VWK_45,
    /* 46 */ AQ_VWK_46,
    /* 47 */ AQ_VWK_47,
    /* 48 */ AQ_VWK_48,
    /* 49 */ AQ_VWK_49,
    /* 50 */ AQ_VWK_MAX,
} AqBacoonvwork;

f32 D_AQ_801C4188;
s32 D_i3_801C4190[10];
f32 D_i3_801C41B8[30];
s32 sAqBacoonlimbTimers[AQ_LIMB_MAX];
s32 D_i3_801C42A0[25];
f32 D_i3_801C4308[82];
s32 D_i3_801C4450;
s32 D_i3_801C4454;
f32 D_i3_801C4458;
f32 D_i3_801C445C;

#include "prevent_bss_reordering.h"

f32 D_i3_801BFB60 = 0.0f;
s32 D_i3_801BFB64[11] = {
    0, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3,
};
u8 D_i3_801BFB90[12] = {
    0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
};
Gfx* D_i3_801BFB9C[3] = { D_AQ_6015FF0, D_AQ_6022110, D_AQ_6015DD0 };
f32 D_i3_801BFBA8[2] = { 40.0f, -40.0f };
f32 D_i3_801BFBB0[3] = { 20.0f, 10.0f, 15.0f };
f32 D_i3_801BFBBC[3] = { 8.0f, 27.0f, 42.0f };
f32 D_i3_801BFBC8[3] = { 15.0f, 6.0f, 7.0f };
f32 D_i3_801BFBD4[3] = { 358.0f, 12.0f, 352.0f };
f32 D_i3_801BFBE0[12] = {
    1.3f, 0.1f, 1.0f, 777.0f, 0.7f, 0.5f, 5.0f, 777.0f, 1.0f, 0.2f, 2.0f, 777.0f,
};
f32 D_i3_801BFC10[12] = {
    0.6f, 0.1f, 1.0f, 777.0f, 1.5f, 0.5f, 5.0f, 777.0f, 1.0f, 0.2f, 2.0f, 777.0f,
};
f32 D_i3_801BFC40[12] = {
    1.3f, 0.1f, 1.0f, 777.0f, 0.7f, 0.5f, 5.0f, 777.0f, 1.0f, 0.2f, 2.0f, 777.0f,
};
s32 D_i3_801BFC70[3] = { 18, 22, 45 };
f32 D_i3_801BFC7C[3] = { 20.0f, 10.0f, 0.0f };
f32 D_i3_801BFC88[3] = { 10.0f, 320.0f, 30.0f };
Vec3f D_i3_801BFC94[6 * 4] = {
    { 1.0f, 1.0f, 1.0f }, { 0.9f, 0.9f, 0.9f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f },
    { 0.9f, 0.9f, 0.9f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.9f, 0.9f, 0.9f },
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.9f, 1.0f, 0.9f }, { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.9f, 1.0f, 0.9f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.8f, 0.9f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f },
};
s32 D_i3_801BFDB4[6 * 4] = {
    1, 5, 15, 100000, 1, 5, 15, 100000, 1, 5, 15, 100000, 1, 10, 20, 100000, 1, 10, 20, 100000, 1, 10, 20, 100000,
};
s32 D_i3_801BFE14 = 0;
Vec3f D_i3_801BFE18[6 * 4] = {
    { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f },
    { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f },
    { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.2f, 0.2f, 0.2f }, { 0.3f, 0.3f, 0.3f }, { 0.2f, 0.2f, 0.2f },
    { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f },
    { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f }, { 0.2f, 0.2f, 0.2f },
};
Vec3f D_i3_801BFF38[6 * 4] = {
    { 1.0f, 1.0f, 1.0f }, { 5.0f, 5.0f, 5.0f },    { 10.0f, 10.0f, 10.0f }, { 5.0f, 5.0f, 5.0f }, { 1.0f, 1.0f, 1.0f },
    { 5.0f, 5.0f, 5.0f }, { 10.0f, 10.0f, 10.0f }, { 5.0f, 5.0f, 5.0f },    { 1.0f, 1.0f, 1.0f }, { 3.0f, 3.0f, 3.0f },
    { 2.0f, 2.0f, 2.0f }, { 1.0f, 1.0f, 1.0f },    { 1.0f, 1.0f, 1.0f },    { 3.0f, 1.0f, 3.0f }, { 2.0f, 1.0f, 2.0f },
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f },    { 3.0f, 1.0f, 3.0f },    { 2.0f, 1.0f, 2.0f }, { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 4.0f, 3.0f },    { 1.0f, 3.0f, 2.0f },    { 1.0f, 1.0f, 1.0f },
};
f32 D_i3_801C0058 = 191.0f;
f32 D_i3_801C005C = 63.0f;
f32 D_i3_801C0060[7 * 2] = {
    50.0f, 8.0f, 50.0f, 8.0f, 10.0f, 1.0f, 20.0f, 2.0f, 20.0f, 2.0f, 20.0f, 2.0f, 50.0f, 2.0f,
};
Vec3f D_i3_801C0098[2] = {
    { 370.0f, -53.0f, 1085.0f },
    { -370.0f, -53.0f, 1085.0f },
};
f32 D_i3_801C00B0[3][4] = {
    { 1.0f, 1.2f, 0.8f, 1.0f },
    { 1.0f, 1.2f, 0.9f, 1.0f },
    { 1.0f, 0.7f, 1.4f, 1.0f },
};
s32 D_i3_801C00E0[4] = { 1, 5, 8, 40 };
f32 D_i3_801C00F0[3][4] = {
    { 0.3f, 0.3f, 0.3f, 0.3f },
    { 0.3f, 0.3f, 0.3f, 0.3f },
    { 0.5f, 0.5f, 0.5f, 0.5f },
};
f32 D_i3_801C0120[3][4] = {
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 2.0f, 2.0f, 2.0f, 2.0f },
};
f32 D_i3_801C0150[4][4] = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, -25.5f, 0.0f, 0.0f },
    { -25.5f, 25.5f, -25.5f, 0.0f },
    { 25.5f, 0.0f, 25.5f, 0.0f },
};
f32 D_i3_801C0190[5] = {
    0.0f, -30.0f, 30.0f, -30.0f, 30.0f,
};

PosRot* D_i3_801C27C0;
PosRot D_i3_801C27C8[4 * 50];
Vtx D_i3_801C3A88[2][2][28];

void Aquas_801A8E30(void) {
    s32 i;
    f32 spA8[17];
    f32 sp64[17];
    s32 j;
    Vtx* sp5C = LOAD_ASSET(D_AQ_6031D90);
    Vtx* sp58 = LOAD_ASSET(D_AQ_6011A78);

    for (i = 0; i < 17; i++) {
        if ((i == 0) || (i == 16)) {
            spA8[i] = 0.0f;
            sp64[i] = 0.0f;
        } else {
            spA8[i] = RAND_FLOAT_CENTERED(70.0f);
            sp64[i] = RAND_FLOAT_CENTERED(70.0f);
        }
    }

    for (i = 0; i < 34; i++) {
        j = (sp5C[i].v.ob[2] + 200) / 25;
        sp58[i].v.ob[0] = sp5C[i].v.ob[0] + spA8[j];
        sp58[i].v.ob[1] = sp5C[i].v.ob[1] + sp64[j];
    }
}

void Aquas_801A92EC(AqJellyfish* this, f32 xUnk, f32 yUnk, f32 zUnk, s32 index, s32 mode) {
    gTexturedLines[index].mode = mode;
    gTexturedLines[index].xyScale = 10.0f;
    gTexturedLines[index].posAA.x = this->obj.pos.x;
    gTexturedLines[index].posAA.y = this->obj.pos.y;
    gTexturedLines[index].posAA.z = this->obj.pos.z;
    gTexturedLines[index].posBB.x = xUnk;
    gTexturedLines[index].posBB.y = yUnk;
    gTexturedLines[index].posBB.z = zUnk;
    gTexturedLines[index].prim.r = gTexturedLines[index].prim.g = gTexturedLines[index].prim.b =
        gTexturedLines[index].prim.a = 255;
    gTexturedLines[index].timer = 3;
}

void Aquas_SetupDebris(ActorDebris* this, Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state, f32 scale,
                       s32 timerBC, s32 unk48) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_DEBRIS;
    this->state = state;
    this->scale = scale;
    this->work_048 = unk48;
    this->obj.pos = *pos;
    this->obj.rot = *rot;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->timer_0BC = timerBC;
    this->gravity = 0.5f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Aquas_SpawnDebris(Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state, f32 scale, s32 timerBC,
                       s32 unk48) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Aquas_SetupDebris(&gActors[i], pos, rot, xVel, yVel, zVel, state, scale, timerBC, unk48);
            break;
        }
    }
}

void Aquas_SpawnItem(Vec3f* pos, ObjectId objId) {
    s32 i;
    Item* item;

    for (i = 0, item = &gItems[0]; i < ARRAY_COUNT(gItems); i++, item++) {
        if (item->obj.status == OBJ_FREE) {
            Item_Initialize(item);
            item->obj.status = OBJ_INIT;
            item->obj.id = objId;
            item->obj.pos.x = pos->x;
            item->obj.pos.y = pos->y;
            item->obj.pos.z = pos->z;
            item->timer_4A = 2;
            Object_SetInfo(&item->info, item->obj.id);
            break;
        }
    }
}

f32 Aquas_801A958C(s32 arg0, f32 arg1) {
    f32 var_fv1 = arg0 / 2.0f;

    var_fv1 = MIN(arg1, var_fv1);

    return var_fv1;
}

void Aquas_801A95C8(void) {
    Math_SmoothStepToF(&gPlayer[0].cam.eye.x, gCsCamEyeX, 0.1f, 50.0f, 0.0001f);
    Math_SmoothStepToF(&gPlayer[0].cam.eye.y, gCsCamEyeY, 0.1f, 50.0f, 0.0001f);
    Math_SmoothStepToF(&gPlayer[0].cam.eye.z, gCsCamEyeZ, 0.1f, 50.0f, 0.0001f);

    Math_SmoothStepToF(&gPlayer[0].cam.at.x, gCsCamAtX, 0.1f, 50.0f, 0.0001f);
    Math_SmoothStepToF(&gPlayer[0].cam.at.y, gCsCamAtY, 0.1f, 50.0f, 0.0001f);
    Math_SmoothStepToF(&gPlayer[0].cam.at.z, gCsCamAtZ, 0.1f, 50.0f, 0.0001f);
}

void Aquas_801A96DC(AqPearl* this) {
    this->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    this->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);
}

void Aquas_801A9728(AqSculpin* this, f32 radius, f32 scale, s32 spread) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < 36; i += spread) {
        x = SIN_DEG(i * 10.0f) * radius;
        z = COS_DEG(i * 10.0f) * radius;
        y = gGroundHeight + 30.0f;
        Effect_Effect364_Spawn(this->obj.pos.x + x, y, this->obj.pos.z + z, scale);
    }
}

void Aquas_InitLevel(void) {
    s32 i;
    f32* var_v0;
    f32* var_v0_4;
    s32* var_a0;
    s32* var_v0_2;
    s32* var_v0_3;

    gTeamShields[TEAM_ID_FALCO] = gTeamShields[TEAM_ID_SLIPPY] = gTeamShields[TEAM_ID_PEPPY] = 255;

    for (i = 0; i < ARRAY_COUNT(D_i3_801C4190); i++) {
        D_i3_801C4190[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_i3_801C41B8); i++) {
        D_i3_801C41B8[i] = 0.0f;
    }

    for (i = 0; i < AQ_LIMB_MAX; i++) {
        sAqBacoonlimbTimers[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_i3_801C42A0); i++) {
        D_i3_801C42A0[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_i3_801C4308); i++) {
        D_i3_801C4308[i] = 0;
    }

    D_i3_801C4458 = D_i3_801C445C = 0.0f;
    D_i3_801C4450 = D_i3_801C4454 = 0;
    D_i3_801C41B8[12] = 40.0f;
    D_i3_801C41B8[13] = 100.0f;
    D_i3_801C41B8[14] = 120.0f;
    D_i3_801C41B8[15] = 20.0f;
    D_i3_801C41B8[16] = 30.0f;
    D_i3_801C41B8[17] = 50.0f;

    if (gSavedObjectLoadIndex != 0) {
        D_i3_801C41B8[12] = 0.0f;
        D_i3_801C41B8[13] = 3.0f;
        D_i3_801C41B8[14] = 5.0f;
        D_i3_801C41B8[15] = 0.0f;
        D_i3_801C41B8[16] = 0.0f;
        D_i3_801C41B8[17] = 0.0f;
    }

    D_i3_801C4190[5] = 0;
    D_i3_801C41B8[25] = D_bg_8015F970;
    D_i3_801C41B8[26] = 128.0f;
}

void Aquas_801A99D4(Player* player) {
    s32 sp24 = fabsf(player->trueZpos / 1000.0f);

    Math_SmoothStepToF(&D_bg_8015F970, D_i3_801C41B8[25], 1.0f, 10.0f, 0.00001f);
    Math_SmoothStepToF(&D_AQ_801C4188, D_i3_801C41B8[26], 0.1f, 10.0f, 0.00001f);

    if ((D_i3_801C4190[8] < sp24) && (D_i3_801C41B8[25] < 4600.0f)) {
        D_i3_801C4190[8] = sp24;
        D_i3_801C41B8[25] += 150.0f;
        D_i3_801C41B8[26] = D_AQ_801C4188 - 6.0f;

        if (D_i3_801C41B8[26] < 0.0f) {
            D_i3_801C41B8[26] = 0.0f;
        }
        if (D_i3_801C41B8[25] > 4600.0f) {
            D_i3_801C41B8[25] = 4600.0f;
        }

        D_i3_801C41B8[12] -= 2.0f;
        if (D_i3_801C41B8[12] < 0.0f) {
            D_i3_801C41B8[12] = 0.0f;
        }

        D_i3_801C41B8[13] -= 6.0f;
        if (D_i3_801C41B8[13] < 3.0f) {
            D_i3_801C41B8[13] = 3.0f;
        }

        D_i3_801C41B8[14] -= 6.0f;
        if (D_i3_801C41B8[14] < 5.0f) {
            D_i3_801C41B8[14] = 5.0f;
        }

        D_i3_801C41B8[15] -= 1.0f;
        if (D_i3_801C41B8[15] < 0.0f) {
            D_i3_801C41B8[15] = 0.0f;
        }

        D_i3_801C41B8[16] -= 1.5f;
        if (D_i3_801C41B8[16] < 0.0f) {
            D_i3_801C41B8[16] = 0.0f;
        }

        D_i3_801C41B8[17] -= 2.5f;
        if (D_i3_801C41B8[17] < 0.0f) {
            D_i3_801C41B8[17] = 0.0f;
        }

        gLight1R = D_i3_801C41B8[12];
        gLight1G = D_i3_801C41B8[13];
        gLight1B = D_i3_801C41B8[14];

        gAmbientR = D_i3_801C41B8[15];
        gAmbientG = D_i3_801C41B8[16];
        gAmbientB = D_i3_801C41B8[17];
    }
}

void Aquas_801A9C98(Player* player) {
    Actor* actor;
    s32 i;
    s32 var_v0;

    if ((D_i3_801C4190[0] != 777) && (D_i3_801C4190[0] > 0)) {
        i = D_i3_801C4190[0] - 1;
        actor = &gActors[i];

        if ((actor->obj.status != OBJ_ACTIVE) || ((player->trueZpos - 300.0f) <= actor->obj.pos.z) ||
            (actor->obj.pos.z <= (player->trueZpos - 7000.0f)) || (actor->obj.id != D_i3_801C4190[1]) ||
            (actor->health == 0)) {
            D_i3_801C4190[0] = D_i3_801C4190[3] = D_i3_801C4190[5] = D_i3_801C4190[1] = 0;
        } else {
            var_v0 = 1;
            if (actor->info.hitbox[1] == HITBOX_ROTATED) {
                var_v0 = 5;
            }
            D_i3_801C41B8[2] = actor->obj.pos.z + actor->info.hitbox[var_v0 + 0] + actor->info.hitbox[var_v0 + 1];
            D_i3_801C41B8[1] = actor->obj.pos.y + actor->info.hitbox[var_v0 + 2];
            D_i3_801C41B8[0] = actor->obj.pos.x + actor->info.hitbox[var_v0 + 4];
        }
    }
}

void Aquas_801A9DE4(Player* player) {
    s32 i;

    if (D_i3_801C4190[0] == 777) {
        if ((gBosses[0].obj.status != OBJ_ACTIVE) || (gBosses[0].health == 0) || (fabsf(D_i3_801C4308[10]) <= 6.0f) ||
            ((D_i3_801C4190[4] == 121) && (gBosses[0].swork[AQ_SWK_12] == 0))) {
            D_i3_801C4190[0] = D_i3_801C4190[4] = D_i3_801C4190[3] = D_i3_801C4190[5] = D_i3_801C4190[1] = 0;
        } else {
            i = D_i3_801C4190[4] - 2;

            D_i3_801C41B8[2] = gBosses[0].obj.pos.z + gBosses[0].info.hitbox[i + 0] + gBosses[0].info.hitbox[i + 1];
            D_i3_801C41B8[1] = gBosses[0].obj.pos.y + gBosses[0].info.hitbox[i + 2];
            D_i3_801C41B8[0] = gBosses[0].obj.pos.x + gBosses[0].info.hitbox[i + 4];
        }
    }
}

// Loop looks really fake. optimized out index?
void Aquas_801A9ED0(Player* player) {
    s32 j;
    s32 i;
    s32 sp8C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    Vec3f sp70;
    Vec3f sp64;
    f32* tempy;

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);

    sp70.x = 0.0f;
    sp70.y = 0.0f;
    sp70.z = -1200.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp64);

    if (D_i3_801C4190[3] == 0) {
        sp8C = D_i3_801C4190[4];

        if ((fabsf(D_i3_801C4308[10]) >= 6.0f) && (gBosses[0].state >= 10) && (gBosses[0].obj.status == OBJ_ACTIVE) &&
            (gBosses[0].health != 0)) {
            for (j = 119, i = 121; j < 199; j += 10, i += 10) {
                if ((j == 119) || (j == 129) || (j == 139) || (j == 169)) {
                    tempy = &gBosses[0].info.hitbox[i];

                    temp_fv0 = gBosses[0].obj.pos.y + tempy[0] + tempy[1] + 200.0f;
                    temp_fa0 = gBosses[0].obj.pos.y + tempy[0] - tempy[1] - 200.0f;
                    temp_fv1 = gBosses[0].obj.pos.x + tempy[2] + tempy[3] + 200.0f;
                    temp_fa1 = gBosses[0].obj.pos.x + tempy[2] - tempy[3] - 200.0f;

                    if ((gBosses[0].state >= 10) && ((player->pos.y + sp64.y) <= temp_fv0) &&
                        (temp_fa0 <= (player->pos.y + sp64.y)) && ((player->pos.x + sp64.x) <= temp_fv1) &&
                        (temp_fa1 <= (player->pos.x + sp64.x))) {
                        if (D_i3_801C41B8[11] >=
                            fabsf(player->trueZpos - gBosses[0].obj.pos.z - gBosses[0].info.hitbox[j])) {
                            D_i3_801C41B8[11] =
                                fabsf(player->trueZpos - gBosses[0].obj.pos.z - gBosses[0].info.hitbox[j]);
                            D_i3_801C4190[0] = 777;
                            D_i3_801C4190[4] = i;
                            D_i3_801C4190[1] = OBJ_BOSS_AQ_BACOON;
                        }

                        if (((j == 129) && (gBosses[0].swork[AQ_SWK_8] == 0)) ||
                            ((j == 139) && (gBosses[0].swork[AQ_SWK_9] == 0)) ||
                            ((j == 119) && (gBosses[0].swork[AQ_SWK_12] == 0))) {
                            D_i3_801C4190[0] = D_i3_801C4190[4] = D_i3_801C4190[3] = D_i3_801C4190[5] =
                                D_i3_801C4190[1] = 0;
                        }
                    }
                }
            }

            if ((sp8C != D_i3_801C4190[4]) && (D_i3_801C41B8[5] == 3.0f)) {
                AUDIO_PLAY_SFX(NA_SE_MAR_LOCKON, gDefaultSfxSource, 4);
                D_i3_801C41B8[5] = 20.0f;
            }
        }
    }
    Aquas_801A9DE4(player);
}

// Blue Marine Reticle
void Aquas_801AA20C(void) {
    s32 i;
    f32 x;
    f32 y;

    if (gPlayer[0].draw) {
        Matrix_Push(&gGfxMatrix);
        Math_SmoothStepToF(&D_i3_801C41B8[5], 3.0f, 1.0f, 4.0f, 0.0001f);
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);

        if (D_i3_801C4190[3] == 0) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            x = -10.0f;
            y = 10.0f;

            if (D_i3_801C4190[0] != 0) {
                x = y = 0.0f;
            }

            Matrix_Translate(gGfxMatrix, D_i3_801C41B8[0] + x, D_i3_801C41B8[1] + y,
                             D_i3_801C41B8[2] + gPlayer[0].zPath, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_i3_801C41B8[5], D_i3_801C41B8[5], D_i3_801C41B8[5], MTXF_APPLY);

            for (i = 0; i < 4; i++) {
                Matrix_RotateZ(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_blue_marine_3000470);
                Matrix_Pop(&gGfxMatrix);
            }
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            Matrix_Translate(gGfxMatrix, D_i3_801C41B8[0], D_i3_801C41B8[1], D_i3_801C41B8[2] + gPlayer[0].zPath,
                             MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_i3_801C41B8[5], D_i3_801C41B8[5], D_i3_801C41B8[5], MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_blue_marine_3000130);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Aquas_801AA4BC(Player* player) {
    f32 rotBankTarget;
    f32 rotBankScale;

    if (player->unk_230 == 0) {
        rotBankTarget = 0.0f;
        rotBankScale = 0.1f;
        if ((gInputHold->button & Z_TRIG) && !(gInputHold->button & R_TRIG)) {
            rotBankTarget = 90.0f;
            rotBankScale = 0.2f;
            if (player->zRotBank < 70.0f) {
                Math_SmoothStepToF(&player->arwing.upperRightFlapYrot, -70.0f, 0.3f, 100.0f, 0);
                Math_SmoothStepToF(&player->arwing.bottomRightFlapYrot, -70.0f, 0.3f, 100.0f, 0);
                Math_SmoothStepToF(&player->arwing.upperLeftFlapYrot, 70.0f, 0.3f, 100.0f, 0);
                Math_SmoothStepToF(&player->arwing.bottomLeftFlapYrot, 70.0f, 0.3f, 100.0f, 0);
            }
        }

        if ((gInputHold->button & R_TRIG) && !(gInputHold->button & Z_TRIG)) {
            rotBankTarget = -90.0f;
            rotBankScale = 0.2f;
            if (player->zRotBank > -70.0f) {
                Math_SmoothStepToF(&player->arwing.upperRightFlapYrot, 70.0f, 0.3f, 100.0f, 0);
                Math_SmoothStepToF(&player->arwing.bottomRightFlapYrot, 70.0f, 0.3f, 100.0f, 0);
                Math_SmoothStepToF(&player->arwing.upperLeftFlapYrot, -70.0f, 0.3f, 100.0f, 0);
                Math_SmoothStepToF(&player->arwing.bottomLeftFlapYrot, -70.0f, 0.3f, 100.0f, 0);
            }
        }

        Math_SmoothStepToF(&player->zRotBank, rotBankTarget, rotBankScale, 10.0f, 0);
    }

    if ((gInputPress->button & Z_TRIG) && (player->unk_230 == 0)) {
        player->sfx.bank = 1;
        if (player->rollInputTimerL != 0) {
            player->rollState = 1;
            player->rollTimer = 10;
            player->rollRate = player->baseRollRate = 30;
            player->sfx.roll = 1;
        } else {
            player->rollInputTimerL = 10;
        }
    }

    if ((gInputPress->button & R_TRIG) && (player->unk_230 == 0)) {
        player->sfx.bank = 1;
        if (player->rollInputTimerR != 0) {
            player->rollState = 1;
            player->rollTimer = 10;
            player->rollRate = player->baseRollRate = -30;
            player->sfx.roll = 1;
        } else {
            player->rollInputTimerR = 10;
        }
    }

    Math_SmoothStepToF(&player->unk_150, 1.0f, 0.05f, 10.0f, 0.0001f);

    player->zRotBarrelRoll = Math_ModF(player->zRotBarrelRoll, 360.0f);

    if (player->barrelRollAlpha > 0) {
        player->barrelRollAlpha -= 30;
        if (player->barrelRollAlpha <= 0) {
            player->barrelRollAlpha = 0;
        }
    }

    if (player->rollState == 0) {
        Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 10.0f, 0.00001f);
    }

    if (player->rollInputTimerL != 0) {
        player->rollInputTimerL--;
    }
    if (player->rollInputTimerR != 0) {
        player->rollInputTimerR--;
    }

    if (player->timer_214 != 0) {
        player->timer_214--;
    }
    if (player->timer_218 != 0) {
        player->timer_218--;
    }
    if (player->rollTimer != 0) {
        player->rollTimer--;
    }

    if (player->rollState != 0) {
        player->rollInputTimerL = player->rollInputTimerR = 0;
        player->unk_150 = 1.5f;
        player->zRotBarrelRoll += player->rollRate;

        if (player->rollTimer == 0) {
            if (player->rollRate > 0) {
                player->rollRate -= 5;
            }
            if (player->rollRate < 0) {
                player->rollRate += 5;
            }
            if (player->rollRate == 0) {
                player->rollState = 0;
            }
        } else {
            if (player->barrelRollAlpha < 180) {
                player->barrelRollAlpha += 60;
                if (player->barrelRollAlpha > 180) {
                    player->barrelRollAlpha = 180;
                }
            }
        }
    }
}

void Aquas_UpdateCamera(Player* player) {
    f32 stickX = +gInputPress->stick_x;
    f32 stickY = -gInputPress->stick_y;
    f32 zRot;

    if (player->state != PLAYERSTATE_ACTIVE) {
        stickX = stickY = 0.0f;
    }

    Math_SmoothStepToF(&player->unk_030, stickX, 0.05f, 1.0f, 0.05f);

    if (player->pos.y < (gGroundHeight + 50.0f)) {
        Math_SmoothStepToF(&player->unk_02C, stickY * 0.3f, 0.05f, 1.0f, 0.05f);
    } else {
        Math_SmoothStepToF(&player->unk_02C, stickY, 0.05f, 2.0f, 0.05f);
    }

    gCsCamEyeX = (player->pos.x - player->xPath) * (600.0f / player->pathWidth);
    gCsCamEyeX -= player->unk_030 * 1.5f;
    gCsCamEyeX += player->xPath + D_i3_801C41B8[9];

    gCsCamEyeY = player->pos.y * (740.0f / player->pathHeight);
    gCsCamEyeY -= player->unk_02C - 50.0f;
    gCsCamEyeY += player->yPath;

    gCsCamAtX = (player->pos.x - player->xPath - D_i3_801C41B8[9]) * (600.0f / player->pathWidth);
    gCsCamAtX += player->xShake * -2.0f;
    gCsCamAtX -= player->unk_030 * 0.5f;
    gCsCamAtX += player->xPath;

    gCsCamAtY = (player->pos.y - player->yPath) * (750.0f / player->pathHeight);
    gCsCamAtY += player->xRock * 10.0f;
    gCsCamAtY -= player->unk_02C * -0.55f;
    gCsCamAtY += player->yPath + D_i3_801C41B8[10];

    if (gCsCamAtY < 20.0f) {
        gCsCamAtY = 20.0f;
    }

    gCsCamEyeZ = 240.0f;
    gCsCamAtZ = player->trueZpos + (gPathProgress - 1.0f);

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, player->unk_014, 1000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, player->unk_014, 1000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, 0.2f, 30.0f, 0.0f);

    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, player->unk_014, 1000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, player->unk_014, 1000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, player->unk_014, 1000.0f, 0);

    Math_SmoothStepToF(&player->unk_014, 1.0f, 1.0f, 0.05f, 0.0f);

    zRot = -player->rot.z;

    Math_SmoothStepToF(&player->camRoll, zRot * 0.3f, 0.1f, 1.5f, 0.0f);
}

void Aquas_BlueMarineMove(Player* player) {
    Vec3f sp8C;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    f32 stickX;
    f32 sp60;
    f32 stickY;
    f32 sp58;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1_2;
    s32 pad;

    Aquas_801AA4BC(player);
    Aquas_801A99D4(player);
    Aquas_801A8E30();

    stickX = -gInputPress->stick_x;
    stickY = +gInputPress->stick_y;

    gPlayerTurnStickMod = 0.68f;

    Math_SmoothStepToF(&player->unk_180, stickX * gPlayerTurnStickMod, 1.0f, 10.0f, 0.0001f);

    var_fa0 = fabsf(player->unk_180 * 0.5f);
    if (var_fa0 > 2.0f) {
        var_fa0 = 2.0f;
    }

    if (player->unk_180 < 0.0f) {
        if (D_i3_801C41B8[3] > player->unk_180) {
            D_i3_801C41B8[3] -= var_fa0;
        }
    } else {
        if (D_i3_801C41B8[3] < player->unk_180) {
            D_i3_801C41B8[3] += var_fa0;
        }
    }

    Math_SmoothStepToF(&D_i3_801C41B8[3], player->unk_180, 0.1f, 2.0f, 0.00001f);

    sp60 = D_i3_801C41B8[3];
    gPlayerTurnRate = 7.0f;

    if ((player->pos.x < (-player->pathWidth + player->xPath + 10.0f)) && (sp60 >= 20.0f)) {
        gPlayerTurnRate = 2.0f;
        Math_SmoothStepToF(&D_i3_801C41B8[9], 30.0f, 0.1f, 10.0f, 0.0001f);
    }
    if ((player->pos.x > (player->pathWidth + player->xPath - 10.0f)) && (sp60 <= -20.0f)) {
        gPlayerTurnRate = 2.0f;
        Math_SmoothStepToF(&D_i3_801C41B8[9], -30.0f, 0.1f, 10.0f, 0.0001f);
    }

    Math_SmoothStepToF(&player->rot.y, sp60, 0.3f, gPlayerTurnRate, 0.00001f);

    if (gPlayerTurnRate != 2.0f) {
        Math_SmoothStepToF(&D_i3_801C41B8[9], 0.0f, 0.1f, 20.0f, 0.0001f);
    }

    Math_SmoothStepToF(&player->unk_17C, stickY * gPlayerTurnStickMod, 1.0f, 7.0f, 0.0001f);

    var_fa1 = fabsf(player->unk_17C * 0.05f);
    if (var_fa1 > 2.0f) {
        var_fa1 = 2.0f;
    }

    if (player->unk_17C * -1.0f < 0.0f) {
        if (D_i3_801C41B8[4] > player->unk_17C) {
            D_i3_801C41B8[4] -= var_fa1;
        }
    } else {
        if (D_i3_801C41B8[4] < player->unk_17C) {
            D_i3_801C41B8[4] += var_fa1;
        }
    }

    Math_SmoothStepToF(&D_i3_801C41B8[4], player->unk_17C * -1.0f, 0.1f, 3.0f, 0.00001f);

    sp58 = D_i3_801C41B8[4] * 0.8f;
    gPlayerTurnRate = 10.0f;

    if (player->pos.y < (gGroundHeight + 50.0f)) {
        if (sp58 <= 0.0f) {
            sp58 = 0.0f;
            gPlayerTurnRate = 2.0f;
            if (D_i3_801C4190[7] == 0) {
                AUDIO_PLAY_SFX(NA_SE_MAR_BOUND, player->sfxSource, 0);
                D_i3_801C4190[7] = 1;
            }
        }
    } else {
        D_i3_801C4190[7] = 0;
    }

    if ((player->pathHeight - 50.0f) <= player->pos.y) {
        if (sp58 >= 0.0f) {
            Math_SmoothStepToF(&D_i3_801C41B8[10], 30.0f, 1.0f, 1.0f, 0.00001f);
        }
    } else {
        Math_SmoothStepToF(&D_i3_801C41B8[10], 0.0f, 0.1f, 1.0f, 0.00001f);
    }

    Math_SmoothStepToF(&player->rot.x, sp58, 1.0f, gPlayerTurnRate, 0.00001f);

    var_fv1_2 = 2.0f;
    if (stickX == 0.0f) {
        var_fv1_2 = 1.0f;
    }

    Math_SmoothStepToF(&player->rot.z, player->unk_180 * 0.7f, 0.08f, var_fv1_2, 0.0001f);

    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    sp8C.x = sp8C.y = 0.0f;
    sp8C.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp68);

    sp68.x *= 1.4f;
    sp68.y *= 1.4f;

    Matrix_RotateY(gCalcMatrix, player->yRot_114 * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->xRot_120 * M_DTOR, MTXF_APPLY);

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp80);

    sp8C.x = sp8C.y = 0.0f;
    sp8C.z = -player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp74);

    player->vel.x = (sp80.x + sp74.x) * player->unk_150;
    player->vel.y = (sp80.y + sp74.y) * player->unk_150;
    player->vel.z = sp80.z + sp74.z;

    player->pos.x += player->vel.x;

    if (player->pos.x > player->pathWidth + player->xPath) {
        player->pos.x = player->pathWidth + player->xPath;
        player->vel.x = 0.0f;
    }
    if (player->pos.x < player->xPath - player->pathWidth) {
        player->pos.x = player->xPath - player->pathWidth;
        player->vel.x = 0.0f;
    }

    player->pos.y += player->vel.y;

    if (player->pos.y > player->pathHeight) {
        player->pos.y = player->pathHeight;
        player->vel.y = 0.0f;
    }
    if (player->pos.y < player->pathFloor) {
        player->pos.y = player->pathFloor;
        player->vel.y = 0.0f;
    }

    if (player->pos.x > (player->xPath + (player->pathWidth - 100.0f))) {
        player->flags_228 = PFLAG_228_0;
    }
    if (player->pos.x < (player->xPath - (player->pathWidth - 100.0f))) {
        player->flags_228 = PFLAG_228_1;
    }
    if (player->pos.y > (player->yPath + (player->pathHeight - 100.0f))) {
        player->flags_228 = PFLAG_228_3;
    }
    if (player->pos.y <= (gGroundHeight + 100)) {
        player->flags_228 = PFLAG_228_2;
    }

    if (D_i3_801C4190[6] != 0) {
        player->baseSpeed = 20.0f;
        Math_SmoothStepToF(&D_i3_801BFB60, -40.0f, 0.01f, 0.1f, 0.0f);
        player->vel.z += D_i3_801BFB60;
        if (player->vel.z <= 0.0f) {
            player->vel.z = 0.0f;
        }
    }

    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->xRock = SIN_DEG(player->rockPhase * 0.7f) * 0.5f;
    player->bobPhase += 10.0f;
    player->rockPhase += 8.0f + D_i3_801C41B8[24];
    player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
    player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;

    if (player->pos.y < (gWaterLevel + 50.0f)) {
        Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114) * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);

        sp8C.x = sp8C.y = 0.0f;
        sp8C.z = 70.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp80);

        if (player->boostSpeed > 1.0f) {
            player->unk_178 -= 30.0f;
            Aquas_Effect366_Spawn(player->pos.x + RAND_FLOAT_CENTERED(10.0f) + sp80.x,
                                  player->pos.y + RAND_FLOAT_CENTERED(10.0f) + sp80.y,
                                  player->trueZpos + RAND_FLOAT_CENTERED(10.0f) + (sp80.z * -1.0f), 0.4f, 1);
        } else {
            player->unk_178 -= 10.0f;
            if ((gGameFrameCount % 8) == 0) {
                Aquas_Effect366_Spawn(player->pos.x + RAND_FLOAT_CENTERED(10.0f) + sp80.x,
                                      player->pos.y + RAND_FLOAT_CENTERED(10.0f) + sp80.y,
                                      player->trueZpos + RAND_FLOAT_CENTERED(20.0f) + sp80.z, 0.4f, 0);
            }
        }
    }
}

void Aquas_BlueMarineDown(Player* player) {
    func_effect_8007D0E0(player->pos.x, player->pos.y, player->trueZpos, 6.0f);
    Effect_Effect384_Spawn(player->pos.x, player->pos.y, player->trueZpos, 3.0f, 5);
    Effect386_Spawn1(player->pos.x, player->pos.y, player->trueZpos, 0.0f, 0.0f, 0.0f, 3.0f, 80);
    Cutscene_KillPlayer(player);
}

void Aquas_801ABA40(PlayerShot* shot) {
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    Vec3f sp60;
    Vec3f sp54;

    D_i3_801C41B8[21] = shot->obj.pos.x;
    D_i3_801C41B8[22] = shot->obj.pos.y;
    D_i3_801C41B8[23] = shot->obj.pos.z;

    if ((fabsf(shot->obj.pos.z - (gPlayer[0].cam.eye.z - gPathProgress)) > 10000.0f) ||
        (fabsf(shot->obj.pos.y - gPlayer[0].cam.eye.y) > 1500.0f) ||
        ((fabsf(shot->obj.pos.x - gPlayer[0].cam.eye.x) > 4000.0f) && (shot->unk_5C != 0))) {
        shot->timer = 0;
    }

    if (shot->obj.pos.y < gGroundHeight) {
        shot->obj.pos.y = gGroundHeight + 2.0f;
        PlayerShot_SpawnEffect344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f,
                                  2.0f, 0, 0);
        Effect_FireSmoke_Spawn(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 1.2f);
        D_i3_801C4190[5] = D_i3_801C4190[3] = 0;
        PlayerShot_Impact(shot);
    } else if (((shot->timer == 0) || (D_i3_801C4454 == 0)) && (shot->unk_5C != 0)) {
        Effect_FireSmoke_Spawn(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 1.2f);
        D_i3_801C41B8[21] = D_i3_801C41B8[22] = D_i3_801C41B8[23] = 0.0f;
        D_i3_801C4190[5] = D_i3_801C4190[3] = 0;
        PlayerShot_Impact(shot);
    } else {
        Math_SmoothStepToF(&shot->unk_48, 50.0f, 0.2f, 10.0f, 0.00001f);
        shot->obj.rot.z += shot->unk_48;
        if ((gGameFrameCount % 2) == 0) {
            PlayerShot_SpawnEffect351(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z);
        }

        PlayerShot_CollisionCheck(shot);

        shot->vec_2C.x = (shot->obj.pos.y * 0.01f) + 1.2f;
        shot->vec_2C.y = (shot->obj.pos.y * 0.003f) + 0.6f;
        shot->vec_2C.z = (shot->obj.pos.y * 0.001f) + 0.6f;

        shot->unk_58 = (shot->obj.pos.y * -0.24f) + 150.0f;
        if (shot->unk_58 < 30) {
            shot->unk_58 = 30;
        }

        switch (shot->unk_5C) {
            case 0:
                shot->timer = 50;
                shot->obj.rot.y = gPlayer[0].rot.y;
                shot->obj.rot.x = gPlayer[0].rot.x;
                shot->unk_5C++;
                break;

            case 1:
                if (D_i3_801C4190[3] != 0) {
                    sp7C = shot->obj.pos.x - D_i3_801C41B8[0];
                    sp78 = shot->obj.pos.y - D_i3_801C41B8[1];
                    sp74 = shot->obj.pos.z - D_i3_801C41B8[2];

                    sp6C = Math_RadToDeg(Math_Atan2F(sp7C, sp74));
                    sp70 = Math_RadToDeg(-Math_Atan2F(sp78, sqrtf(SQ(sp7C) + SQ(sp74))));

                    Math_SmoothStepToAngle(&shot->obj.rot.y, sp6C, 1.0f, 100.0f, 0.00001f);
                    Math_SmoothStepToAngle(&shot->obj.rot.x, sp70, 1.0f, 100.0f, 0.00001f);

                    if (shot->timer < 2) {
                        if (D_i3_801C4458 < -30.0f) {
                            D_i3_801C4458 += 20.0f;
                        }
                        if (D_i3_801C445C < 1.0f) {
                            D_i3_801C445C += 0.25f;
                        }
                        shot->timer = 10;
                    }
                }

                if (shot->unk_54 == 0) {
                    shot->unk_54 = -30.0f;
                }

                if ((gGameFrameCount % 4) == 0) {
                    Math_SmoothStepToF(&shot->unk_54, D_i3_801C4458, 0.1f, 50.0f, 0.0001f);
                }

                Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, MTXF_APPLY);

                sp60.x = sp60.y = 0.0f;
                sp60.z = shot->unk_54;

                Matrix_MultVec3f(gCalcMatrix, &sp60, &sp54);

                shot->vel.x = sp54.x;
                shot->vel.y = sp54.y;
                shot->vel.z = sp54.z;

                if ((shot->obj.pos.y < (gGroundHeight + 30.0f)) && (shot->vel.y < 0.0f) && (D_i3_801C4190[3] != 0)) {
                    shot->vel.y = 0.0f;
                }
                break;
        }

        if (D_i3_801C4454 < 297) {
            gLight3x = shot->obj.pos.x;
            gLight3y = shot->obj.pos.y;
            gLight3z = shot->obj.pos.z;
            gLight3R = 255;
            gLight3G = 200;
            gLight3B = 150;
            Math_SmoothStepToF(&gLight3Brightness, 0.8f, 1.0f, 0.08f, 0.001f);
        }

        if (D_i3_801C4454 != 0) {
            D_i3_801C4454--;
        }
    }
}

void Aquas_BlueMarineTorpedo(Player* player) {
    s32 i;
    PlayerShot* shot;

    for (i = 15, shot = &gPlayerShots[15]; i < ARRAY_COUNT(gPlayerShots); i++, shot++) {
        if (shot->obj.status == SHOT_FREE) {
            Player_SetupArwingShot(player, shot, 0.0f, 0.0f, PLAYERSHOT_LOCK_ON, 50.0f);
            AUDIO_PLAY_SFX(NA_SE_MAR_BOMB_SHOT, shot->sfxSource, 0);
            D_i3_801C4190[5] = i + 1;
            D_i3_801C4454 = 300;
            D_i3_801C4458 = -100.0f;
            D_i3_801C445C = 0.1f;
            gLight3Brightness = 1.0f;
            break;
        }
    }
}

void Aquas_BlueMarineLaser(Player* player) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            Player_SetupArwingShot(player, &gPlayerShots[i], 0.0f, -10.0f, PLAYERSHOT_SINGLE_LASER, 120.0f);
            if (gLaserStrength[gPlayerNum] == LASERS_SINGLE) {
                AUDIO_PLAY_SFX(NA_SE_MAR_SHOT, gPlayerShots[i].sfxSource, 0);
            } else {
                AUDIO_PLAY_SFX(NA_SE_MAR_TWIN_LASER, gPlayerShots[i].sfxSource, 0);
            }
            break;
        }
    }
}

void Aquas_BlueMarineShoot(Player* player) {
    s32 temp;
    s32 i;
    f32 tempy1;
    f32 tempy2;
    f32 tempx1;
    f32 tempx2;
    s32 var_v1;
    Vec3f sp68;
    Vec3f sp5C;
    Actor* actor;

    if ((gPlayerShots[D_i3_801C4190[5] - 1].obj.status == SHOT_FREE) && (D_i3_801C4190[5] != 0)) {
        D_i3_801C41B8[21] = D_i3_801C41B8[22] = D_i3_801C41B8[23] = 0.0f;
        D_i3_801C4190[5] = D_i3_801C4190[3] = 0;
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);

    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = -1200.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp5C);

    D_i3_801C41B8[6] = player->pos.x + sp5C.x;
    D_i3_801C41B8[7] = player->pos.y + sp5C.y;
    D_i3_801C41B8[8] = player->trueZpos + sp5C.z;

    if (D_i3_801C4190[3] == 0) {
        if (D_i3_801C4190[0] == 0) {
            D_i3_801C41B8[0] = player->pos.x + sp5C.x;
            D_i3_801C41B8[1] = player->pos.y + sp5C.y;
            D_i3_801C41B8[2] = player->trueZpos + sp5C.z;
            D_i3_801C41B8[5] = 3.0f;
        }

        D_i3_801C41B8[11] = 10000.0f;
        temp = D_i3_801C4190[0];

        for (i = 0, actor = &gActors[0]; i < ARRAY_COUNT(gActors); i++, actor++) {
            if ((actor->obj.status == OBJ_ACTIVE) && (actor->obj.id != OBJ_ACTOR_DEBRIS)) {
                var_v1 = 1;
                if (actor->info.hitbox[1] == HITBOX_ROTATED) {
                    var_v1 = 5;
                }

                tempy1 = actor->obj.pos.y + actor->info.hitbox[var_v1 + 2] + actor->info.hitbox[var_v1 + 3] + 200.0f;
                tempy2 = actor->obj.pos.y + actor->info.hitbox[var_v1 + 2] - actor->info.hitbox[var_v1 + 3] - 200.0f;
                tempx1 = actor->obj.pos.x + actor->info.hitbox[var_v1 + 4] + actor->info.hitbox[var_v1 + 5] + 200.0f;
                tempx2 = actor->obj.pos.x + actor->info.hitbox[var_v1 + 4] - actor->info.hitbox[var_v1 + 5] - 200.0f;

                if ((actor->health > 0) && (actor->timer_0C2 < 5) &&
                    (actor->obj.pos.z <= (player->trueZpos - 300.0f)) &&
                    ((player->trueZpos - 7000.0f) <= actor->obj.pos.z) && (player->pos.y + sp5C.y <= tempy1) &&
                    (tempy2 <= player->pos.y + sp5C.y) && (player->pos.x + sp5C.x <= tempx1) &&
                    (tempx2 <= player->pos.x + sp5C.x) &&
                    (fabsf(player->trueZpos - actor->obj.pos.z - actor->info.hitbox[var_v1 + 0]) < D_i3_801C41B8[11])) {
                    D_i3_801C41B8[11] = fabsf(player->trueZpos - actor->obj.pos.z - actor->info.hitbox[var_v1 + 0]);
                    D_i3_801C4190[0] = actor->index + 1;
                    D_i3_801C4190[1] = actor->obj.id;
                }
            }
        }

        if ((D_i3_801C4190[0] != temp) && (D_i3_801C41B8[5] == 3.0f)) {
            AUDIO_PLAY_SFX(NA_SE_MAR_LOCKON, gDefaultSfxSource, 4);
            D_i3_801C41B8[5] = 20.0f;
        }
        if (D_i3_801C4190[0] != 0) {
            Aquas_801A9C98(player);
        }
        if (gBosses[0].health != 0) {
            Aquas_801A9ED0(player);
        }
    } else {
        Aquas_801A9C98(player);
        Aquas_801A9DE4(player);
    }

    if (gInputPress->button & A_BUTTON) {
        Aquas_BlueMarineLaser(player);
    }

    if (gInputPress->button & B_BUTTON) {
        Aquas_BlueMarineTorpedo(player);
        if (D_i3_801C4190[0] != 0) {
            D_i3_801C4190[3] = 1;
        }
    }

    if (D_i3_801C4190[5] == 0) {
        gLight3x = player->pos.x;
        gLight3y = player->pos.y - 5.0f;
        gLight3z = player->trueZpos - 60.0f;

        gLight3R += 4;
        gLight3G += 3;
        gLight3B += 2;

        if (gLight3R >= 255) {
            gLight3R = 255;
        }
        if (gLight3G > 200) {
            gLight3G = 200;
        }
        if (gLight3B > 150) {
            gLight3B = 150;
        }
        Math_SmoothStepToF(&gLight3Brightness, 0.2f, 1.0f, 0.04f, 0.001f);
    }
}

void Aquas_Effect366_Setup(Effect366* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 state) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_366;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->scale1 = RAND_FLOAT(360.0f);
    this->state = state;
    this->unk_4A = 40;
    this->scale2 = scale2 * 0.2f;
    this->unk_46 = 50;
    this->unk_60.y = gPlayer[0].rot.y + gPlayer[0].yRot_114;

    if (this->state == 2) {
        this->unk_46 = 100;
    }
    Object_SetInfo(&this->info, this->obj.id);
}

void Aquas_Effect366_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 unk4E) {
    s32 i;

    for (i = 0; i < 95; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Aquas_Effect366_Setup(&gEffects[i], xPos, yPos, zPos, scale2, unk4E);
            break;
        }
    }
}

void Aquas_Effect366_Update(Effect366* this) {
    f32 temp_fs0;

    if (this->unk_46 != 0) {
        this->unk_46--;
    }

    switch (this->state) {
        case 0:
            if (this->vel.y < 5.0f) {
                this->vel.y += 0.1f;
            }
            if (this->unk_46 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            this->scale1 += 33.0f;
            temp_fs0 = COS_DEG(this->scale1) * 1.5f;
            this->vel.x = __cosf(gPlayer[0].camYaw) * temp_fs0;
            this->vel.z = __sinf(gPlayer[0].camYaw) * temp_fs0;
            break;

        case 1:
            if (this->unk_46 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            this->unk_60.x += 0.07f;
            this->scale1 += 33.0f;

            this->vel.y = this->unk_60.x + (SIN_DEG(this->scale1) * 3.0f);
            temp_fs0 = COS_DEG(this->scale1) * 3.0f;
            this->vel.x = COS_DEG(this->unk_60.y) * temp_fs0;
            this->vel.z = -SIN_DEG(this->unk_60.y) * temp_fs0;
            break;

        case 2:
            if (this->vel.y < 10.0f) {
                this->vel.y += 0.2f;
            }
            if (this->unk_46 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            this->scale1 += 55.0f;
            temp_fs0 = COS_DEG(this->scale1) * 2.5f;
            this->vel.x = __cosf(gPlayer[0].camYaw) * temp_fs0;
            this->vel.z = __sinf(gPlayer[0].camYaw) * temp_fs0;
            break;
    }
}

void Aquas_BlueMarine_Draw(Player* player) {
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -40.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3000C70);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, -4.5f, 1.2f, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, player->unk_178 * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3006DE0);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 2.0f, 40.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, -player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3006C70);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, -19.0f, -3.6f, 1.2f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3000AF0);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 19.0f, -3.6f, 1.2f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3006AF0);
    Matrix_Pop(&gGfxMatrix);
}

void Aquas_BlueMarineBoost(Player* player) {
    f32 pad;
    f32 pad2;
    Vec3f sp54;
    Vec3f sp48;

    player->sfx.boost = 0;

    if (player->meteoWarpTimer != 0) {
        player->meteoWarpTimer--;
        player->boostSpeed += 0.3f;
        Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114) * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);

        sp54.x = sp54.y = 0.0f;
        sp54.z = 70.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
        Aquas_Effect366_Spawn(player->pos.x + RAND_FLOAT_CENTERED(10.0f) + sp48.x,
                              player->pos.y + RAND_FLOAT_CENTERED(10.0f) + sp48.y,
                              player->trueZpos + RAND_FLOAT_CENTERED(10.0f) + (sp48.z * -1.0f), 0.4f, 1);
        Math_SmoothStepToF(&player->camDist, -130.0f, 0.1f, 10.0f, 0.00001f);

        player->zRotBarrelRoll -= player->meteoWarpSpinSpeed;
        player->meteoWarpSpinSpeed += 0.2f;
        if (player->meteoWarpSpinSpeed > 50.0f) {
            player->meteoWarpSpinSpeed = 50.0f;
        }
        if (((gGameFrameCount % 2) == 0) && (gBlurAlpha > 64)) {
            gBlurAlpha -= 1; // can't be --
        }
    } else {
        player->meteoWarpSpinSpeed = 0.0f;
        if (gBlurAlpha < 255) {
            gBlurAlpha += 4;
            if (gBlurAlpha >= 252) {
                gBlurAlpha = 255;
            }
        }

        if (!(gBrakeButton[player->num] & gInputHold->button) && !(gBoostButton[player->num] & gInputHold->button)) {
            player->boostCooldown = 1;
            if (player->boostMeter == 0.0f) {
                player->boostCooldown = 0;
            }
        }

        if ((gBoostButton[player->num] & gInputHold->button) && (player->unk_230 == 0) &&
            (player->state != PLAYERSTATE_U_TURN) && (player->boostCooldown == 0)) {
            if (player->boostMeter == 0) {
                AUDIO_PLAY_SFX(NA_SE_MARINE_BOOST, player->sfxSource, 4);
            }

            player->boostMeter += 3.0f;
            if (player->boostMeter > 90.0f) {
                player->boostMeter = 90.0f;
                player->boostCooldown = 1;
            }

            player->boostSpeed += 2.0f;
            if (player->boostSpeed > 10.0f) {
                player->boostSpeed = 10.0f;
            }

            Math_SmoothStepToF(&D_i3_801C41B8[27], 10.0f, 0.1f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&player->camDist, -200.0f, 0.1f, D_i3_801C41B8[27], 0.00001f);

            player->sfx.boost = 1;

            Math_SmoothStepToF(&D_ctx_801779A8[0], 50.0f, 1.0f, 10.0f, 0.0f);
        } else {
            D_i3_801C41B8[27] = 0.0f;

            if (player->boostMeter > 0.0f) {
                player->boostMeter -= 0.50f;
                if (player->boostMeter <= 0.0f) {
                    player->boostMeter = 0.0f;
                    player->boostCooldown = 0;
                }
            }

            if (player->boostSpeed > 0.0f) {
                player->boostSpeed -= 1.0f;
                if (player->boostSpeed < 0.0f) {
                    player->boostSpeed = 0.0f;
                }
            }
        }
    }
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 2.0f, 0.0f);
}

void Aquas_BlueMarineBrake(Player* player) {
    player->sfx.brake = false;

    if ((gInputHold->button & gBrakeButton[player->num]) && (player->unk_230 == 0) &&
        (player->state != PLAYERSTATE_U_TURN) && (player->boostCooldown == 0)) {
        if (player->boostMeter == 0) {
            AUDIO_PLAY_SFX(NA_SE_MARINE_BRAKE, player->sfxSource, 4);
        }

        player->boostMeter += 3.0f;
        if (player->boostMeter > 90.0f) {
            player->boostMeter = 90.0f;
            player->boostCooldown = 1;
        }

        player->boostSpeed -= 1.0f;
        if (player->boostSpeed < -20.0f) {
            player->boostSpeed = -20.0f;
        }

        Math_SmoothStepToF(&D_i3_801C41B8[28], 10.0f, 1.0f, 2.0f, 0.00001f);
        Math_SmoothStepToF(&player->camDist, 180.0f, 0.1f, D_i3_801C41B8[28], 0.0f);

        player->sfx.brake = true;

        Math_SmoothStepToF(&D_ctx_801779A8[0], 25.0f, 1.0f, 5.0f, 0.0f);
    } else {
        if (player->boostMeter > 0.0f) {
            player->boostMeter -= 0.5f;
            if (player->boostMeter <= 0.0f) {
                player->boostMeter = 0.0f;
                player->boostCooldown = 0;
                D_i3_801C41B8[28] = 0.0f;
            }

            Math_SmoothStepToF(&D_i3_801C41B8[28], 0.0f, 1.0f, 1.0f, 0.0001f);

            if (player->boostSpeed < 0.0f) {
                player->boostSpeed += 0.5f;
                if (player->boostSpeed > 0.0f) {
                    player->boostSpeed = 0.0f;
                }
            }
        }
    }
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 2.0f, 0.0f);
}

void Aquas_801AD598(Actor255* this) {
    s32 i;

    D_i3_801C27C0 = &D_i3_801C27C8[50 * this->iwork[0]];

    for (i = 50 * this->iwork[0]; i < 50 * this->iwork[0] + 50; i++, D_i3_801C27C0++) {
        D_i3_801C27C0->pos.x = this->obj.pos.x;
        D_i3_801C27C0->pos.y = this->obj.pos.y;
        D_i3_801C27C0->pos.z = this->obj.pos.z;
        D_i3_801C27C0->rot.x = this->obj.rot.x;
        D_i3_801C27C0->rot.y = this->obj.rot.y;
        D_i3_801C27C0->rot.z = this->obj.rot.z;
        D_i3_801C27C0->rot.x = this->rot_0F4.x;
        D_i3_801C27C0->rot.y = this->rot_0F4.y;
        D_i3_801C27C0->rot.z = this->rot_0F4.z;
    }
}

void Aquas_Actor255_Init(Actor255* this) {
    Aquas_801AD598(this);
    this->iwork[1] = 10;
    this->scale = 1.0f;
}

void Aquas_Actor255_Update(Actor255* this) {
    s32 var_v0 = this->iwork[2] - 1;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;

    if ((D_i3_801C42A0[23] == 0) || (gActors[var_v0].state >= 4)) {
        this->timer_0C2 = 30000;
        this->state = 2;
        this->vel.y = 0.0f;
        this->vel.x = 0.0f;
        this->vel.z = 0.0f;
    }

    if ((gPlayer[0].trueZpos + 500.0f) <= this->obj.pos.z) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    this->counter_04E++;
    if (this->counter_04E >= 50) {
        this->counter_04E = 0;
    }

    switch (this->state) {
        case 0:
            if (this->timer_0BC != 0) {
                this->rot_0F4.x += D_i3_801C4308[10];
                this->rot_0F4.z += 10.0f;
                this->rot_0F4.z = Math_ModF(this->rot_0F4.z, 360.0f);
            } else {
                this->health = 30;
                AUDIO_PLAY_SFX(NA_SE_EN_SANADA_SWIM, this->sfxSource, 4);
                this->state++;
            }
            break;

        case 1:
            if (this->dmgType != DMG_NONE) {
                if (this->health > 0) {
                    this->dmgType = DMG_NONE;
                    this->timer_0C6 = 15;
                    this->health -= this->damage;

                    AUDIO_PLAY_SFX(NA_SE_EN_SANADA_DAMAGE, this->sfxSource, 4);

                    if (this->health <= 0) {
                        this->timer_0C2 = 30000;
                        this->state = 2;
                        this->vel.y = 0.0f;
                        this->vel.x = 0.0f;
                        this->vel.z = 0.0f;
                        AUDIO_PLAY_SFX(NA_SE_EN_SANADA_DOWN, this->sfxSource, 4);
                    }
                }
            }

            if (this->obj.pos.z <= (gPlayer[0].trueZpos - 200.0f)) {
                this->fwork[7] = sp80 = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(100.0f) - this->obj.pos.x;
                this->fwork[8] = sp7C = gPlayer[0].pos.y - 30.0f - this->obj.pos.y;
                this->fwork[9] = sp78 = gPlayer[0].trueZpos - this->obj.pos.z;
            } else {
                sp80 = this->fwork[7];
                sp7C = this->fwork[8];
                sp78 = this->fwork[9] + 600.0f;
            }

            Math_RadToDeg(Math_Atan2F(sp80, sp78));
            sp70 = sqrtf(SQ(sp80) + SQ(sp78));
            Math_RadToDeg(-Math_Atan2F(sp7C, sp70));

            this->fwork[0] += (this->iwork[0] + 1) * 5.0f;
            this->fwork[1] += 10.0f + (this->iwork[0] + 1) * 5.0f;
            this->fwork[5] = (this->iwork[0] + 1) * 0.2f;
            this->fwork[6] = (this->iwork[0] + 1) * 0.2f;

            sp7C = SIN_DEG(this->fwork[0]) * sp70 * this->fwork[5];
            sp74 = COS_DEG(this->fwork[1]) * sp70 * this->fwork[6];
            sp80 = COS_DEG(this->rot_0F4.y) * sp74;
            sp78 = -SIN_DEG(this->rot_0F4.y) * sp74;

            if (sp7C < 20.0f) {
                sp7C = 20.0f;
            }

            if ((Rand_ZeroOne() < 0.7) && (this->obj.rot.z == 0.0f)) {
                this->fwork[2] = 360.0f;
            }

            Math_SmoothStepToF(&this->rot_0F4.z, this->fwork[2], 0.1f, 10.0f, 0.001f);

            if (this->rot_0F4.z >= 360.0f) {
                this->rot_0F4.z = 0.0f;
                this->fwork[2] = 0.0f;
            }

            sp68 = Math_RadToDeg(Math_Atan2F(gPlayer[0].pos.x + sp80 + RAND_FLOAT_CENTERED(200.0f) - this->obj.pos.x,
                                             gPlayer[0].trueZpos + sp78 - this->obj.pos.z));
            sp6C = Math_RadToDeg(-Math_Atan2F(gPlayer[0].pos.y - 30.0f + sp7C - this->obj.pos.y, sp70));

            if (gPlayer[0].trueZpos <= this->obj.pos.z) {
                sp68 = this->rot_0F4.y;
                sp6C = this->rot_0F4.x;
            }

            Math_SmoothStepToAngle(&this->rot_0F4.y, sp68, 1.0f, 5.0f, 0.001f);
            Math_SmoothStepToAngle(&this->rot_0F4.x, sp6C, 1.0f, 5.0f, 0.001f);
            Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);

            sp5C.x = 0.0f;
            sp5C.y = 0.0f;
            sp5C.z = 40.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
            sp5C.z = 10.0f + (this->iwork[0] + 1) * RAND_FLOAT(10.0f);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp44);
            this->vel.x = sp50.x;
            this->vel.y = sp50.y;
            this->vel.z = sp44.z;
            break;

        case 2:
            if (this->timer_0C6 == 0) {
                this->timer_0C6 = 15;
            }
            if (this->timer_0BC == 0) {
                var_v0 = this->iwork[0] * 50 + this->counter_04E - D_i3_801BFB64[this->iwork[1]];
                if (var_v0 < this->iwork[0] * 50) {
                    if (var_v0 > 0) {
                        var_v0 -= this->iwork[0] * 50;
                    }
                    var_v0 = var_v0 + (this->iwork[0] + 1) * 50;
                }
                D_i3_801C27C0 = &D_i3_801C27C8[var_v0];
                func_effect_800815DC();
                this->iwork[1]--;
                if (this->iwork[1] <= 0) {
                    this->itemDrop = DROP_NONE;
                    this->dmgSource = DMG_SRC_2;
                    Actor_Despawn(this);
                    Object_Kill(&this->obj, this->sfxSource);
                }
                this->timer_0BC = 4;
                func_effect_8007D0E0(D_i3_801C27C0->pos.x, D_i3_801C27C0->pos.y, D_i3_801C27C0->pos.z, 3.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_SEA_EXPLOSION_S, this->sfxSource, 4);
            }
            break;
    }
    D_i3_801C27C0 = &D_i3_801C27C8[50 * this->iwork[0] + this->counter_04E];

    D_i3_801C27C0->pos.x = this->obj.pos.x;
    D_i3_801C27C0->pos.y = this->obj.pos.y;
    D_i3_801C27C0->pos.z = this->obj.pos.z;

    D_i3_801C27C0->rot.x = this->rot_0F4.x;
    D_i3_801C27C0->rot.y = this->rot_0F4.y;
    D_i3_801C27C0->rot.z = this->rot_0F4.z;
}

void Aquas_801ADF7C(f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, u8 type, s32 flag, f32 scale,
                    s32 index) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, xPos, yPos, zPos + gPathProgress, MTXF_APPLY);

    Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * xRot, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * zRot, MTXF_APPLY);

    Graphics_SetScaleMtx(scale);

    if (index < 2) {
        if (!flag) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_57);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        }
    } else {
        if (!flag) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_57);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        }
    }
    gSPDisplayList(gMasterDisp++, D_i3_801BFB9C[type]);
    Matrix_Pop(&gGfxMatrix);
}

// Bacoon Snake
void Aquas_Actor255_Draw(Actor255* this) {
    s32 i;
    f32 xz;
    f32 yRot;
    f32 xRot;
    s32 index;

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);

    for (i = 0; i <= this->iwork[1]; i++) {
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild(this, i);

        if ((this->iwork[1] != 10) && (i == 0)) {
            i = 1;
        }

        index = ((this->iwork[0] * 50) + this->counter_04E) - D_i3_801BFB64[i];

        if (index < (this->iwork[0] * 50)) {
            if (index > 0) {
                index -= this->iwork[0] * 50;
            }
            index = index + ((this->iwork[0] + 1) * 50);
        }

        D_i3_801C27C0 = &D_i3_801C27C8[index];

        xRot = D_i3_801C27C0->rot.x;
        yRot = D_i3_801C27C0->rot.y;

        if (i >= 2) {
            yRot = RAD_TO_DEG(Math_Atan2F(gPlayer[0].cam.eye.x - D_i3_801C27C0->pos.x,
                                          gPlayer[0].cam.eye.z - (D_i3_801C27C0->pos.z + gPathProgress)));
            xz = sqrtf(((gPlayer[0].cam.eye.z - (D_i3_801C27C0->pos.z + gPathProgress)) *
                        (gPlayer[0].cam.eye.z - (D_i3_801C27C0->pos.z + gPathProgress))) +
                       ((gPlayer[0].cam.eye.x - D_i3_801C27C0->pos.x) * (gPlayer[0].cam.eye.x - D_i3_801C27C0->pos.x)));
            xRot = RAD_TO_DEG(-Math_Atan2F(gPlayer[0].cam.eye.y - D_i3_801C27C0->pos.y, xz));
        }

        Aquas_801ADF7C(D_i3_801C27C0->pos.x, D_i3_801C27C0->pos.y, D_i3_801C27C0->pos.z, xRot, yRot,
                       D_i3_801C27C0->rot.z, D_i3_801BFB90[i], this->timer_0C6 % 2U, this->scale, i);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Aquas_Actor256_Init(Actor256* this) {
    this->fwork[1] = 1.0f;
    this->obj.rot.x = 336.0f;
    this->scale = 0.5f;
}

void Aquas_Actor256_Update(Actor256* this) {
    s32 i;

    switch (this->state) {
        case 0:
            this->obj.pos.y = fabsf(D_i3_801C4308[10] * 15.0f) + 347.0f;
            if (this->obj.pos.y >= 757.0f) {
                this->obj.pos.y = 757.0f;
            }
            if (this->obj.pos.y <= 347.0f) {
                this->obj.pos.y = 347.0f;
            }

            this->scale = fabsf(D_i3_801C4308[10] / -28.0f) + 0.5f;

            if (this->scale > 1.3f) {
                this->scale = 1.3f;
            }
            if (this->scale <= 0.5f) {
                this->scale = 0.5f;
            }

            if (gBosses[0].timer_052 == 0) {
                this->health = 0;
                if (this->info.hitbox[10] != 116.0f) {
                    this->info.hitbox[10] = 116.0f;
                }
            }

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                if ((fabsf(D_i3_801C4308[10]) >= 6.0f) && (gBosses[0].state >= 10) &&
                    (gBosses[0].swork[AQ_SWK_0] < 2)) {
                    this->timer_0C6 = 30;
                    this->iwork[1] = 0;
                    D_i3_801C4308[79] -= 5.0f;

                    AUDIO_PLAY_SFX(NA_SE_EN_KAIBASHIRA_DAMAGE, this->sfxSource, 4);

                    if (D_i3_801C4308[79] <= -28.0f) {
                        D_i3_801C4308[79] = -28.0f;
                    }

                    if (D_i3_801C4308[10] <= -23.0f) {
                        if (gBosses[0].timer_052 == 0) {
                            gBosses[0].timer_052 = 72;

                            this->health = 10;

                            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                                if ((gActors[i].obj.id == OBJ_ACTOR_256) && (this->index != gActors[i].index)) {
                                    gActors[i].health = 10;
                                }
                            }
                        } else {
                            this->iwork[1] = 0;
                            this->timer_0C6 = 0;
                        }

                        if (gBosses[0].swork[AQ_SWK_0] == 0) {
                            gBosses[0].swork[AQ_SWK_0] = 1;
                            this->info.hitbox[10] = 300.0f;
                            if (this->iwork[23] == 0) {
                                Radio_PlayMessage(gMsg_ID_15120, RCID_SLIPPY);
                            }
                            this->iwork[23]++;
                            this->iwork[23] &= 1;
                        } else if (this->damage == 31) {
                            this->health -= this->damage;

                            Radio_PlayMessage(gMsg_ID_15130, RCID_FALCO);

                            if (this->health <= 0) {
                                gBosses[0].swork[AQ_SWK_0] = 2;
                                this->health = 0;
                                this->timer_0C6 = 300;
                                this->fwork[2] = this->scale;
                                AUDIO_PLAY_SFX(NA_SE_EN_WT_DISAPPEAR_L, this->sfxSource, 4);
                                this->state++;
                            }
                        }
                    }
                }
            }
            break;

        case 1:
            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect390_Spawn(this->obj.pos.x, this->fwork[0] + this->obj.pos.y, this->obj.pos.z, this->vel.x,
                                       this->vel.y, this->vel.z, 0.1f, 10);
                Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + (this->fwork[0] * -1.0f),
                                       this->obj.pos.z + 200.0f, this->vel.x, this->vel.y, this->vel.z, 0.1f, 10);
                this->fwork[0] += 40.0f;
            }

            if ((this->fwork[2] * 400.0f) <= this->fwork[0]) {
                this->timer_0BC = 20;
                this->state++;
            }
            break;

        case 2:
            if (this->timer_0BC == 0) {
                for (i = 0; i < 6; i++) {
                    Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y + 450.0f, this->obj.pos.z + 50.0f, 50.0f);
                    Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y - 420.0f, this->obj.pos.z + 300.0f, 50.0f);
                }
                this->fwork[3] = 0.7f;
                this->timer_0BC = 10;

                this->state++;
            }
            break;

        case 3:
            if (this->timer_0BC == 0) {
                Math_SmoothStepToF(&this->fwork[3], 0.0f, 0.1f, 2.0f, 0);
                Math_SmoothStepToF(&this->scale, 0.0f, this->fwork[3], 10.0f, 0);

                if (this->scale <= 0.2f) {
                    Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 50.0f);
                    Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 50.0f);
                    Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 50.0f);

                    Object_Kill(&this->obj, this->sfxSource);

                    D_i3_801C42A0[23]--;

                    gBosses[0].swork[AQ_SWK_0] = 3;
                    gBosses[0].swork[AQ_SWK_19] = 30;

                    D_i3_801C4308[79] = 0.0f;

                    if (D_i3_801C42A0[23] == 0) {
                        D_i3_801C4308[79] = -180.0f;
                        for (i = 0; i < 60; i++) {
                            Aquas_Effect366_Spawn(gBosses[0].obj.pos.x + RAND_FLOAT_CENTERED(1800.0f),
                                                  gBosses[0].obj.pos.y + 400.0f + RAND_FLOAT_CENTERED(1000.0f),
                                                  gBosses[0].obj.pos.z + 700.0f + RAND_FLOAT_CENTERED(1000.0f), 7.0f,
                                                  2);
                        }
                        gBosses[0].timer_052 = 0;
                        gBosses[0].timer_056 = 60;
                        gBosses[0].state = 14;
                    }
                    D_i3_801C4308[80] += D_i3_801BFBA8[this->iwork[0]];
                }
            }
            break;
    }
}

void Aquas_Actor256_Draw(Actor256* this) {
    f32 var_fv0;
    u8 var_t1;
    u8 i;
    Vtx* var_t5;
    Vtx* temp_v1_2;

    if ((this->timer_0C6 != 0) && (this->state == 0) && (gPlayState != PLAY_PAUSE)) {
        this->iwork[1]++;
        this->iwork[1] %= 8;
    }

    temp_v1_2 = SEGMENTED_TO_VIRTUAL(D_AQ_6019078);
    if (this->iwork[1] < 4) {
        var_t5 = SEGMENTED_TO_VIRTUAL(D_AQ_6018C78);
    } else {
        var_t5 = LOAD_ASSET(D_AQ_6018878);
    }

    var_t1 = this->iwork[1] % 4;
    if (var_t1 >= 3) {
        var_t1 = 4 - var_t1;
    }

    var_fv0 = this->timer_0C6 / 60.0f;
    if (var_fv0 < 0.1f) {
        var_fv0 = 0.1f;
    }

    for (i = 0; i < 28; i += 1) {
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.ob[0] =
            temp_v1_2[i].n.ob[0] + (s16) ((((var_t5[i].n.ob[0] - temp_v1_2[i].n.ob[0]) * var_t1) / 2) * var_fv0);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.ob[1] =
            temp_v1_2[i].n.ob[1] + (((var_t5[i].n.ob[1] - temp_v1_2[i].n.ob[1]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.ob[2] =
            temp_v1_2[i].n.ob[2] + (((var_t5[i].n.ob[2] - temp_v1_2[i].n.ob[2]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.flag = temp_v1_2[i].n.flag;
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.tc[0] =
            temp_v1_2[i].n.tc[0] + (((var_t5[i].n.tc[0] - temp_v1_2[i].n.tc[0]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.tc[1] =
            temp_v1_2[i].n.tc[1] + (((var_t5[i].n.tc[1] - temp_v1_2[i].n.tc[1]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.n[0] =
            temp_v1_2[i].n.n[0] + (((var_t5[i].n.n[0] - temp_v1_2[i].n.n[0]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.n[1] =
            temp_v1_2[i].n.n[1] + (((var_t5[i].n.n[1] - temp_v1_2[i].n.n[1]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.n[2] =
            temp_v1_2[i].n.n[2] + (((var_t5[i].n.n[2] - temp_v1_2[i].n.n[2]) * var_t1) / 2);
        D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][i].n.a = temp_v1_2[i].n.a;
    }

    Matrix_Scale(gGfxMatrix, this->fwork[1] - 0.25f + ((1.5f - this->scale) * 0.5f), this->scale, this->fwork[1],
                 MTXF_APPLY);

    if (this->state != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_32);
    } else if (gBosses[0].swork[AQ_SWK_0] == 1) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_4);
    } else if ((this->timer_0C6 % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_22);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetTextureLUT(gMasterDisp++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gMasterDisp++, D_AQ_6008FC8);
    gDPLoadTextureBlock(gMasterDisp++, D_AQ_6008EC8, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(gMasterDisp++, D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2], 14, 0);
    gSP1Triangle(gMasterDisp++, 0, 1, 2, 0);
    gSP1Triangle(gMasterDisp++, 3, 1, 0, 0);
    gSP1Triangle(gMasterDisp++, 4, 5, 0, 0);
    gSP1Triangle(gMasterDisp++, 0, 6, 7, 0);
    gSP1Triangle(gMasterDisp++, 2, 6, 0, 0);
    gSP1Triangle(gMasterDisp++, 0, 5, 3, 0);
    gSP1Triangle(gMasterDisp++, 0, 8, 4, 0);
    gSP1Triangle(gMasterDisp++, 7, 8, 0, 0);
    gSP1Triangle(gMasterDisp++, 9, 4, 8, 0);
    gSP1Triangle(gMasterDisp++, 8, 7, 10, 0);
    gSP1Triangle(gMasterDisp++, 8, 11, 9, 0);
    gSP1Triangle(gMasterDisp++, 10, 11, 8, 0);
    gSP1Triangle(gMasterDisp++, 12, 4, 9, 0);
    gSP1Triangle(gMasterDisp++, 13, 5, 4, 0);
    gSP1Triangle(gMasterDisp++, 4, 12, 13, 0);
    gSP1Triangle(gMasterDisp++, 3, 5, 13, 0);
    gSP1Triangle(gMasterDisp++, 13, 6, 2, 0);
    gSP1Triangle(gMasterDisp++, 7, 6, 13, 0);
    gSP1Triangle(gMasterDisp++, 13, 12, 7, 0);
    gSP1Triangle(gMasterDisp++, 10, 7, 12, 0);
    gSPVertex(gMasterDisp++, &D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][1], 3, 0);
    gSPVertex(gMasterDisp++, &D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][9], 2, 3);
    gSPVertex(gMasterDisp++, &D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][12], 8, 5);
    gSP1Triangle(gMasterDisp++, 0, 2, 7, 0);
    gSP1Triangle(gMasterDisp++, 7, 2, 8, 0);
    gSP1Triangle(gMasterDisp++, 6, 8, 2, 0);
    gSP1Triangle(gMasterDisp++, 8, 1, 9, 0);
    gSP1Triangle(gMasterDisp++, 1, 8, 6, 0);
    gSP1Triangle(gMasterDisp++, 5, 10, 4, 0);
    gSP1Triangle(gMasterDisp++, 3, 10, 5, 0);
    gSP1Triangle(gMasterDisp++, 8, 12, 7, 0);
    gSP1Triangle(gMasterDisp++, 7, 11, 0, 0);
    gSP1Triangle(gMasterDisp++, 0, 11, 9, 0);
    gSP1Triangle(gMasterDisp++, 9, 1, 0, 0);
    gSP1Triangle(gMasterDisp++, 9, 12, 8, 0);
    gDPLoadTLUT_pal256(gMasterDisp++, D_AQ_6019338);
    gDPLoadTextureBlock(gMasterDisp++, D_AQ_6019238, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(gMasterDisp++, &D_i3_801C3A88[this->iwork[0]][gSysFrameCount % 2][20], 8, 0);
    gSP1Triangle(gMasterDisp++, 0, 1, 2, 0);
    gSP1Triangle(gMasterDisp++, 2, 3, 0, 0);
    gSP1Triangle(gMasterDisp++, 4, 5, 6, 0);
    gSP1Triangle(gMasterDisp++, 6, 7, 4, 0);
    gDPPipeSync(gMasterDisp++);
    gDPSetTextureLUT(gMasterDisp++, G_TT_NONE);
}

void Aquas_Actor257_Init(Actor257* this) {
    s32 temp = this->iwork[0];

    this->fwork[0] = this->fwork[1] = this->fwork[2] = 1.0f;
    this->obj.pos.x = D_i3_801C4308[1 + temp];
    this->obj.pos.y = D_i3_801C4308[4 + temp];
    this->obj.pos.z = D_i3_801C4308[7 + temp];
    this->obj.rot.x = D_i3_801BFBBC[temp] + D_i3_801C4308[10];
}

void Aquas_Actor257_Update(Actor257* this) {
    s32 i;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 pad64;
    Vec3f sp58;
    Vec3f sp4C;
    Actor* sp48;

    if (this->state < 4) {
        i = this->iwork[0];

        this->obj.pos.x = D_i3_801C4308[1 + i];
        this->obj.pos.y = D_i3_801C4308[4 + i];
        this->obj.pos.z = D_i3_801C4308[7 + i];

        this->obj.rot.x = D_i3_801BFBBC[i] + D_i3_801C4308[10];
        if (this->obj.rot.x < 0.0f) {
            this->obj.rot.x += 359.0f;
        }
        if (this->obj.rot.x >= 360.0f) {
            this->obj.rot.x -= 360.0f;
        }
        this->obj.rot.y = D_i3_801BFBC8[i];
        this->obj.rot.z = D_i3_801BFBD4[i];
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;

        if ((gBosses[0].state >= 10) && (this->health != 0) && (this->damage == 31)) {
            this->timer_0BE = 70;
            this->health -= this->damage;

            AUDIO_PLAY_SFX(NA_SE_EN_WT_DAMAGE_S, this->sfxSource, 4);

            if (this->timer_0C6 == 0) {
                this->timer_0C6 = 70;
            }

            if (this->health <= 0) {
                this->health = this->timer_0BE = 0;
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 3);
                gHitCount += 4;
                D_ctx_80177850 = 15;
                this->info.bonus = 0;
                this->state = 4;
            }
        }
    }

    if (D_i3_801C42A0[23] == 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (this->timer_0C6 & 1) {
        Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + 100.0f, this->obj.pos.z + RAND_FLOAT(500.0f),
                               this->vel.x, this->vel.y, this->vel.z, this->scale * 0.2f, 10);
    }

    switch (this->state) {
        case 0:
            if (gBosses[0].state >= 10) {
                this->timer_0BC = D_i3_801BFBB0[this->iwork[0]] + RAND_FLOAT(20.0f);
                this->health = 90;
                this->state++;
            }
            break;

        case 1:
            if ((this->timer_0BC == 0) && (fabsf(D_i3_801C4308[10]) < 5.0f) && (this->timer_0C6 == 0)) {
                i = this->iwork[3] - 1;
                if (i >= 0) {
                    if (!((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_255) &&
                          (gActors[i].iwork[0] == this->iwork[0]))) {
                        this->iwork[3] = 0;
                        this->state = 2;
                    }
                } else {
                    this->iwork[3] = 0;
                    this->state = 2;
                }
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[0], 1.0f, 0.2f, 0.5f, 0.01f);
            this->fwork[2] = this->fwork[1] = this->fwork[0];
            if (this->fwork[0] == 1.0f) {
                this->state = 3;
            }
            break;

        case 3:
            i = this->iwork[2] * 4;
            Math_SmoothStepToF(&this->fwork[0], D_i3_801BFBE0[i], D_i3_801BFBE0[i + 1], D_i3_801BFBE0[i + 2], 0.00001f);
            Math_SmoothStepToF(&this->fwork[1], D_i3_801BFC10[i], D_i3_801BFC10[i + 1], D_i3_801BFC10[i + 2], 0.00001f);
            Math_SmoothStepToF(&this->fwork[2], D_i3_801BFC40[i], D_i3_801BFC40[i + 1], D_i3_801BFC40[i + 2], 0.00001f);
            this->iwork[1]++;
            i = this->iwork[3] - 1;

            if ((i >= 0) && !((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_255) &&
                              (gActors[i].iwork[0] == this->iwork[0]))) {
                this->iwork[3] = 0;
                i = -1;
            }

            if ((this->iwork[1] == 13) && (i < 0)) {
                AUDIO_PLAY_SFX(NA_SE_EN_SANADA_APPEAR, this->sfxSource, 4);
                for (i = 0, sp48 = &gActors[0]; i < ARRAY_COUNT(gActors); i++, sp48++) {
                    if (sp48->obj.status == OBJ_FREE) {
                        Actor_Initialize(sp48);
                        sp48->obj.status = OBJ_INIT;
                        sp48->obj.id = OBJ_ACTOR_255;
                        sp48->obj.pos.x = this->obj.pos.x;
                        sp48->obj.pos.y = this->obj.pos.y;
                        sp48->obj.pos.z = this->obj.pos.z;
                        sp48->obj.rot.x = sp48->rot_0F4.x =
                            Math_ModF(this->obj.rot.x + 270.0f + D_i3_801BFC7C[this->iwork[0]], 360.0f);
                        sp48->obj.rot.y = sp48->rot_0F4.y =
                            Math_ModF(this->obj.rot.y + D_i3_801BFC88[this->iwork[0]], 360.0f);
                        sp48->rot_0F4.z = this->obj.rot.z;
                        sp48->obj.rot.z = this->obj.rot.z;
                        sp48->timer_0BC = 10;
                        Object_SetInfo(&sp48->info, sp48->obj.id);
                        this->iwork[3] = i + 1;
                        sp48->iwork[0] = this->iwork[0];
                        sp48->iwork[2] = this->index + 1;
                        Matrix_RotateY(gCalcMatrix, sp48->obj.rot.y * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, sp48->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateZ(gCalcMatrix, sp48->obj.rot.z * M_DTOR, MTXF_APPLY);
                        sp58.x = sp58.y = 0.0f;
                        sp58.z = 60.0f;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
                        sp48->vel.x = sp4C.x;
                        sp48->vel.y = sp4C.y;
                        sp48->vel.z = sp4C.z;
                        break;
                    }
                }
                if (i >= ARRAY_COUNT(gActors)) {
                    this->iwork[3] = 0;
                    sp48->obj.status = OBJ_FREE;
                }
            }

            if (this->iwork[1] == D_i3_801BFC70[this->iwork[2]]) {
                this->iwork[2]++;
                if (this->iwork[2] >= 3) {
                    this->iwork[1] = this->iwork[2] = 0;
                    this->state = 1;
                    this->fwork[0] = this->fwork[1] = this->fwork[2] = 1.0f;
                    this->timer_0BC = D_i3_801BFBB0[this->iwork[0]] + 70.0f - RAND_FLOAT_CENTERED(30.0f);
                }
            }
            break;

        case 4:
            this->state = 5;
            this->vel.y = 10.0f;
            this->vel.z = 5.0f;
            AUDIO_PLAY_SFX(NA_SE_EN_WT_BROKEN, this->sfxSource, 4);
            break;

        case 5:
            if (this->obj.pos.y > (gGroundHeight + 70.0f)) {
                Math_SmoothStepToF(&this->fwork[0], 1.0f, 0.1f, 0.2f, 0.0001f);
                Math_SmoothStepToF(&this->fwork[1], 1.0f, 0.1f, 0.2f, 0.0001f);
                Math_SmoothStepToF(&this->fwork[2], 1.0f, 0.1f, 0.2f, 0.0001f);
                Math_SmoothStepToF(&this->vel.y, -10.0f, 0.1f, 1.0f, 0.001f);
                Math_SmoothStepToAngle(&this->obj.rot.x, 80.0f, 0.1f, 1.0f, 0.001f);

                if (((gGameFrameCount % 2) == 0)) {
                    Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(300.0f),
                                          this->obj.pos.y + RAND_FLOAT_CENTERED(200.0f), this->obj.pos.z, 4.0f, 2);
                }

                if (this->timer_0C6 == 0) {
                    this->timer_0C6 = 70;
                }
                this->fwork[6] = 10.0f;
                this->timer_0C0 = 20;
            } else {
                Math_SmoothStepToF(&this->fwork[6], 30.0f, 0.1f, 12.0f, 0.1f);
                sp70 = RAND_FLOAT(30.0f);

                if (((gGameFrameCount % 4) == 0)) {
                    for (i = 0; i < 36; i += 2) {
                        sp6C = __sinf(sp70 + (i * 10.0f * M_DTOR)) * this->fwork[6] * 10.0f;
                        sp68 = __cosf(sp70 + (i * 10.0f * M_DTOR)) * this->fwork[6] * 10.0f;
                        pad64 = gGroundHeight + 30.0f;
                        Effect_Effect364_Spawn(this->obj.pos.x + sp6C, pad64, this->obj.pos.z + sp68, 20.0f);
                    }
                }

                if (this->vel.z != 0) {
                    this->vel.y = this->vel.z = 0.0f;
                    AUDIO_PLAY_SFX(NA_SE_EN_WT_BOUND_M, this->sfxSource, 4);
                }

                if (this->timer_0C0 == 1) {
                    AUDIO_PLAY_SFX(NA_SE_EN_WT_DISAPPEAR_S, this->sfxSource, 4);
                }

                if (this->timer_0C0 == 0) {
                    if (this->timer_0BE == 0) {
                        this->timer_0BE = 10;
                    }

                    Math_SmoothStepToF(&this->fwork[0], 0.0f, 0.05f, 0.1f, 0.001f);
                    Math_SmoothStepToF(&this->fwork[1], 0.0f, 0.05f, 0.1f, 0.001f);
                    Math_SmoothStepToF(&this->fwork[2], 0.0f, 0.05f, 0.1f, 0.001f);
                    Math_SmoothStepToF(&this->obj.pos.y, -300.0f, 0.1f, 1.0f, 0.001f);

                    if (this->fwork[0] <= 0.2f) {
                        for (i = 0; i < 5; i++) {
                            Effect_Effect362_Spawn(this->obj.pos.x, gGroundHeight + 50.0f, this->obj.pos.z, 20.0f);
                            Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(300.0f),
                                                  gGroundHeight + (i * 20.0f), this->obj.pos.z, 5.0f, 2);
                        }

                        if (gBosses[0].state < 13) {
                            gBosses[0].state++;
                            if (gBosses[0].state == 13) {
                                gBosses[0].swork[AQ_SWK_19] = 30;
                            }
                        }
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                }
            }
            break;
    }

    if (this->timer_0BE != 0) {
        this->fwork[3] = SIN_DEG(this->timer_0BE * 20.0f) * Aquas_801A958C(this->timer_0BE, 20.0f);
        this->fwork[4] = SIN_DEG(this->timer_0BE * 20.0f) * Aquas_801A958C(this->timer_0BE, 20.0f);
        this->fwork[5] = SIN_DEG(this->timer_0BE * 20.0f) * Aquas_801A958C(this->timer_0BE, 20.0f);
    }
}

void Aquas_Actor257_Draw(Actor257* this) {
    Matrix_RotateY(gGfxMatrix, (this->obj.rot.x + this->fwork[3]) * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, (this->obj.rot.y + this->fwork[4]) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, (this->obj.rot.z + this->fwork[5]) * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, this->fwork[0], this->fwork[1], this->fwork[2], MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if ((this->timer_0C6 % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild(this, this->iwork[0]);

    switch (this->iwork[0]) {
        case 0:
            gSPDisplayList(gMasterDisp++, D_AQ_6019E80);
            break;
        case 1:
            gSPDisplayList(gMasterDisp++, D_AQ_60194D0);
            break;
        case 2:
            gSPDisplayList(gMasterDisp++, D_AQ_6019880);
            break;
    }

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Aquas_AqPearl_Update(AqPearl* this) {
    Vec3f sp44;
    Vec3f sp38;

    if ((this->dmgType != DMG_NONE) || (gBosses[0].state >= 16)) {
        this->state = 3;
    }

    switch (this->state) {
        case 0:
            if (this->timer_0BC == 0) {
                Matrix_RotateY(gCalcMatrix, this->fwork[2] * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->fwork[1] * M_DTOR, MTXF_APPLY);
                sp44.x = sp44.y = 0.0f;
                sp44.z = 50.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                this->vel.x = sp38.x;
                this->vel.y = sp38.y;
                this->vel.z = sp38.z;
                this->timer_0BE = 5;
                this->iwork[1] = 255;
                this->iwork[2] = 255;
                this->iwork[3] = 255;
                this->state++;
            }
            break;

        case 1:
            if (this->timer_0BE == 0) {
                Matrix_RotateY(gCalcMatrix, this->fwork[4] * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->fwork[3] * M_DTOR, MTXF_APPLY);
                sp44.x = sp44.y = 0.0f;
                sp44.z = 30.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                this->vel.x = sp38.x;
                this->vel.y = sp38.y;
                this->vel.z = sp38.z;
                this->timer_0C0 = 10;
                this->state++;
            }
            break;

        case 2:
            if (this->timer_0C0 == 0) {
                this->iwork[1] -= 20;
                this->iwork[2] -= 20;
                this->iwork[3] -= 20;
                if (this->iwork[1] < 5) {
                    this->iwork[1] = this->iwork[2] = this->iwork[3] = 5;
                }
            }
            break;

        case 3:
            if (Rand_ZeroOne() < 0.1) {
                this->itemDrop = DROP_SILVER_RING_10p;
                this->dmgSource = DMG_SRC_2;
                Actor_Despawn(this);
            }
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_800815DC();
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, 5.0f);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_SEA_EXPLOSION_S);
            break;
    }

    if (((gGameFrameCount % 16) == 0)) {
        Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(10.0f),
                              this->obj.pos.y + RAND_FLOAT_CENTERED(10.0f),
                              this->obj.pos.z + RAND_FLOAT_CENTERED(10.0f), 2.0f, 1);
    }
    Aquas_801A96DC(this);
}

void Aquas_AqPearl_Draw(AqPearl* this) {
    if (this->timer_0BC == 0) {
        Graphics_SetScaleMtx(0.8f);
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->iwork[1], this->iwork[2], this->iwork[3], 255);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aAqPearlDL);
    }
}

void Aquas_801B0F88(AqBacoon* this) {
    if ((D_i3_801C42A0[23] != 0) && (this->swork[AQ_SWK_0] < 2)) {
        this->swork[AQ_SWK_19] = 30;
        D_i3_801C4308[79] = 0.0f;
        this->swork[AQ_SWK_0] = 3;
    }
}

void Aquas_801B0FCC(AqBacoon* this) {
    D_i3_801C4308[54] = D_i3_801C4308[61] = D_i3_801C4308[68] = 0.1f;
    this->swork[AQ_SWK_19] = 500;
    D_i3_801C4308[79] = -28.0f;
}

void Aquas_801B1008(AqBacoon* this, s32 timer) {
    if ((this->swork[AQ_SWK_19] == 0) && (fabsf(D_i3_801C4308[10]) <= 1.0f) && (this->swork[AQ_SWK_0] == 0)) {
        D_i3_801C4308[79] = -28.0f;
        this->swork[AQ_SWK_19] = timer;
        this->swork[AQ_SWK_0] = 0;
        if (this->swork[AQ_SWK_22] == 0) {
            Radio_PlayMessage(gMsg_ID_15110, RCID_PEPPY);
        }
        this->swork[AQ_SWK_22]++;
        this->swork[AQ_SWK_22] &= 3;
    }

    if ((fabsf(D_i3_801C4308[10]) >= 15.0f) && (this->timer_056 == 0)) {
        this->swork[AQ_SWK_2] = this->swork[AQ_SWK_3] = 1;
        this->timer_056 = 60;
    }
}

void Aquas_AqBacoon_Init(AqBacoon* this) {
    s32 i;
    Actor* actor;

    gBossActive = true;
    gBossFrameCount = 0;

    this->health = 150;

    for (i = 0, actor = &gActors[0]; i < 2; actor++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_256;
            actor->obj.pos.x = this->obj.pos.x + D_i3_801C0098[i].x;
            actor->obj.pos.y = this->obj.pos.y + D_i3_801C0098[i].y;
            actor->obj.pos.z = this->obj.pos.z + D_i3_801C0098[i].z;
            actor->iwork[0] = i;
            i++;
            Object_SetInfo(&actor->info, actor->obj.id);
        }
    }

    D_i3_801C42A0[23] = 2;
    D_i3_801C42A0[0] = 255;
    D_i3_801C42A0[9] = D_i3_801C0058;
    D_i3_801C42A0[11] = 9;
    D_i3_801C42A0[10] = 10;
    D_i3_801C42A0[13] = 6;
    D_i3_801C42A0[14] = 11;

    this->fwork[AQ_FWK_1] = 10.0f;

    D_i3_801C4308[79] = D_i3_801C4308[10] = D_i3_801C4308[80] = D_i3_801C4308[11] = 0.0f;
    D_i3_801C4308[58] = D_i3_801C4308[65] = D_i3_801C4308[72] = 1.0f;

    this->fwork[AQ_FWK_8] = this->fwork[AQ_FWK_9] = this->fwork[AQ_FWK_10] = 1.0f;
    this->swork[AQ_SWK_14] = this->swork[AQ_SWK_15] = this->swork[AQ_SWK_16] = 255;
    this->swork[AQ_SWK_17] = 10;

    D_i3_801C42A0[1] = D_i3_801C42A0[2] = D_i3_801C42A0[4] = D_i3_801C42A0[5] =
        (D_i3_801C42A0[6] = D_i3_801C42A0[7] = 0) ^ 0; // fake

    for (i = 0; i < AQ_LIMB_MAX; i++) {
        sAqBacoonlimbTimers[i] = 0;
    }

    this->obj.pos.y += 400.0f;

    this->info.hitbox[119] = 1028.0f;
    this->info.hitbox[169] = 800.0f;

    this->swork[AQ_SWK_8] = this->swork[AQ_SWK_9] = 2;

    AUDIO_PLAY_SFX(NA_SE_EN_SHELL_BEAT, this->sfxSource, 4);
}

// OBJ_BOSS_AQ_BACOON action
#ifdef NON_MATCHING
//  unclear how to use the 4 indices
// loop at 2854 unrolls incorrectly
// sp100 shouldn't be on the stack
// https://decomp.me/scratch/M6ghQ
void Aquas_AqBacoon_Update(AqBacoon* this) {
    s32 i;
    s32 i2;
    s32 i3;
    s32 i7;
    Actor* actor;
    f32 sp110;
    f32 var_fs3;
    f32 var_fs0;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    Vec3f spD4;
    f32 temp3;
    f32 var_fs1;

    gBossFrameCount++;

    switch (this->state) {
        case 0:
            if (this->swork[AQ_SWK_21] == 0) {
                for (i2 = 0, actor = &gActors[0]; i2 < 3; actor++) {
                    if (actor->obj.status == OBJ_FREE) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_INIT;
                        actor->obj.id = OBJ_ACTOR_257;
                        actor->iwork[0] = i2;
                        Object_SetInfo(&actor->info, actor->obj.id);
                        i2++;
                    }
                }
                this->swork[AQ_SWK_21] = 1;
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                Radio_PlayMessage(gMsg_ID_15100, RCID_FOX);
            }

            if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) <= 3000.0f) {
                D_i3_801C4190[6] = 1;
                this->timer_056 = 20;
                Audio_PlaySequence(SEQ_PLAYER_BGM, NA_BGM_BOSS_AQ, 0, 1);
                this->state = 1;
            }
            break;

        case 1:
            if (this->timer_056 == 0) {
                D_i3_801C4308[14] = 80.0f;
                D_i3_801C4308[12] = D_i3_801C4308[13] = 0.0f;
                this->timer_056 = 20;
                this->state = 2;
                AUDIO_PLAY_SFX(NA_SE_BUBBLE_UP, this->sfxSource, 0);
            }
            break;

        case 2:
            Aquas_801B0FCC(this);
            if (!(this->timer_056 & 1)) {
                for (i3 = 0; i3 < 30; i3++) {
                    Aquas_Effect366_Spawn(gBosses[0].obj.pos.x + RAND_FLOAT_CENTERED(1800.0f),
                                          gBosses[0].obj.pos.y + RAND_FLOAT_CENTERED(500.0f),
                                          gBosses[0].obj.pos.z + 700.0f + RAND_FLOAT_CENTERED(1000.0f), 7.0f, 2);
                }
            }
            if (this->timer_056 == 0) {
                this->timer_056 = 40;
                this->state = 3;
            }
            break;

        case 3:
            Aquas_801B0FCC(this);
            Math_SmoothStepToF(&D_i3_801C4308[12], -45.0f, 0.5f, 1.0f, 0.01f);
            Math_SmoothStepToF(&D_i3_801C4308[13], 30.0f, 0.5f, 1.0f, 0.01f);
            Math_SmoothStepToAngle(&D_i3_801C4308[14], 0.0f, 1.0f, 2.0f, 0.0f);
            Math_SmoothStepToAngle(&D_i3_801C4308[15], D_i3_801C0190[this->swork[AQ_SWK_20]], 1.0f, 10, 0.0f);

            if (this->timer_056 == 0) {
                this->timer_056 = 10;
                this->swork[AQ_SWK_20]++;
                if (this->swork[AQ_SWK_20] >= 5) {
                    this->state = 4;
                }
            }
            break;

        case 4:
            Aquas_801B0FCC(this);
            Math_SmoothStepToF(&D_i3_801C4308[58], 0.25f, 0.3f, 1.0f, 0.0f);

            if (this->timer_056 == 0) {
                this->timer_056 = 20;
                this->state = 5;
            }
            break;

        case 5:
            Aquas_801B0FCC(this);
            Math_SmoothStepToF(&D_i3_801C4308[58], 0.25f, 0.3f, 1.0f, 0.0f);

            if (this->timer_056 == 0) {
                this->timer_056 = 30;
                this->state = 6;
            }
            break;

        case 6:
            Aquas_801B0FCC(this);
            if (this->timer_056 == 0) {
                this->state = 7;
            }
            break;

        case 7:
            this->swork[AQ_SWK_19] = 500;
            D_i3_801C4308[79] = -28.0f;

            Math_SmoothStepToF(&D_i3_801C4308[54], 1.0f, 0.001f, 0.01f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], 1.0f, 0.001f, 0.01f, 0.0f);

            if (D_i3_801C4308[54] >= 0.9f) {
                this->timer_056 = 20;
                D_i3_801C4308[79] = 0.0f;
                this->swork[AQ_SWK_0] = 3;
                this->state = 8;
            }
            break;

        case 8:
            if (this->timer_056 == 0) {
                this->timer_056 = 20;
                this->swork[AQ_SWK_12] = 10;
                D_i3_801C42A0[3] = 0;
                Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
                this->swork[AQ_SWK_26] = gBossFrameCount + 156;
                this->state = 9;
            }
            break;

        case 9:
            if (this->timer_056 == 0) {
                this->state = 10;
            }
            break;

        case 10:
        case 11:
        case 12:
            Aquas_801B1008(this, 500);
            break;

        case 13:
            Aquas_801B1008(this, 60);
            break;

        case 14:
            if (this->timer_056 == 58) {
                AUDIO_PLAY_SFX(NA_SE_EN_SHELL_FILLOPEN, this->sfxSource, 4);
            }
            if ((this->timer_056 == 0) && (D_i3_801C4308[12] <= -44.0f)) {
                this->swork[AQ_SWK_2] = this->swork[AQ_SWK_3] = 20;
                this->state = 15;
            }
            if (this->timer_056 == 40) {
                Radio_PlayMessage(gMsg_ID_15140, RCID_PEPPY);
            }
            break;

        case 15:
            if (this->swork[AQ_SWK_2] == 0) {
                this->swork[AQ_SWK_2] = 100 + RAND_INT(50.0f);
            }
            if (this->swork[AQ_SWK_3] == 0) {
                this->swork[AQ_SWK_3] = 100 + RAND_INT(50.0f);
            }
            break;

        case 16:
            D_ctx_801779A8[0] = 20.0f;

            if (gCameraShake == 0) {

                gFillScreenAlpha = gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlphaTarget = 255;

                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 25;
                gCameraShake = 20 + RAND_FLOAT(20);
            }

            if (gCameraShake == 29) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
            }

            Math_SmoothStepToF(&D_i3_801C41B8[25], D_bg_8015F970, 1.0f, 100, 0.f);
            Math_SmoothStepToF(&D_i3_801C41B8[26], 128.0f, 1.0f, 100, 0.f);

            for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
                if (sAqBacoonlimbTimers[i3] == 0) {
                    sAqBacoonlimbTimers[i3] = 100;
                }
            }

            if (D_i3_801C42A0[7] == 0) {
                D_i3_801C42A0[1] = D_i3_801C42A0[2] = D_i3_801C42A0[4] = D_i3_801C42A0[5] = D_i3_801C42A0[6] =
                    D_i3_801C42A0[7] = 50;
            }
            if (((gGameFrameCount % 2) == 0)) {
                Effect_Effect390_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                                       this->obj.pos.y + 400.0f + RAND_FLOAT_CENTERED(400.0f),
                                       this->obj.pos.z + 1000.0f + RAND_FLOAT_CENTERED(800.0f), this->vel.x,
                                       this->vel.y, this->vel.z, 0.5f, 10);
                func_effect_8007D0E0(this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                                     this->obj.pos.y + 200.0f + RAND_FLOAT_CENTERED(400.0f),
                                     this->obj.pos.z + 1000.0f + RAND_FLOAT_CENTERED(800.0f), 10.0f);
            }

            if (i3 && i3) {} //! FAKE

            for (i3 = 0; i3 < 3; i3++) {
                func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                                     this->obj.pos.y + 200.0f + RAND_FLOAT_CENTERED(200.0f),
                                     this->obj.pos.z + 1000.0f + RAND_FLOAT_CENTERED(800.0f), 3.0f + RAND_FLOAT(3.0f),
                                     5);
            }

            if (this->timer_056 == 0) {
                gEffects[98].obj.status = OBJ_FREE;
                gEffects[99].obj.status = OBJ_FREE;
                Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 600.0f, 40.0f);
                this->timer_056 = 50;

                for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
                    sAqBacoonlimbTimers[i3] = 100;
                }

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                this->state = 17;
            }
            break;

        case 17:
            if (this->timer_056 == 20) {
                gEffects[96].obj.status = OBJ_FREE;
                gEffects[97].obj.status = OBJ_FREE;
                Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 600.0f, 80.0f);
            }

            D_i3_801C42A0[0] -= 4;
            if (D_i3_801C42A0[0] < 0) {
                D_i3_801C42A0[0] = 0;
            }

            for (i3 = 0; i3 < 21; i3++) {
                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], 0.1f, 0.1f, 1.0f, 0.0f);
            }

            Math_SmoothStepToF(&this->fwork[AQ_FWK_8], 0.1f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[AQ_FWK_9], 0.1f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[AQ_FWK_10], 0.1f, 0.1f, 1.0f, 0.0f);

            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect390_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                                       this->obj.pos.y + 400.0f + RAND_FLOAT_CENTERED(400.0f),
                                       this->obj.pos.z + 1000.0f + RAND_FLOAT_CENTERED(800.0f), this->vel.x,
                                       this->vel.y, this->vel.z, 0.7f, 15);
            }

            if (this->timer_056 == 1) {
                for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
                    if (i3 != AQ_LIMB_27) {
                        sAqBacoonlimbTimers[i3] = 1000;
                    }
                }
            }
            if (this->timer_056 == 0) {
                this->timer_056 = 300;
                this->state = 18;
            }
            break;

        case 18:
            if (this->timer_056 != 0) {
                for (i3 = 0; i3 < 30; i3++) {
                    Aquas_Effect366_Spawn(gBosses[0].obj.pos.x + RAND_FLOAT_CENTERED(1800.0f),
                                          gBosses[0].obj.pos.y + RAND_FLOAT_CENTERED(500.0f),
                                          gBosses[0].obj.pos.z + 700.0f + RAND_FLOAT_CENTERED(1000.0f), 7.0f, 2);
                }
            }
            break;
    }

    switch (this->swork[AQ_SWK_0]) {
        case 0:
            if (D_i3_801C42A0[23] == 0) {
                D_i3_801C4308[79] = -180.0f;
            } else {
                Math_SmoothStepToF(&D_i3_801C4308[79], 0.0f, 0.05f, 0.2f, 0.0f);
            }
            Math_SmoothStepToF(&D_i3_801C4308[10], D_i3_801C4308[79], 0.05f, 0.3f, 0.0f);
            break;

        case 1:
            Math_SmoothStepToF(&D_i3_801C4308[10], -28.0f, 0.05f, 0.3f, 0.0f);
            if (this->timer_052 < 3) {
                Aquas_801B0F88(this);
            }
            break;

        case 2:
            break;

        case 3:
            Math_SmoothStepToF(&D_i3_801C4308[10], D_i3_801C4308[79], 0.5f, 10.0f, 0.0f);
            if (fabsf(D_i3_801C4308[10]) <= 5.0f) {
                this->swork[AQ_SWK_0] = 0;
                this->timer_052 = 0;
                this->swork[AQ_SWK_19] = 500;
                D_i3_801C4308[79] = 0.0f;

                AUDIO_PLAY_SFX(NA_SE_EN_SHELL_CLOSE, this->sfxSource, 4);

                if (this->state < 14) {
                    for (i3 = 0, actor = &gActors[0]; i3 < ARRAY_COUNT(gActors); i3++, actor++) {
                        if ((actor->obj.id == OBJ_ACTOR_AQ_GAROA) && (actor->obj.status == OBJ_ACTIVE)) {
                            actor->iwork[0] = 1;
                        }
                    }
                    this->timer_058 = 30;
                    this->swork[AQ_SWK_0] = 4;
                    gCameraShake = 50;
                    AUDIO_PLAY_SFX(NA_SE_WATER_PRESSURE, this->sfxSource, 0);
                    func_enmy_80062B60(this->obj.pos.x, this->obj.pos.z + 800.0f, 0, 100.0f);
                    var_fs3 = 80.0f;

                    for (i2 = 0; i2 < 3; i2++, var_fs3 += 10.0f) {
                        for (i3 = 0; i3 < 9; i3++) {
                            var_fs0 = SIN_DEG((27 + 2 * i3) * (10.0f + 3 * i2)) * var_fs3 * 10.0f;
                            var_fs1 = COS_DEG((27 + 2 * i3) * (10.0f + 3 * i2)) * var_fs3 * 10.0f;
                            temp3 = gGroundHeight + 30.0f;
                            Effect_Effect364_Spawn(this->obj.pos.x + var_fs0, temp3,
                                                   this->obj.pos.z + 1000.0f + var_fs1, 20.0f);
                        }
                    }
                }
            }
            break;

        case 4:
            this->swork[AQ_SWK_19] = 50;
            Math_SmoothStepToF(&D_i3_801C4308[10], D_i3_801C4308[79], 0.5f, 5.0f, 0.0f);
            if (this->timer_058 > 10) {
                Math_SmoothStepToF(D_ctx_801779A8, 20.0f, 1.0f, 5.0f, 0.0f);
            }
            if (this->timer_058 != 0) {
                gPlayer[0].boostCooldown = 1;
                Math_SmoothStepToF(&D_i3_801C41B8[24], 20.0f, 0.1f, 1.0f, 0.0f);
                Math_SmoothStepToF(&gPlayer[0].camDist, 180.0f, 0.4f, 20.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&D_i3_801C41B8[24], 0.0f, 0.01f, 0.1f, 0.0f);
                Math_SmoothStepToF(&gPlayer[0].camDist, 0.0f, 0.1f, 2.0f, 0.0f);
                if (gPlayer[0].camDist < 0.1f) {
                    gPlayer[0].boostCooldown = 0;
                    gPlayer[0].camDist = D_i3_801C41B8[24] = 0.0f;
                    this->swork[AQ_SWK_0] = 0;
                }
            }
            break;
    }

    Math_SmoothStepToF(&D_i3_801C4308[80], 0.0f, 1.0f, 2.0f, 0);
    Math_SmoothStepToF(&D_i3_801C4308[11], D_i3_801C4308[80], 0.1f, 2.0f, 0);

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (fabsf(D_i3_801C4308[10]) >= 5.0f) {
            switch (this->dmgPart) {
                case 13:
                    if ((this->swork[AQ_SWK_12] != 0) && (this->state >= 15)) {
                        if (D_i3_801C42A0[23] == 0) {
                            sAqBacoonlimbTimers[AQ_LIMB_9] = D_i3_801C42A0[3] = 50;
                            D_i3_801C42A0[22] = 0;
                            this->swork[AQ_SWK_12]--;
                            this->swork[AQ_SWK_13] = 70;
                            AUDIO_PLAY_SFX(NA_SE_EN_EYEFILM_DAMAGE, this->sfxSource, 4);
                        }
                    } else if (this->state >= 10) {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    }
                    break;

                case 14:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if ((this->state >= 15) && (this->swork[AQ_SWK_8] != 0)) {
                            D_i3_801C42A0[1] = 50;
                            sAqBacoonlimbTimers[AQ_LIMB_7] = 50;
                            this->swork[AQ_SWK_8]--;
                            AUDIO_PLAY_SFX(NA_SE_EN_WT_DAMAGE_S, this->sfxSource, 4);
                            if (this->swork[AQ_SWK_8] == 0) {
                                spD4.x = D_i3_801C4308[73];
                                spD4.y = D_i3_801C4308[74];
                                spD4.z = D_i3_801C4308[75]; // 74?
                                Effect_SpawnTimedSfxAtPos(&spD4, NA_SE_EN_WT_DISAPPEAR_L);
                                this->swork[AQ_SWK_10] = 250.0f + RAND_FLOAT(50.0f);
                            }
                        }
                    }
                    break;

                case 15:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if ((this->state >= 15) && (this->swork[AQ_SWK_9] != 0)) {
                            D_i3_801C42A0[2] = 50;
                            sAqBacoonlimbTimers[AQ_LIMB_8] = 50;
                            this->swork[AQ_SWK_9]--;
                            AUDIO_PLAY_SFX(NA_SE_EN_WT_DAMAGE_S, this->sfxSource, 4);
                            if (this->swork[AQ_SWK_9] == 0) {
                                spD4.x = D_i3_801C4308[76];
                                spD4.y = D_i3_801C4308[77]; // 76?
                                spD4.z = D_i3_801C4308[78];
                                Effect_SpawnTimedSfxAtPos(&spD4, NA_SE_EN_WT_DISAPPEAR_L);
                                this->swork[AQ_SWK_11] = 250.0f + RAND_FLOAT(50.0f);
                            }
                        }
                    }
                    break;

                case 16:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if (this->state >= 15) {
                            D_i3_801C42A0[4] = 75;
                        }
                    }
                    break;

                case 17:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if (this->state >= 15) {
                            D_i3_801C42A0[5] = 75;
                        }
                    }
                    break;

                case 18:
                    if ((this->damage == 31) && (this->swork[AQ_SWK_1] != 2) && (this->swork[AQ_SWK_12] == 0) &&
                        (this->state == 15) && (this->health != 0)) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else {
                            for (i7 = 0; i7 < AQ_LIMB_MAX; i7++) {
                                sAqBacoonlimbTimers[i7] = 50;
                            }
                            D_i3_801C42A0[1] = D_i3_801C42A0[2] = D_i3_801C42A0[4] = D_i3_801C42A0[5] =
                                D_i3_801C42A0[6] = D_i3_801C42A0[7] = 50;

                            this->swork[AQ_SWK_13] = 40;
                            this->swork[AQ_SWK_1] = 2;
                            AUDIO_PLAY_SFX(NA_SE_EN_SHELL_DAMAGE, this->sfxSource, 4);
                            this->health -= this->damage;
                            if ((this->swork[AQ_SWK_25] == 0) || (this->swork[AQ_SWK_25] == 2)) {
                                Radio_PlayMessage(gMsg_ID_7086, RCID_SLIPPY);
                            }
                            this->swork[AQ_SWK_25]++;
                            if (this->health <= 0) {
                                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                                Boss_AwardBonus(this);
                                Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
                                gTeamLowHealthMsgTimer = -1;
                                if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) ||
                                    (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
                                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                                    gPlayer[0].csState = 0;
                                }
                                D_i3_801C4190[1] = 0;
                                D_i3_801C4190[5] = 0;
                                D_i3_801C4190[3] = 0;
                                D_i3_801C4190[4] = 0;
                                D_i3_801C4190[0] = 0;
                                this->health = 0;
                                this->swork[AQ_SWK_13] = 40;
                                this->swork[AQ_SWK_1] = 2;
                                this->timer_056 = 50;
                                AUDIO_PLAY_SFX(NA_SE_EN_SHELL_DOWN, this->sfxSource, 4);
                                gShowBossHealth = false;
                                this->state = 16;
                            }
                        }
                    }
                    break;

                case 19:
                case 20:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if (this->state >= 15) {
                            D_i3_801C42A0[6] = 50;
                        }
                    }
                    break;

                default:
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    break;
            }
        }
    }

    if (this->state >= 15) {
        switch (this->swork[AQ_SWK_1]) {
            case 0:
                Math_SmoothStepToF(&D_i3_801C4308[12], -45.0f, 1.0f, this->fwork[AQ_FWK_1], 0.01f);
                Math_SmoothStepToF(&D_i3_801C4308[13], 30.0f, 1.0f, this->fwork[AQ_FWK_1], 0.01f);

                if ((this->timer_050 == 0) && (*(&D_i3_801C4308[12]) == -45.0f)) {
                    this->timer_050 = 7;
                    this->swork[AQ_SWK_1]++;
                }
                break;

            case 1:
                var_fs0 = 2.0f * this->fwork[AQ_FWK_1];
                Math_SmoothStepToF(&D_i3_801C4308[12], 0.0f, 1.0f, var_fs0, 0.0001f);
                Math_SmoothStepToF(&D_i3_801C4308[13], 0.0f, 1.0f, var_fs0, 0.0001f);
                if (this->timer_050 == 0) {
                    this->swork[AQ_SWK_1] = 0;
                    this->timer_050 = 40.0f - ((this->health - 150) / 5.0f);
                }
                break;

            case 2:
                if (D_i3_801C42A0[7] != 0) {
                    Math_SmoothStepToF(&D_i3_801C4308[12], -80.0f, 1.0f, 10.0f, 0.0001f);
                    Math_SmoothStepToF(&D_i3_801C4308[13], 30.0f, 1.0f, 10.0f, 0.0001f);
                } else {
                    this->timer_050 = 50;
                    this->swork[AQ_SWK_1] = 0;
                }
                break;
        }
    }

    this->swork[AQ_SWK_14] += D_i3_801C0150[this->swork[AQ_SWK_18]][0];
    this->swork[AQ_SWK_15] += D_i3_801C0150[this->swork[AQ_SWK_18]][1];
    this->swork[AQ_SWK_16] += D_i3_801C0150[this->swork[AQ_SWK_18]][2];

    if (this->swork[AQ_SWK_14] < 0) {
        this->swork[AQ_SWK_14] = 0;
    }
    if (this->swork[AQ_SWK_15] < 0) {
        this->swork[AQ_SWK_15] = 0;
    }
    if (this->swork[AQ_SWK_16] < 0) {
        this->swork[AQ_SWK_16] = 0;
    }
    if (this->swork[AQ_SWK_17] == 0) {
        this->swork[AQ_SWK_17] = 10;
        this->swork[AQ_SWK_18]++;
        this->swork[AQ_SWK_18] &= 3;
    }

    if ((this->state >= 4) && (this->state < 16)) {
        sp104 = gPlayer[0].pos.x - this->obj.pos.x;
        sp100 = gPlayer[0].pos.y - this->obj.pos.y;
        spFC = gPlayer[0].trueZpos - this->obj.pos.z;
        spE8 = Math_RadToDeg(Math_Atan2F(sp104, spFC));
        // spEC = sqrtf(SQ(sp104) + SQ(spFC));
        spE4 = Math_RadToDeg(-Math_Atan2F(sp100, sqrtf(SQ(sp104) + SQ(spFC))));
        if ((spE8 <= 40.0f) || (spE8 >= 320.0f)) {
            Math_SmoothStepToAngle(&D_i3_801C4308[15], spE8, 1.0f, 5.0f, 0.001f);
        }
        if ((spE4 <= 30.0f) || (spE4 >= 330.0f)) {
            Math_SmoothStepToAngle(&D_i3_801C4308[14], spE4, 1.0f, 5.0f, 0.001f);
        }
    }

    for (i3 = 0; i3 < 6; i3++) {
        if ((D_i3_801C42A0[i3 + 1] == 0) && (this->state < 17)) {
            if ((i3 + 1 != this->swork[AQ_SWK_6]) && (i3 + 1 != this->swork[AQ_SWK_7])) {
                i2 = D_i3_801C42A0[i3 + 16];

                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], D_i3_801BFC94[4 * i3 + i2].x, D_i3_801BFE18[4 * i3 + i2].x,
                                   D_i3_801BFF38[4 * i3 + i2].x, 0.00001f);
                Math_SmoothStepToF(&D_i3_801C4308[59 + i3], D_i3_801BFC94[4 * i3 + i2].y, D_i3_801BFE18[4 * i3 + i2].y,
                                   D_i3_801BFF38[4 * i3 + i2].y, 0.00001f);
                Math_SmoothStepToF(&D_i3_801C4308[66 + i3], D_i3_801BFC94[4 * i3 + i2].z, D_i3_801BFE18[4 * i3 + i2].z,
                                   D_i3_801BFF38[4 * i3 + i2].z, 0.00001f);

                D_i3_801C42A0[i3 + 10]++;
                if (D_i3_801C42A0[i3 + 10] >= D_i3_801BFDB4[4 * i3 + i2]) {
                    D_i3_801C42A0[i3 + 16]++;
                    if ((D_i3_801C42A0[i3 + 16] >= 4) || (D_i3_801BFDB4[4 * i3 + D_i3_801C42A0[i3 + 16]] == 100000)) {
                        D_i3_801C42A0[i3 + 10] = 0;
                        D_i3_801C42A0[i3 + 16] = 0;
                    }
                }
            }
        }
    }

    spF4 = gPlayer[0].pos.y - D_i3_801C4308[77];
    spF8 = gPlayer[0].pos.x - D_i3_801C4308[76];
    spF0 = gPlayer[0].trueZpos - D_i3_801C4308[78];
    sp104 = gPlayer[0].pos.x - D_i3_801C4308[73];
    sp100 = gPlayer[0].pos.y - D_i3_801C4308[74];
    spFC = gPlayer[0].trueZpos - D_i3_801C4308[75];

    spE8 = Math_RadToDeg(Math_Atan2F(sp104, spFC));
    spE0 = Math_RadToDeg(Math_Atan2F(spF8, spF0));
    spFC = sqrtf(SQ(sp104) + SQ(spFC));
    spF0 = sqrtf(SQ(spF8) + SQ(spF0));
    spE4 = Math_RadToDeg(-Math_Atan2F(sp100, spFC));
    spEC = Math_RadToDeg(-Math_Atan2F(spF4, spF0));

    if ((spE8 <= 15.0f) || (spE8 >= 310.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[18], spE8, 1.0f, 5.0f, 0.001f);
    }
    if ((spE4 <= 12.0f) || (spE4 >= 330.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[16], spE4, 1.0f, 5.0f, 0.001f);
    }
    if ((spE0 <= 20.0f) || (spE0 >= 315.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[19], spE0, 1.0f, 5.0f, 0.001f);
    }
    if ((spEC <= 12.0f) || (spEC >= 330.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[17], spEC, 1.0f, 5.0f, 0.001f);
    }

    if ((this->swork[AQ_SWK_2] == 1) && (this->swork[AQ_SWK_8] != 0) && (this->health != 0) &&
        (this->swork[AQ_SWK_6] == 0)) {
        D_i3_801C42A0[10] = D_i3_801C42A0[16] = 0;
        this->swork[AQ_SWK_6] = 1;
    }
    if ((this->swork[AQ_SWK_3] == 1) && (this->swork[AQ_SWK_9] != 0) && (this->health != 0) &&
        (this->swork[AQ_SWK_7] == 0)) {
        D_i3_801C42A0[11] = D_i3_801C42A0[17] = 0;
        this->swork[AQ_SWK_7] = 2;
    }

    if (this->health != 0) {
        for (i7 = 0; i7 < 2; i7++) {
            if (this->swork[AQ_SWK_6 + i7] != 0) {
                i2 = this->swork[AQ_SWK_4 + i7];

                Math_SmoothStepToF(&D_i3_801C4308[52 + i7], D_i3_801C00B0[0][i2], D_i3_801C00F0[0][i2],
                                   D_i3_801C0120[0][i2], 0.00001f);
                Math_SmoothStepToF(&D_i3_801C4308[59 + i7], D_i3_801C00B0[1][i2], D_i3_801C00F0[1][i2],
                                   D_i3_801C0120[1][i2], 0.00001f);
                Math_SmoothStepToF(&D_i3_801C4308[66 + i7], D_i3_801C00B0[2][i2], D_i3_801C00F0[2][i2],
                                   D_i3_801C0120[2][i2], 0.00001f);

                D_i3_801C42A0[i7 + 10]++;
                if (D_i3_801C42A0[i7 + 10] >= D_i3_801C00E0[i2]) {
                    this->swork[AQ_SWK_4 + i7]++;
                    if (this->swork[AQ_SWK_4 + i7] == 2) {
                        i = 4;
                        if (D_i3_801C42A0[23] == 0) {

                            i = ((160 - this->health) / 10) + 10;
                            if (this->health < 31) {
                                i += 10;
                            }
                            if (i > 40) {
                                i = 40;
                            }
                        }
                        spD4.x = D_i3_801C4308[73 + 3 * i7];
                        spD4.y = D_i3_801C4308[74 + 3 * i7];
                        spD4.z = D_i3_801C4308[75 + 3 * i7];

                        Effect_SpawnTimedSfxAtPos(&spD4, NA_SE_EN_P_BALL_SHOT);

                        i2 = 0;
                        for (i3 = 0; (i2 <= i) && (i3 < ARRAY_COUNT(gActors)); i3++) {
                            if ((gActors[i3].obj.status == OBJ_FREE) && (i3 < ARRAY_COUNT(gActors))) {
                                Actor_Initialize(&gActors[i3]);

                                gActors[i3].obj.status = OBJ_INIT;
                                gActors[i3].obj.id = OBJ_ACTOR_AQ_PEARL;
                                gActors[i3].obj.pos.x = D_i3_801C4308[73 + 3 * i7];
                                gActors[i3].obj.pos.y = D_i3_801C4308[74 + 3 * i7] + 30.0f;
                                gActors[i3].obj.pos.z = D_i3_801C4308[75 + 3 * i7] + 150.0f;

                                if (Rand_ZeroOne() < 0.5f) {
                                    var_fs1 = Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(60.0f), 360.0f);
                                    var_fs0 = Math_ModF(D_i3_801C4308[i7 + 18] + RAND_FLOAT_CENTERED(60.0f), 360.0f);
                                    if (this->health < 61) {
                                        if (i7 == 0) {
                                            var_fs1 =
                                                Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                            var_fs0 = Math_ModF(
                                                D_i3_801C4308[i7 + 18] - 30.0f + RAND_FLOAT_CENTERED(20.0f), 360.0f);
                                        } else {
                                            var_fs1 =
                                                Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                            var_fs0 = Math_ModF(
                                                D_i3_801C4308[i7 + 18] + 30.0f + RAND_FLOAT_CENTERED(20.0f), 360.0f);
                                        }
                                    }
                                } else {
                                    var_fs1 = Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                    var_fs0 = Math_ModF(D_i3_801C4308[i7 + 18] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                }

                                gActors[i3].fwork[3] = var_fs1;
                                gActors[i3].fwork[4] = var_fs0;
                                // gActors[i3].timer_0BC = i2 * 3;
                                gActors[i3].timer_0BC = i2;
                                gActors[i3].timer_0BC *= 3; // nonmatching, but helps elsewhere
                                gActors[i3].fwork[1] = D_i3_801C4308[i7 + 16];
                                gActors[i3].fwork[2] = D_i3_801C4308[i7 + 18];
                                Object_SetInfo(&gActors[i3].info, gActors[i3].obj.id);
                                if (i3 >= ARRAY_COUNT(gActors)) {
                                    gActors[i3].obj.status = OBJ_FREE;
                                }
                                i2++;
                            }
                        }
                    }
                    if (this->swork[AQ_SWK_4 + i7] >= 4) {
                        D_i3_801C42A0[10 + i7] = this->swork[AQ_SWK_6 + i7] = this->swork[AQ_SWK_4 + i7] = 0;
                    }
                }
            }
        }
    }

    for (i7 = 26; i7 < 107; i7 += 10) {
        var_fs0 = D_i3_801C4308[10] - 10;
        if (fabsf(D_i3_801C4308[10]) <= 5.0f) {
            var_fs0 = 0.0f;
        }
        this->info.hitbox[i7] = var_fs0;
    }

    if (this->state >= 10) {
        sp110 = D_i3_801C42A0[9];
        i2 = (gGameFrameCount & 0x1F); // % 0x20 if possible
        if (sAqBacoonlimbTimers[AQ_LIMB_9] != 0) {
            Math_SmoothStepToF(&sp110, 255.0f, 1.0f, 10, 0.0001f);
        } else if ((i2 & 0x10) == 0) {
            Math_SmoothStepToF(&sp110, D_i3_801C005C, 1.0f, 10, 0.0001f);
        } else {
            Math_SmoothStepToF(&sp110, D_i3_801C0058, 1.0f, 10, 0.0001f);
        }
        D_i3_801C42A0[9] = sp110;
    }

    if (D_i3_801C42A0[7] != 0) {
        Math_SmoothStepToF(&D_ctx_801779A8[0], 20.0f, 1.0f, 5.0f, 0);
    }

    for (i2 = 45, i3 = 1, i7 = 0; i7 < 14; i3++, i2++, i7 += 2) {
        if (D_i3_801C42A0[i3] != 0) {
            D_i3_801C4308[i2] = SIN_DEG(D_i3_801C0060[i7 + 0] * D_i3_801C42A0[i3]) *
                                Aquas_801A958C(D_i3_801C42A0[i3], D_i3_801C0060[i7 + 1]);
            D_i3_801C42A0[i3]--;
        }
    }

    if (this->swork[AQ_SWK_12] != 0) {
        if (D_i3_801C42A0[3] != 0) {
            var_fs3 = 1.0f;
            if (D_i3_801C42A0[22] < 4) {
                var_fs3 = 1.2f;
            }
            Math_SmoothStepToF(&D_i3_801C4308[54], var_fs3, 0.3f, 1.0f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], var_fs3, 0.3f, 1.0f, 0.0f);
            D_i3_801C42A0[22]++;
            if (D_i3_801C42A0[22] >= 9) {
                D_i3_801C42A0[22] = 0;
            }
        }
    } else {
        D_i3_801C42A0[3] = 10;
        if (this->swork[AQ_SWK_13] != 0) {
            Math_SmoothStepToF(&D_i3_801C4308[54], 0.0f, 0.3f, 0.5f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], 0.0f, 0.3f, 0.5f, 0.0f);
            this->info.hitbox[119] = -10000.0f;
            if (this->swork[AQ_SWK_13] == 1) {
                AUDIO_PLAY_SFX(NA_SE_EN_EYEFILM_REVIVAL, this->sfxSource, 4);
            }
        } else if ((this->health != 0) || (this->state < 16)) {
            Math_SmoothStepToF(&D_i3_801C4308[54], 1.0f, 0.3f, 0.5f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], 1.0f, 0.3f, 0.5f, 0.0f);
            if (D_i3_801C4308[61] >= 0.9f) {
                this->swork[AQ_SWK_12] = 10;
                this->info.hitbox[119] = 1028.0f;
            }
        } else {
            Math_SmoothStepToF(&D_i3_801C4308[54], 0, 0.1f, 10, 0);
            Math_SmoothStepToF(&D_i3_801C4308[61], 0, 0.1f, 10.0f, 0);
            D_i3_801C42A0[9] -= 5;
            if (D_i3_801C42A0[9] < 0) {
                D_i3_801C42A0[9] = 0;
            }
        }
    }

    if ((D_i3_801C42A0[7] != 0) || (this->state >= 16)) {
        var_fs3 = 0.25f;
    } else {
        var_fs3 = 1.0f;
    }

    Math_SmoothStepToF(&D_i3_801C4308[58], var_fs3, 0.3f, 1.0f, 0);

    for (i3 = 0; i3 < 2; i3++) {
        if (this->swork[AQ_SWK_8 + i3] == 0) {
            if (this->swork[AQ_SWK_10 + i3] == 1) {
                spD4.x = D_i3_801C4308[73 + 3 * i3];
                spD4.y = D_i3_801C4308[74 + 3 * i3];
                spD4.z = D_i3_801C4308[75 + 3 * i3];
                Effect_SpawnTimedSfxAtPos(&spD4, NA_SE_EN_P_GUN_APPEAR);
            }

            if ((fabsf(D_i3_801C4308[10]) <= 3.0f) || (this->swork[AQ_SWK_10 + i3] == 0)) {
                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], 1.0f, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[59 + i3], 1.0f, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[66 + i3], 1.0f, 0.1f, 0.5f, 0.0f);
                if (D_i3_801C4308[i3 + 66] >= 0.9f) {
                    for (i = 0; i < 3; i++) {
                        spD4.x = D_i3_801C4308[73 + 3 * i3] + RAND_FLOAT(i * 200.0f);
                        spD4.y = D_i3_801C4308[74 + 3 * i3] + RAND_FLOAT(i * 200.0f);
                        spD4.z = D_i3_801C4308[75 + 3 * i3] + RAND_FLOAT(i * 400.0f);
                        Aquas_SpawnItem(&spD4, OBJ_ITEM_SILVER_RING);
                    }
                    this->swork[AQ_SWK_8 + i3] = 2;
                }
            } else {
                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], 0, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[59 + i3], 0, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[66 + i3], 0, 0.1f, 0.5f, 0.0f);
                D_i3_801C42A0[i3 + 1] = 50;
            }
        }
    }

    if (this->swork[AQ_SWK_2] != 0) {
        this->swork[AQ_SWK_2]--;
    }
    if (this->swork[AQ_SWK_3] != 0) {
        this->swork[AQ_SWK_3]--;
    }
    if (this->swork[AQ_SWK_10] != 0) {
        this->swork[AQ_SWK_10]--;
    }
    if (this->swork[AQ_SWK_11] != 0) {
        this->swork[AQ_SWK_11]--;
    }
    if (this->swork[AQ_SWK_13] != 0) {
        this->swork[AQ_SWK_13]--;
    }
    if (this->swork[AQ_SWK_17] != 0) {
        this->swork[AQ_SWK_17]--;
    }
    if (this->swork[AQ_SWK_19] != 0) {
        this->swork[AQ_SWK_19]--;
    }
    if (this->swork[AQ_SWK_26] == gBossFrameCount) {
        gShowBossHealth = true;
    }
    if (this->swork[AQ_SWK_26] < gBossFrameCount) {
        gBossHealthBar = (this->health / 150.0f) * 255.0f;
    }
}
#else
void Aquas_AqBacoon_Update(AqBacoon* this);
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/overlays/ovl_i3/fox_aq/Aquas_AqBacoon_Update.s")
#endif

bool Aquas_AqBacoon_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Vec3f sp6C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp60;
    f32 sp5C = 0.0f;
    f32 sp58 = 0.0f;
    f32 sp54 = 0.0f;
    s32 sp50 = false;
    Boss* this = thisx;

    if (sAqBacoonlimbTimers[limbIndex] >= 1000) {
        *dList = NULL;
    } else if ((sAqBacoonlimbTimers[limbIndex] != 0) && (gPlayState != PLAY_PAUSE)) {
        sAqBacoonlimbTimers[limbIndex]--;
    }

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    if ((D_i3_801C42A0[0] != 255) && (limbIndex != 27)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_58);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, D_i3_801C42A0[0]);
    } else if ((sAqBacoonlimbTimers[limbIndex] % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    } else {
        sp50 = true;
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    switch (limbIndex) {
        case AQ_LIMB_4:
            rot->x = D_i3_801C4308[13];
            sp5C = this->fwork[AQ_FWK_8];
            sp58 = this->fwork[AQ_FWK_9];
            sp54 = this->fwork[AQ_FWK_10];
            break;

        case AQ_LIMB_5:
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, gBosses[0].swork[AQ_SWK_14], gBosses[0].swork[AQ_SWK_15],
                            gBosses[0].swork[AQ_SWK_16], 255);
            rot->x = D_i3_801C4308[14];
            rot->y = D_i3_801C4308[15];
            pos->z = 40.0f;
            sp5C = D_i3_801C4308[58];
            sp58 = D_i3_801C4308[65];
            sp54 = D_i3_801C4308[72];
            break;

        case AQ_LIMB_6:
            rot->x = D_i3_801C4308[12];
            sp5C = this->fwork[AQ_FWK_8];
            sp58 = this->fwork[AQ_FWK_9];
            sp54 = this->fwork[AQ_FWK_10];
            break;

        case AQ_LIMB_7:
            rot->x = D_i3_801C4308[16];
            rot->y = D_i3_801C4308[18];
            rot->x += D_i3_801C4308[45];
            rot->y += D_i3_801C4308[45];
            rot->z += D_i3_801C4308[45];
            sp5C = D_i3_801C4308[52];
            sp58 = D_i3_801C4308[59];
            sp54 = D_i3_801C4308[66];
            break;

        case AQ_LIMB_8:
            rot->x = D_i3_801C4308[17];
            rot->y = D_i3_801C4308[19];
            rot->x += D_i3_801C4308[46];
            rot->y += D_i3_801C4308[46];
            rot->z += D_i3_801C4308[46];
            sp5C = D_i3_801C4308[53];
            sp58 = D_i3_801C4308[60];
            sp54 = D_i3_801C4308[67];
            break;

        case AQ_LIMB_9:
            rot->x += D_i3_801C4308[47];
            rot->y += D_i3_801C4308[47];
            rot->z += D_i3_801C4308[47];

            sp5C = D_i3_801C4308[54];
            sp58 = D_i3_801C4308[61];
            sp54 = D_i3_801C4308[68];

            if (sp50) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_61);
                if (gBosses[0].health != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;

        case AQ_LIMB_10:
            rot->x += D_i3_801C4308[48];
            rot->y += D_i3_801C4308[48];
            rot->z += D_i3_801C4308[48];
            sp5C = D_i3_801C4308[55];
            sp58 = D_i3_801C4308[62];
            sp54 = D_i3_801C4308[69];
            break;

        case AQ_LIMB_12:
            rot->x = D_i3_801C4308[14];
            rot->y = D_i3_801C4308[15];
            sp5C = this->fwork[AQ_FWK_8];
            sp58 = this->fwork[AQ_FWK_9];
            sp54 = this->fwork[AQ_FWK_10];
            break;

        case AQ_LIMB_15:
            rot->x += D_i3_801C4308[49];
            rot->y += D_i3_801C4308[49];
            rot->z += D_i3_801C4308[49];
            sp5C = D_i3_801C4308[56];
            sp58 = D_i3_801C4308[63];
            sp54 = D_i3_801C4308[70];
            break;

        case AQ_LIMB_18:
            rot->y += D_i3_801C4308[50];
            rot->z += D_i3_801C4308[50];
            sp5C = D_i3_801C4308[57];
            sp58 = D_i3_801C4308[64];
            sp54 = D_i3_801C4308[71];
            break;

        case AQ_LIMB_22:
            rot->x += D_i3_801C4308[51];
            rot->y += D_i3_801C4308[51];
            rot->z += D_i3_801C4308[51];
            sp5C = this->fwork[AQ_FWK_8];
            sp58 = this->fwork[AQ_FWK_9];
            sp54 = this->fwork[AQ_FWK_10];
            break;

        case AQ_LIMB_24:
            rot->x = D_i3_801C4308[10];
            rot->z = D_i3_801C4308[11];
            break;

        case AQ_LIMB_27:
            break;
    }

    if (sp5C > 0.0f) {
        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
        if (*dList != NULL) {
            Matrix_MultVec3f(gCalcMatrix, &sp6C, &sp60);
            Display_SetSecondLight(&sp60);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, sp5C, sp58, sp54, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, *dList);
            Matrix_Pop(&gGfxMatrix);
        }
        return true;
    }
    return false;
}

void Aquas_AqBacoon_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp6C;
    Vec3f sp60 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp54 = { 340.0f, 600.0f, 1480.0f };
    Vec3f sp48 = { -640.0f, 380.0f, 1520.0f };
    Vec3f sp3C = { 760.0f, 340.0f, 1560.0f };
    Vec3f sp30 = { 130.0f, 350.0f, 130.0f };
    Vec3f sp24 = { -130.0f, 350.0f, 130.0f };

    switch (limbIndex) {
        case AQ_LIMB_5:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[21] = sp6C.x;
            D_i3_801C4308[22] = sp6C.y;
            D_i3_801C4308[23] = sp6C.z;
            break;

        case AQ_LIMB_7:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[24] = sp6C.x;
            D_i3_801C4308[25] = sp6C.y;
            D_i3_801C4308[26] = sp6C.z;
            Matrix_MultVec3f(gCalcMatrix, &sp30, &sp6C);
            D_i3_801C4308[73] = sp6C.x;
            D_i3_801C4308[74] = sp6C.y;
            D_i3_801C4308[75] = sp6C.z;
            break;

        case AQ_LIMB_8:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[27] = sp6C.x;
            D_i3_801C4308[28] = sp6C.y;
            D_i3_801C4308[29] = sp6C.z;
            Matrix_MultVec3f(gCalcMatrix, &sp24, &sp6C);
            D_i3_801C4308[76] = sp6C.x;
            D_i3_801C4308[77] = sp6C.y;
            D_i3_801C4308[78] = sp6C.z;
            break;

        case AQ_LIMB_9:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[30] = sp6C.x;
            D_i3_801C4308[31] = sp6C.y;
            D_i3_801C4308[32] = sp6C.z;
            break;

        case AQ_LIMB_10:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[33] = sp6C.x;
            D_i3_801C4308[34] = sp6C.y;
            D_i3_801C4308[35] = sp6C.z;
            break;

        case AQ_LIMB_15:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[36] = sp6C.x;
            D_i3_801C4308[37] = sp6C.y;
            D_i3_801C4308[38] = sp6C.z;
            break;

        case AQ_LIMB_18:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[39] = sp6C.x;
            D_i3_801C4308[40] = sp6C.y;
            D_i3_801C4308[41] = sp6C.z;
            break;

        case AQ_LIMB_22:
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp6C);
            D_i3_801C4308[42] = sp6C.x;
            D_i3_801C4308[43] = sp6C.y;
            D_i3_801C4308[44] = sp6C.z;
            break;

        case AQ_LIMB_24:
            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp6C);
            D_i3_801C4308[1] = sp6C.x;
            D_i3_801C4308[4] = sp6C.y;
            D_i3_801C4308[7] = sp6C.z;
            Matrix_MultVec3f(gCalcMatrix, &sp48, &sp6C);
            D_i3_801C4308[2] = sp6C.x;
            D_i3_801C4308[5] = sp6C.y;
            D_i3_801C4308[8] = sp6C.z;
            Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp6C);
            D_i3_801C4308[3] = sp6C.x;
            D_i3_801C4308[6] = sp6C.y;
            D_i3_801C4308[9] = sp6C.z;
            break;

        case AQ_LIMB_27:
            break;
    }
}

void Aquas_AqBacoon_Draw(AqBacoon* this) {
    Animation_DrawSkeleton(3, D_AQ_602BD60, this->vwork, Aquas_AqBacoon_OverrideLimbDraw, Aquas_AqBacoon_PostLimbDraw,
                           this, gCalcMatrix);
}

f32 D_i3_801C01F8[11] = {
    400.0f, 430.0f, 460.0f, 490.0f, 520.0f, 550.0f, 580.0f, 610.0f, 640.0f, 670.0f, 700.0f,
};
f32 D_i3_801C0224[11] = {
    6.0f, 6.0f, 8.0f, 8.0f, 8.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
};
Vec3f D_i3_801C0250 = { 0.0f, 0.0f, 0.0f };

bool Aquas_AqSculpin_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    AqSculpin* this = (AqSculpin*) thisx;

    if ((this->timer_0C6 % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
        if ((limbIndex > 0) && (limbIndex < 5)) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_60);
        }
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    return false;
}

void Aquas_AqSculpin_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = D_i3_801C0250;
    AqSculpin* this = (AqSculpin*) thisx;

    if (this->health == 0) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, this->vwork);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[8]);
                break;

            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                break;

            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[10]);
                break;

            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
                break;

            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[12]);
                break;

            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[13]);
                break;

            case 7:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[14]);
                break;

            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
                break;
        }
    }
}

void Aquas_AqSculpin_Draw(AqSculpin* this) {
    Vec3f jointTable[30];

    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    Animation_GetFrameData(&aAqSculpinAnim, this->animFrame, jointTable);
    Animation_DrawSkeleton(3, aAqSculpinSkel, jointTable, Aquas_AqSculpin_OverrideLimbDraw,
                           Aquas_AqSculpin_PostLimbDraw, this, gCalcMatrix);
}

f32 D_i3_801C025C[2] = { 120.0f, 0.0f };
s32 D_i3_801C0264[19] = { 0, 0, 3, 4, 0, 5, 6, 7, 1, 2, 0, 0, 0, 0, 0, 0, 8, 9, 0 };

void Aquas_AqSculpin_Update(AqSculpin* this) {
    s32 i;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    AqSculpin* sculpin;

    if ((this->health == 0) && (this->state != 0)) {
        for (i = 0; i < 5; i++) {
            func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT(i * 15.0f), this->obj.pos.y + RAND_FLOAT(i * 3.0f),
                                 this->obj.pos.z + RAND_FLOAT(i * 5.0f), 0.4f + RAND_FLOAT(0.4f), 7);
        }
        this->health = 0;
        this->state = 7;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_AQ_ZAKO_DOWN);
    }

    switch (this->state) {
        case 0:
            for (i = 0; i < 8; i++) {
                this->vwork[i].x = this->obj.pos.x;
                this->vwork[i].y = this->obj.pos.y;
                this->vwork[i].z = this->obj.pos.z;
                this->vwork[8 + i].x = this->obj.rot.x;
                this->vwork[8 + i].y = this->obj.rot.y;
                this->vwork[8 + i].z = this->obj.rot.z;
            }
            this->info.bonus = 0;
            this->health = 10;
            this->fwork[4] = 1000.0f + RAND_FLOAT_CENTERED(400.0f);
            this->state++;
            break;

        case 2:
            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos, 1.0f, 10.0f, 0);
            if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < this->fwork[4]) {
                Aquas_801A9728(this, 50.0f, 10.0f, 8);
                this->state = 3;
                this->vel.y = 30.0f;
            } else if (((gGameFrameCount % 16) == 0)) {
                Effect_Effect364_Spawn(this->obj.pos.x, gGroundHeight + 30.0f, this->obj.pos.z, 10.0f);
            }
            break;

        case 3:
            Math_SmoothStepToAngle(&this->obj.rot.x, 270.0f, 1.0f, 100.0f, 0.0001f);
            if (this->obj.rot.x == 270.0f) {
                this->iwork[1] = RAND_FLOAT(10.0f);
                this->fwork[0] = D_i3_801C01F8[this->iwork[1]];
                this->state = 4;
            }
            break;

        case 4:
            Math_SmoothStepToF(&this->vel.y, 0.0f, 1.0f, 4.0f, 0.0001f);
            this->vel.z = gPlayer[0].vel.z;
            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - this->fwork[4], 0.1f, 100.0f, 0);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[0], 1.0f, D_i3_801C0224[this->iwork[1]], 0);
            this->fwork[1] += 10.0f;
            this->vel.x = COS_DEG(this->fwork[1]) * this->iwork[1] * 0.1f;

            if ((this->fwork[0] - 1.0f) <= this->obj.pos.y) {
                this->state = 5;
            }

            if ((gGameFrameCount % 8) == 0) {
                Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                                      this->obj.pos.y + RAND_FLOAT_CENTERED(100.0f),
                                      this->obj.pos.z + RAND_FLOAT_CENTERED(100.0f), 1.0f, 1);
            }
            break;

        case 5:
            this->vel.z = gPlayer[0].vel.z;

            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 1000.0f, 0.1f, 100.0f, 0);
            Math_SmoothStepToF(&this->vel.x, 0.0f, 1.0f, 2.0f, 0.001f);
            Math_SmoothStepToAngle(&this->obj.rot.x, D_i3_801C025C[this->iwork[0]], 1.0f, 20.0f, 0);

            if (this->obj.rot.x == D_i3_801C025C[this->iwork[0]]) {
                this->iwork[0]++;
                if (this->iwork[0] >= 2) {
                    sp88.x = gPlayer[0].pos.x - this->obj.pos.x;
                    sp88.y = gPlayer[0].pos.y - this->obj.pos.y;
                    sp88.z = gPlayer[0].trueZpos - this->obj.pos.z;
                    this->fwork[2] = Math_RadToDeg(Math_Atan2F(sp88.x, sp88.z));
                    this->fwork[3] = Math_RadToDeg(-Math_Atan2F(sp88.y, sqrtf(SQ(sp88.x) + SQ(sp88.z))));
                    Matrix_RotateY(gCalcMatrix, this->fwork[2] * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->fwork[3] * M_DTOR, MTXF_APPLY);
                    sp7C.x = sp7C.y = 0.0f;
                    sp7C.z = 40.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp70);
                    this->vel.x = sp70.x;
                    this->vel.y = sp70.y;
                    this->vel.z = sp70.z;
                    this->state = 6;
                }
            }
            break;

        case 6:
            Math_SmoothStepToAngle(&this->obj.rot.x, this->fwork[3], 1.0f, 5.0f, 0);
            Math_SmoothStepToAngle(&this->obj.rot.y, this->fwork[2], 1.0f, 5.0f, 0);

            if ((gGameFrameCount % 4) == 0) {
                Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                                      this->obj.pos.y + RAND_FLOAT_CENTERED(100.0f),
                                      this->obj.pos.z + RAND_FLOAT_CENTERED(100.0f), 1.0f, 1);
            }
            break;

        case 7:
            for (i = 0; i < 8; i++) {
                Aquas_SpawnDebris(&this->vwork[i], &this->vwork[8 + i], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(5.0f),
                                  RAND_FLOAT_CENTERED(10.0f), 49, this->scale, 200, i);
                Effect_Effect362_Spawn(this->vwork[i].x, this->vwork[i].y, this->vwork[i].z + 100.0f, 6.0f);
            }
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            func_effect_800815DC();
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f);
            break;
    }

    if (this->state >= 2) {
        if (this->state < 3) {
            this->animFrame++;
        } else {
            this->animFrame += 3;
        }
        if (this->animFrame >= Animation_GetFrameCount(&aAqSculpinAnim)) {
            this->animFrame = 0;
        }
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->health != 0) {
            if (this->damage == 31) {
                this->info.bonus = 1;
                this->health -= this->damage;
                if (this->health <= 0) {
                    this->health = 0;
                }
            } else if (this->damage == 30) {
                for (i = 0, sculpin = &gActors[0]; i < ARRAY_COUNT(gActors); i++, sculpin++) {
                    if ((sculpin->obj.status == OBJ_ACTIVE) && (sculpin->obj.id == OBJ_ACTOR_AQ_SCULPIN) &&
                        (sculpin->state == 1) && (i != this->index) &&
                        (fabsf(sculpin->obj.pos.x - this->obj.pos.x) <= 300.0f) &&
                        (fabsf(sculpin->obj.pos.z - this->obj.pos.z) <= 300.0f)) {
                        sculpin->state = 2;
                    }
                }
            } else if ((this->state >= 3) && (this->state < 5)) {
                this->info.bonus = 1;
                this->timer_0C6 = 15;
                this->health -= this->damage;
                if (this->health <= 0) {
                    this->health = 0;
                }
            }
        }
    }
}

bool Aquas_AqAnglerFish_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    f32 sp6C = 1.0f;
    f32 sp68 = 1.0f;
    f32 sp64 = 1.0f;
    Vec3f sp58;
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    Actor* this = (Actor*) thisx;

    if ((this->timer_0C6 % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    } else if ((limbIndex < 7) || (limbIndex >= 9)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    switch (limbIndex) {
        case 7:
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) this->fwork[4]);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            sp6C = this->fwork[1];
            sp68 = this->fwork[2];
            sp64 = this->fwork[3];
            break;
        case 8:
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) this->fwork[4]);
            break;
    }

    if (sp6C != 1.0f) {
        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);

        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);

        if (*dList != NULL) {
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp58);
            Display_SetSecondLight(&sp58);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, sp6C, sp68, sp64, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, *dList);
            Matrix_Pop(&gGfxMatrix);
        }
        return true;
    }
    return false;
}

void Aquas_AqAnglerFish_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp3C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp30;
    Vec3f sp24;
    Actor* this = (Actor*) thisx;

    if ((this->health == 0) || (limbIndex == 7)) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                break;

            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[10]);
                break;

            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
                break;

            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[12]);
                break;

            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[13]);
                break;

            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[14]);
                break;

            case 7:
                sp30.x = this->fwork[11];
                sp30.y = 0.0f;
                sp30.z = 0.0f;
                Matrix_MultVec3f(gCalcMatrix, &sp30, &sp24);
                this->fwork[8] = sp24.x;
                this->fwork[9] = gGroundHeight;
                this->fwork[10] = sp24.z;
                break;

            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
                break;

            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[16]);
                break;

            case 16:
                Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->vwork[8]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[17]);
                break;
        }
    }
}

f32 D_i3_801C02C8[2] = { 255.0f, 68.0f };
s32 D_i3_801C02D0[2] = { 70, 100 };

void Aquas_AqAnglerFish_Draw(AqAnglerFish* this) {
    Vec3f frameTable[30];

    Matrix_Push(&gCalcMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    Animation_GetFrameData(&aAqAnglerFishAnim, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, aAqAnglerFishSkel, frameTable, Aquas_AqAnglerFish_OverrideLimbDraw,
                           Aquas_AqAnglerFish_PostLimbDraw, this, gCalcMatrix);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Pop(&gCalcMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, this->fwork[8], this->fwork[9], this->fwork[10], MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, this->fwork[5], this->fwork[6], this->fwork[7], MTXF_APPLY);
    RCP_SetupDL(&gMasterDisp, SETUPDL_49);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) this->iwork[12]);
    gDPSetEnvColor(gMasterDisp++, 127, 127, 0, (s32) this->iwork[12]);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aOrbDL);
    Matrix_Pop(&gGfxMatrix);
}

void Aquas_AqAnglerFish_Init(AqAnglerFish* this) {
    this->health = 200;
    this->iwork[13] = this->fwork[4] = 255.0f;
    this->fwork[12] = this->obj.rot.y;
    this->iwork[14] = this->iwork[16] = this->obj.rot.z;
}

void Aquas_AqAnglerFish_Update(AqAnglerFish* this) {
    Actor* var_v0;
    s32 i;
    f32 spB4;
    f32 temp_dz;
    f32 temp_fscc;
    f32 temp_ryr;
    f32 temp_fsc;
    f32 temp2;
    f32 temp_dx;
    f32 sp98;
    Vec3f sp8C;
    Vec3f sp80;
    f32 var_rxd;

    if (this->health == 0) {
        for (i = 0; i < 9; i++) {
            Aquas_SpawnDebris(&this->vwork[i], &this->vwork[9 + i], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(5.0f),
                              RAND_FLOAT_CENTERED(10.0f), 48, this->scale, 200, i);
            Effect_Effect362_Spawn(this->vwork[i].x, this->vwork[i].y, this->vwork[i].z, 10.0f);
        }

        func_effect_800815DC();
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 150.0f, 10.0f);
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 150.0f, 10.0f);
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 150.0f, 10.0f);

        for (i = 0; i < 5; i++) {
            func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT(i * 15.0f), this->obj.pos.y + RAND_FLOAT(i * 3.0f),
                                 this->obj.pos.z + RAND_FLOAT(i * 5.0f), 1.0f + RAND_FLOAT(1.0f), 7);
        }

        this->itemDrop = DROP_SILVER_RING_50p;
        if (this->iwork[16] != 0) {
            this->itemDrop = DROP_GOLD_RING_1;
        }

        Actor_Despawn(this);
        Object_Kill(&this->obj, this->sfxSource);
        AUDIO_PLAY_SFX(NA_SE_OB_MINI_BOMB, this->sfxSource, 4);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_AQ_ZAKO_DOWN);
    }

    this->fwork[5] = (this->obj.pos.y * 0.01f) + 2.5f;
    this->fwork[6] = (this->obj.pos.y * 0.003f) + 0.8f;
    this->fwork[7] = (this->obj.pos.y * 0.001f) + 0.8f;

    this->iwork[12] = (this->obj.pos.y * -0.24f) + 150.0f;
    if (this->iwork[12] < 30.0f) {
        this->iwork[12] = 30;
    }

    this->fwork[1] = (this->obj.pos.y * 0.0032f) + 1.0f;
    this->fwork[2] = (this->obj.pos.y * 0.0032f) + 1.5f;
    this->fwork[3] = (this->obj.pos.y * 0.0032f) + 2.0f;

    this->fwork[11] = this->obj.pos.y + 300.0f;
    if (this->fwork[11] > 1200.0f) {
        this->fwork[11] = 1200.0f;
    }

    this->animFrame++;
    if (this->animFrame >= Animation_GetFrameCount(&aAqAnglerFishAnim)) {
        this->animFrame = 0;
    }

    switch (this->state) {
        case 0:
            for (i = 0; i < 9; i++) {
                this->vwork[0 + i].x = this->obj.pos.x;
                this->vwork[0 + i].y = this->obj.pos.y;
                this->vwork[0 + i].z = this->obj.pos.z;
                this->vwork[9 + i].x = this->obj.rot.x;
                this->vwork[9 + i].y = this->obj.rot.y;
                this->vwork[9 + i].z = this->obj.rot.z;
            }

            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

            sp8C.x = sp8C.y = 0.0f;
            sp8C.z = -1400.0f;

            if (this->iwork[14] != 0) {
                sp8C.z = -5000.0f;
            }

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp80);

            this->fwork[15] = this->obj.pos.x + sp80.x;
            this->fwork[16] = this->obj.pos.z + sp80.z;

            this->state = 1;
            break;

        case 1:
            if (this->timer_0BC == 1) {
                this->iwork[15] = 1;
            }
            if (this->iwork[15] != 0) {
                if ((gPlayer[0].trueZpos + 300.0f) < this->obj.pos.z) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            } else {
                if (((gGameFrameCount % 2) == 0)) {
                    for (i = 0, var_v0 = &gActors[0]; i < ARRAY_COUNT(gActors); i++, var_v0++) {
                        if ((var_v0->obj.status == OBJ_ACTIVE) && (var_v0->obj.id == OBJ_ACTOR_AQ_SCULPIN) &&
                            (var_v0->state == 1) &&
                            (fabsf(var_v0->obj.pos.x - this->fwork[8]) <= (this->fwork[5] * 48.0f)) &&
                            (var_v0->obj.pos.y <= (this->obj.pos.y + 50.0f)) &&
                            (fabsf(var_v0->obj.pos.z - this->fwork[10]) <= (this->fwork[7] * 125.0f))) {
                            var_v0->state = 2;
                        }
                    }
                }
                sp98 = sqrtf(SQ(this->obj.pos.z - this->fwork[16]) + SQ(this->obj.pos.x - this->fwork[15]));
                this->fwork[13] -= 20.0f;
                this->fwork[14] += 5.0f;

                spB4 = SIN_DEG(this->fwork[13]) * sp98 * 0.1f;
                temp_fsc = COS_DEG(this->fwork[14]) * sp98 * 0.8f;
                temp_fscc = COS_DEG(this->obj.rot.y) * temp_fsc;
                temp2 = -SIN_DEG(this->obj.rot.y) * temp_fsc;

                temp_fscc = Math_Atan2F(this->obj.pos.x - this->fwork[15] + temp_fscc,
                                        this->obj.pos.z - this->fwork[16] + temp2);
                temp_fsc = -Math_Atan2F(this->obj.pos.y - spB4, sp98);
                temp_fscc = Math_RadToDeg(temp_fscc);

                Math_SmoothStepToAngle(&this->obj.rot.y, temp_fscc, 0.1f, 100.0f, 0.001f);

                temp_fscc = Math_RadToDeg(temp_fsc);

                if (this->obj.pos.y >= 1000.0f) {
                    temp_fscc = 0.0f;
                }

                Math_SmoothStepToAngle(&this->obj.rot.x, temp_fscc, 0.1f, 100.0f, 0.001f);
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

                sp8C.x = sp8C.y = 0.0f;
                sp8C.z = 10.0f;

                if (this->iwork[14] != 0) {
                    sp8C.z = 30.0f;
                }

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp80);

                this->vel.x = sp80.x;
                this->vel.y = sp80.y;
                this->vel.z = sp80.z;

                if (this->iwork[15] != 0) {
                    this->vel.x = this->vel.y = this->vel.z = 0.0f;
                }

                if ((this->iwork[14] != 0) && (this->obj.pos.z < (gPlayer[0].trueZpos - 2000.0f))) {
                    this->iwork[14] = 0;
                    this->timer_0BC = 500;
                }
            }
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if ((this->health != 0) && (this->dmgPart == 0)) {
            this->health -= this->damage;
            this->timer_0C6 = 30;

            AUDIO_PLAY_SFX(NA_SE_EN_AQ_ZAKO_DAMAGE, this->sfxSource, 4);

            if (this->health <= 0) {
                this->health = 0;
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 3);
                gHitCount += 4;
                D_ctx_80177850 = 15;
            }
        }
    }
}

void Aquas_AqSpindlyFish_Init(AqSpindlyFish* this) {
    s32 i;

    for (i = 0; i < 15; i++) {
        this->vwork[0 + i].x = this->obj.pos.x;
        this->vwork[0 + i].y = this->obj.pos.y;
        this->vwork[0 + i].z = this->obj.pos.z;

        this->vwork[15 + i].x = this->obj.rot.x;
        this->vwork[15 + i].y = this->obj.rot.y;
        this->vwork[15 + i].z = this->obj.rot.z;
    }

    this->health = 0;

    if (this->obj.rot.z != 0) {
        this->obj.rot.z = 0.0f;
        this->state = 1;
    }
    this->fwork[4] = this->obj.pos.z;
}

void Aquas_AqSpindlyFish_Update(AqSpindlyFish* this) {
    s32 i;
    f32 temp_dx;
    f32 temp_dy;
    f32 temp_dz;
    s32 pad;
    f32 spA8;
    Vec3f sp9C;
    Vec3f sp90;

    if (this->health == -100) {
        this->itemDrop = DROP_SILVER_RING_50p;
        Actor_Despawn(this);
        for (i = 0; i < 15; i++) {
            Aquas_SpawnDebris(&this->vwork[i], &this->vwork[15 + i], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(5.0f),
                              RAND_FLOAT_CENTERED(10.0f), 51, this->scale, 200, i);
            func_effect_800815DC();
            func_effect_8007D0E0(this->vwork[i].x, this->vwork[i].y, this->vwork[i].z + 100.0f, 6.0f);
        }
        Object_Kill(&this->obj, this->sfxSource);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_AQ_ZAKO_DOWN);
    }

    switch (this->state) {
        case 0:
            if (this->timer_0BC == 0) {
                this->timer_0BC = 200;

                this->fwork[1] = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(800.0f);
                this->fwork[2] = gPlayer[0].pos.y + 50.0f + RAND_FLOAT(100.0f);
                this->fwork[3] = gPlayer[0].trueZpos - 1500.0f;

                if (this->fwork[1] > 700.0f) {
                    this->fwork[1] = 700.0f;
                }
                if (this->fwork[1] < -700.0f) {
                    this->fwork[1] = -700.0f;
                }

                if (Rand_ZeroOne() < 0.2f) {
                    this->fwork[3] = gPlayer[0].trueZpos - 800.0f;
                    this->fwork[1] = gPlayer[0].pos.x;
                    this->fwork[2] = gPlayer[0].pos.y + 50.0f;
                }

                if (fabsf(this->fwork[4] - this->obj.pos.z) >= 20000.0f) {
                    this->fwork[3] = -10000.0f;
                }
            }
            this->fwork[3] += gPlayer[0].vel.z;

            temp_dx = this->fwork[1] - this->obj.pos.x;
            temp_dy = this->fwork[2] - this->obj.pos.y;
            temp_dz = this->fwork[3] - this->obj.pos.z;

            spA8 = Math_RadToDeg(Math_Atan2F(temp_dx, temp_dz));
            temp_dz = Math_RadToDeg(-Math_Atan2F(temp_dy, sqrtf(SQ(temp_dx) + SQ(temp_dz))));
            temp_dy = Math_SmoothStepToAngle(&this->obj.rot.y, spA8, 0.1f, 1.0f, 0);
            Math_SmoothStepToAngle(&this->obj.rot.x, temp_dz, 0.1f, 1.0f, 0);

            temp_dz = 340.0f;
            if (temp_dy < 0.0f) {
                temp_dz = 20.0f;
            }

            Math_SmoothStepToAngle(&this->obj.rot.z, temp_dz, 0.1f, 1.0f, 0.f);
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

            sp9C.x = sp9C.y = 0.0f;
            sp9C.z = 10.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp9C, &sp90);

            this->vel.x = sp90.x;
            this->vel.y = sp90.y;
            this->vel.z = sp90.z - 20.0f;
            break;

        case 1:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

            sp9C.y = sp9C.x = 0.0f;
            sp9C.z = 19.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp9C, &sp90);

            this->vel.x = sp90.x;
            this->vel.y = sp90.y;
            this->vel.z = sp90.z;
            break;
    }

    if ((gGameFrameCount % 4) == 0) {
        for (i = 0; i < 3; i++) {
            func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT_CENTERED(70.0f),
                                 this->obj.pos.y + RAND_FLOAT_CENTERED(70.0f),
                                 this->obj.pos.z + RAND_FLOAT_CENTERED(70.0f), 1.0f, 1);
        }
    }

    this->animFrame++;
    if (Animation_GetFrameCount(&aAqSpindlyFishAnim) < this->animFrame) {
        this->animFrame = 0;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->health > -100) {
            this->timer_0C6 = 15;
            this->health -= this->damage;
            for (i = 0; i < 10; i++) {
                func_effect_80081A8C(this->hitPos.x + RAND_FLOAT_CENTERED(70.0f),
                                     this->hitPos.y + RAND_FLOAT_CENTERED(70.0f),
                                     this->hitPos.z + RAND_FLOAT_CENTERED(70.0f), 1.0f, 1);
            }
            AUDIO_PLAY_SFX(NA_SE_EN_AQ_ZAKO_DAMAGE, this->sfxSource, 4);
            if (this->health <= -100) {
                this->health = -100;
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 3);
                gHitCount += 4;
                D_ctx_80177850 = 15;
            }
        }
    }
}

bool Aquas_AqSpindlyFish_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    if ((limbIndex >= 4) && (limbIndex < 14)) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    return false;
}

void Aquas_AqSpindlyFish_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    AqSpindlyFish* this = (AqSpindlyFish*) thisx;

    if (this->health == -100) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
                break;

            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[16]);
                break;

            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[17]);
                break;

            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[18]);
                break;

            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[19]);
                break;

            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[20]);
                break;

            case 7:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[21]);
                break;

            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[22]);
                break;

            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[8]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[23]);
                break;

            case 10:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[9]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[24]);
                break;

            case 11:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[10]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[25]);
                break;

            case 12:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[11]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[26]);
                break;

            case 13:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[12]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[27]);
                break;

            case 22:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[13]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[28]);
                break;

            case 23:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[14]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[29]);
                break;
        }
    }
}

void Aquas_AqSpindlyFish_Draw(AqSpindlyFish* this) {
    Vec3f frameTable[30];

    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    if ((this->timer_0C6 % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    Animation_GetFrameData(&aAqSpindlyFishAnim, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, aAqSpindlyFishSkel, frameTable, Aquas_AqSpindlyFish_OverrideLimbDraw,
                           Aquas_AqSpindlyFish_PostLimbDraw, this, gCalcMatrix);
}

void Aquas_AqGaroa_Init(AqGaroa* this) {
    s32 i;

    this->fwork[4] = 10.0f;
    this->fwork[3] = -1000.0f;
    this->fwork[2] = 30.0f;

    this->obj.pos.y = 150.0f;

    this->fwork[5] = 20.0f;
    this->fwork[6] = 20.0f;

    this->health = 60;

    for (i = 0; i < 10; i++) {
        this->vwork[0 + i].x = this->obj.pos.x;
        this->vwork[0 + i].y = this->obj.pos.y;
        this->vwork[0 + i].z = this->obj.pos.z;

        this->vwork[10 + i].x = this->obj.rot.x;
        this->vwork[10 + i].y = this->obj.rot.y;
        this->vwork[10 + i].z = this->obj.rot.z;
    }
}

void Aquas_AqGaroa_Update(AqGaroa* this) {
    s32 i;
    s32 j;
    f32 spAC;
    f32 temp_dz;
    f32 temp_dy;
    f32 temp_fs2;
    f32 temp1;
    Vec3f sp90;
    Vec3f sp84;
    Effect* effect;

    if (this->health == 0) {
        for (i = 0; i < 10; i++) {
            func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT(i * 15.0f), this->obj.pos.y + RAND_FLOAT(i * 3.0f),
                                 this->obj.pos.z + RAND_FLOAT(i * 5.0f), 1.0f + RAND_FLOAT(0.5f), 7);
        }

        for (i = 0; i < 10; i++) {
            Aquas_SpawnDebris(&this->vwork[0 + i], &this->vwork[10 + i], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(5.0f),
                              RAND_FLOAT_CENTERED(10.0f), 52, this->scale, 200, i);
            Effect_Effect362_Spawn(this->vwork[0 + i].x, this->vwork[0 + i].y, this->vwork[0 + i].z + 100.0f, 6.0f);
        }

        for (i = 0; i < 2; i++) {
            if (this->iwork[2 + i] != 0) {
                j = this->iwork[2 + i] - 1;
                effect = &gEffects[j];
                if ((effect->obj.id == OBJ_EFFECT_395) && (effect->state == 2) && (effect->timer_50 != 0)) {
                    effect->unk_44 = 3;
                    this->iwork[2 + i] = 0;
                }
            }
        }

        func_effect_800815DC();
        func_effect_8007D0E0(this->vwork[7].x, this->vwork[7].y, this->vwork[7].z, 5.0f);
        this->itemDrop = DROP_SILVER_RING_25p;
        Actor_Despawn(this);
        Object_Kill(&this->obj, this->sfxSource);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_AQ_ZAKO_DOWN);
    }

    if (this->state != 6) {
        spAC = gPlayer[0].pos.x - this->obj.pos.x;
        Math_SmoothStepToAngle(&this->obj.rot.y,
                               Math_RadToDeg(Math_Atan2F(spAC, gPlayer[0].trueZpos - this->obj.pos.z)), 1.0f, 5.0f,
                               0.001f);
    }

    if (((this->state >= 2) && (this->state < 4)) || (this->state >= 5)) {
        Math_SmoothStepToF(&this->fwork[4], 10.0f, 0.2f, 20.0f, 0);
        Math_SmoothStepToF(&this->fwork[5], 20.0f, 0.2f, 20.0f, 0);
        Math_SmoothStepToF(&this->fwork[6], 20.0f, 0.2f, 20.0f, 0);
    }

    if ((this->state >= 4) && (this->state < 5)) {
        Math_SmoothStepToF(&this->fwork[4], 159.0f, 0.1f, 10.0f, 0);
        Math_SmoothStepToF(&this->fwork[5], 159.0f, 0.1f, 10.0f, 0);
        Math_SmoothStepToF(&this->fwork[6], 255.0f, 0.1f, 10.0f, 0);
    }
    if (((this->state < 5) || (this->state == 7)) && (this->health != 0) && ((gGameFrameCount % 16) == 0)) {
        Effect_Effect364_Spawn(this->vwork[22].x, gGroundHeight, this->vwork[22].z, 5.0f);
    }

    Math_SmoothStepToF(&this->fwork[1], this->fwork[2], 0.1f, 2.0f, 0.00001f);
    Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].cam.eye.z - gPathProgress + this->fwork[3], 0.1f, this->fwork[1],
                       0.00001);

    if ((this->state == 1) && (fabsf(this->fwork[7] - this->obj.pos.z) >= 10000.0f)) {
        this->timer_0C0 = 20;
        this->state = 5;
    }

    switch (this->state) {
        case 0:
            this->timer_0BE = (s32) (100.0f + RAND_FLOAT(150.0f));
            this->state = 1;
            this->fwork[7] = this->obj.pos.z;
            break;

        case 1:
            if (this->timer_0BC != 0) {
                Math_SmoothStepToF(&this->fwork[4], 255.0f, 0.1f, 50.0f, 0);
                Math_SmoothStepToF(&this->fwork[5], 255.0f, 0.1f, 50.0f, 0);
                Math_SmoothStepToF(&this->fwork[6], 0.0f, 0.1f, 50.0f, 0);
            } else {
                Math_SmoothStepToF(&this->fwork[4], 10.0f, 0.2f, 20.0f, 0);
                Math_SmoothStepToF(&this->fwork[5], 20.0f, 0.2f, 20.0f, 0);
                Math_SmoothStepToF(&this->fwork[6], 20.0f, 0.2f, 20.0f, 0);
                if (this->timer_0BE == 0) {
                    this->iwork[1] = 1;
                    this->state = 2;
                }
            }
            if ((gGameFrameCount % 4) == 0) {
                Aquas_Effect366_Spawn(this->vwork[7].x + RAND_FLOAT_CENTERED(120.0f),
                                      this->vwork[7].y + RAND_FLOAT_CENTERED(50.0f),
                                      this->vwork[7].z + 100.0f + RAND_FLOAT_CENTERED(100.0f), 1.0f, 0);
            }
            break;

        case 2:
            this->animFrame += this->iwork[1];
            if (this->animFrame >= Animation_GetFrameCount(&D_AQ_6024F80)) {
                this->animFrame = 0;
                this->timer_0BE = 0;

                if (this->iwork[1] >= 2) {
                    this->timer_0BE = 30;
                }

                for (i = 0; i < 10; i++) {
                    Aquas_Effect366_Spawn(this->vwork[7].x + RAND_FLOAT_CENTERED(120.0f),
                                          this->vwork[7].y + RAND_FLOAT_CENTERED(50.0f),
                                          this->vwork[7].z + 100.0f + RAND_FLOAT_CENTERED(100.0f), 2.0f, 0);
                }
                this->state = 3;
            }
            break;

        case 3:
            if (this->timer_0BE == 0) {
                for (i = 0; i < 2; i++) {
                    this->iwork[2 + i] = func_effect_80081B24(this->vwork[20 + i].x, this->vwork[20 + i].y,
                                                              this->vwork[20 + i].z, 0.1f) +
                                         1;
                }
                this->timer_0C0 = 10;
                AUDIO_PLAY_SFX(NA_SE_EN_WT_SPARK_CHARGE, this->sfxSource, 4);
                this->state = 4;
            }
            break;

        case 4:
            this->iwork[5]++;
            if (this->timer_0C0 == 0) {
                Audio_KillSfxBySource(this->sfxSource);
                this->animFrame++;
                if (Animation_GetFrameCount(&D_AQ_602AC28) < this->animFrame) {
                    this->animFrame = Animation_GetFrameCount(&D_AQ_6024F80) - 1;
                    this->state = 7;
                }
            }

            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

            if ((this->animFrame < 21) && (this->state == 4) && (this->iwork[3] != 0)) {
                j = this->iwork[3] - 1;
                effect = &gEffects[j];
                if (this->animFrame == 20) {
                    spAC = gPlayer[0].pos.x - effect->obj.pos.x;
                    temp_dy = gPlayer[0].pos.y - effect->obj.pos.y;
                    temp_dz = gPlayer[0].trueZpos - 50.0f - effect->obj.pos.z;

                    temp_fs2 = Math_RadToDeg(Math_Atan2F(spAC, temp_dz));
                    temp1 = Math_RadToDeg(-Math_Atan2F(temp_dy, sqrtf(SQ(spAC) + SQ(temp_dz))));

                    Matrix_RotateY(gCalcMatrix, M_DTOR * temp_fs2, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, M_DTOR * temp1, MTXF_APPLY);

                    sp90.x = sp90.y = 0.0f;
                    sp90.z = 30.0f;

                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp90, &sp84);

                    effect->vel.x = sp84.x;
                    effect->vel.y = sp84.y;
                    effect->vel.z = sp84.z;

                    effect->unk_44 = 2;
                    effect->timer_50 = 100;
                    this->iwork[3] = 0;
                    AUDIO_PLAY_SFX(NA_SE_EN_WT_THROW, this->sfxSource, 4);
                } else {
                    effect->obj.pos.x = this->vwork[21].x;
                    effect->obj.pos.y = this->vwork[21].y;
                    effect->obj.pos.z = this->vwork[21].z;
                }
            }

            if ((this->animFrame < 58) && (this->state == 4) && (this->iwork[2] != 0)) {
                j = this->iwork[2] - 1;
                effect = &gEffects[j];
                if (this->animFrame == 57) {
                    spAC = gPlayer[0].pos.x - effect->obj.pos.x;
                    temp_dy = gPlayer[0].pos.y - effect->obj.pos.y;
                    temp_dz = gPlayer[0].trueZpos - 50.0f - effect->obj.pos.z;

                    temp_fs2 = Math_RadToDeg(Math_Atan2F(spAC, temp_dz));
                    temp1 = Math_RadToDeg(-Math_Atan2F(temp_dy, sqrtf(SQ(spAC) + SQ(temp_dz))));

                    Matrix_RotateY(gCalcMatrix, M_DTOR * temp_fs2, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, M_DTOR * temp1, MTXF_APPLY);

                    sp90.x = sp90.y = 0.0f;
                    sp90.z = 50.0f;

                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp90, &sp84);

                    effect->vel.x = sp84.x;
                    effect->vel.y = sp84.y;
                    effect->vel.z = sp84.z;

                    effect->unk_44 = 2;
                    effect->timer_50 = 100;
                    this->iwork[2] = 0;
                } else {
                    effect->obj.pos.x = this->vwork[20].x;
                    effect->obj.pos.y = this->vwork[20].y;
                    effect->obj.pos.z = this->vwork[20].z;
                }
            }
            break;

        case 5:
            Math_SmoothStepToAngle(&this->obj.rot.x, 40.0f, 0.1f, 10.0f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_AQ_6024F80)) {
                this->animFrame = Animation_GetFrameCount(&D_AQ_6024F80) - 1;
            }

            if (this->timer_0C0 == 0) {
                temp_dy = gPlayer[0].pos.y - 50.0f - this->obj.pos.y;
                temp_dz = gPlayer[0].trueZpos - this->obj.pos.z;
                temp1 = Math_RadToDeg(-Math_Atan2F(temp_dy, sqrtf(SQ(spAC) + SQ(temp_dz))));
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, M_DTOR * temp1, MTXF_APPLY);

                sp90.x = sp90.y = 0.0f;
                sp90.z = 40.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp90, &sp84);

                this->vel.x = sp84.x;
                this->vel.y = sp84.y;
                this->vel.z = sp84.z;
                this->state = 6;
            }
            break;

        case 6:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_AQ_6024F80)) {
                this->animFrame = Animation_GetFrameCount(&D_AQ_6024F80) - 1;
            }

            Math_SmoothStepToAngle(&this->obj.rot.x, 30.0f, 0.1f, 10.0f, 0);
            if (((gGameFrameCount % 2) == 0)) {
                Aquas_Effect366_Spawn(this->vwork[7].x + RAND_FLOAT_CENTERED(120.0f),
                                      this->vwork[7].y + RAND_FLOAT_CENTERED(50.0f),
                                      this->vwork[7].z + RAND_FLOAT_CENTERED(100.0f), 2.0f, 0);
            }
            break;

        case 7:
            this->animFrame--;
            if (this->animFrame <= 0) {
                this->animFrame = 0;
                this->timer_0BE = (s32) (100.0f + RAND_FLOAT(150.0f));
                this->state = 1;
            }
            break;
    }

    if (this->iwork[0] != 0) {
        this->health = 0;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->health != 0) {
            this->info.bonus = 0;
            if (this->damage == 31) {
                if (this->state >= 2) {
                    this->info.bonus = 1;
                    this->timer_0C6 = 30;
                    this->health -= this->damage;
                }
                if (this->state == 1) {
                    this->info.bonus = 1;
                    this->iwork[1] = 7;
                    this->state = 2;
                }
            } else if (this->state >= 2) {
                this->info.bonus = 1;
                this->timer_0C6 = 30;
                this->health -= this->damage;
                AUDIO_PLAY_SFX(NA_SE_EN_AQ_ZAKO_DAMAGE, this->sfxSource, 4);
            } else {
                this->timer_0BC = 50;
            }
            if (this->health <= 0) {
                this->health = 0;
            }
        }
    }
}

bool Aquas_AqGaroa_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    AqGaroa* this = (AqGaroa*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_58);
    if ((this->timer_0C6 % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    if ((this->timer_0C6 == 0) && ((this->fwork[6] <= 254.0f) || (this->state >= 4))) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[4], (s32) this->fwork[5], (s32) this->fwork[6],
                        255);
    }
    return false;
}

void Aquas_AqGaroa_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp40 = { 108.0f, 0.0f, 24.0f };
    Vec3f sp34 = { 102.0f, 14.0f, -21.0f };
    Vec3f sp28 = { 0.0f, 0.0f, 0.0f };
    AqGaroa* this = (AqGaroa*) thisx;

    switch (limbIndex) {
        case 1:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[10]);
            } else {
                Matrix_MultVec3f(gCalcMatrix, &sp40, &this->vwork[20]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[23]);
            }
            break;

        case 2:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
            }
            break;

        case 3:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[12]);
            }
            break;

        case 4:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[13]);
            } else {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[21]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[24]);
            }
            break;

        case 5:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[14]);
            }
            break;

        case 6:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
            }
            break;

        case 9:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[16]);
            }
            break;

        case 10:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[17]);
            }
            break;

        case 11:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[8]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[18]);
            }
            break;

        case 12:
            if (this->health == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[9]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[19]);
            } else {
                Matrix_MultVec3f(gCalcMatrix, &sp28, &this->vwork[22]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[25]);
            }
            break;
    }
}

void Aquas_AqGaroa_Draw(AqGaroa* this) {
    Vec3f frameTable[30];

    if ((this->state >= 3) && (this->state < 5)) {
        Animation_GetFrameData(&D_AQ_602AC28, this->animFrame, frameTable);
    } else {
        Animation_GetFrameData(&D_AQ_6024F80, this->animFrame, frameTable);
    }

    Matrix_Translate(gCalcMatrix, 0.0f, -150.0f, 100.0f, MTXF_APPLY);
    Animation_DrawSkeleton(3, aAqGaroaSkel, frameTable, Aquas_AqGaroa_OverrideLimbDraw, Aquas_AqGaroa_PostLimbDraw,
                           this, gCalcMatrix);
}

void Aquas_AqSquid_Update(AqSquid* this) {
    Vec3f spDC = { 0.0f, 0.0f, 50.0f };
    Vec3f spD0;
    Vec3f spC4;
    Vec3f spB8;
    Vec3f spAC;
    s32 i;
    f32 spfA4;
    f32 spA0;
    f32 spf9C;
    f32 spf98;
    f32 sp94;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

    if ((this->health == 0) && (this->state > 0)) {
        this->itemDrop = DROP_NONE;
        Actor_Despawn(this);

        for (i = 0; i < 5; i++) {
            func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT(i * 15.0f), this->obj.pos.y + RAND_FLOAT(i * 3.0f),
                                 this->obj.pos.z + RAND_FLOAT(i * 5.0f), 0.5f + RAND_FLOAT(0.3f), 7);
        }

        for (i = RAND_INT(10.0f); i < 13; i++) {
            Aquas_SpawnDebris(&this->vwork[0 + i], &this->vwork[13 + i], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(5.0f),
                              RAND_FLOAT_CENTERED(10.0f), 53, this->scale, 200, i);
            Effect_Effect362_Spawn(this->vwork[0 + i].x, this->vwork[0 + i].y, this->vwork[0 + i].z + 100.0f, 6.0f);
        }

        Object_Kill(&this->obj, this->sfxSource);

        func_effect_800815DC();
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_AQ_ZAKO_DOWN);
    }

    switch (this->state) {
        case 0:
            for (i = 0; i < 13; i++) {
                this->vwork[0 + i].x = this->obj.pos.x;
                this->vwork[0 + i].y = this->obj.pos.y;
                this->vwork[0 + i].z = this->obj.pos.z;
                this->vwork[13 + i].x = this->obj.rot.x;
                this->vwork[13 + i].y = this->obj.rot.y;
                this->vwork[13 + i].z = this->obj.rot.z;
            }

            this->health = 30;
            this->animFrame = 19;
            this->fwork[1] = this->obj.pos.z;

            if (this->obj.rot.z >= 4.0f) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_AQ_60314AC);
                this->health = 200;
                this->info.bonus = 1;
                this->state = 2;
                this->obj.rot.x = this->obj.rot.y = this->obj.rot.z = 0.0f;
                this->fwork[7] = this->obj.pos.y;
                this->scale = 2.0f;
            } else {
                if (this->obj.rot.z >= 2.0f) {
                    this->iwork[1] = 1;
                }
                spC4.x = spC4.y = 0.0f;
                spC4.z = 40.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spC4, &spB8);

                this->fwork[4] = spB8.x;
                this->fwork[5] = spB8.y;
                this->fwork[6] = spB8.z;
                this->state = 1;
                this->obj.rot.z = 0.0f;
            }
            break;

        case 1:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&aAqSquidAnim)) {
                this->animFrame = 0;
            }
            if (this->animFrame == 36) {
                this->vel.x = this->fwork[4];
                this->vel.y = this->fwork[5];
                this->vel.z = this->fwork[6];
            }

            Math_SmoothStepToF(&this->vel.x, 0.0f, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToF(&this->vel.y, 0.0f, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.1f, 1.0f, 0.00001f);

            i = 0;
            if (this->iwork[1] != 0) {
                if ((this->animFrame % 8) == 0) {
                    i = 1;
                }
            } else {
                if ((this->animFrame % 2) == 0) {
                    i = 1;
                }
            }

            if ((this->animFrame > 36) && (i != 0) && (fabsf(gPlayer[0].trueZpos - this->obj.pos.z) > 1000.0f)) {
                spfA4 = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(200.0f) - this->vwork[26].x;
                spA0 = gPlayer[0].pos.y + RAND_FLOAT_CENTERED(200.0f) - this->vwork[26].y;
                spf9C = gPlayer[0].trueZpos + RAND_FLOAT_CENTERED(200.0f) - this->vwork[26].z;

                sp94 = Math_RadToDeg(Math_Atan2F(spfA4, spf9C));
                spf98 = Math_RadToDeg(-Math_Atan2F(spA0, sqrtf(SQ(spfA4) + SQ(spf9C))));

                Matrix_RotateY(gCalcMatrix, M_DTOR * sp94, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, M_DTOR * spf98, MTXF_APPLY);

                spC4.x = spC4.y = 0.0f;
                spC4.z = 70.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spC4, &spAC);

                func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, this->vwork[26].x + RAND_FLOAT_CENTERED(200.0f),
                                     this->vwork[26].y + RAND_FLOAT_CENTERED(200.0f), this->vwork[26].z, spf98, sp94,
                                     0.0f, 0.0f, 0.0f, 0.0f, spAC.x, spAC.y, spAC.z, 1.0f);
            }
            break;

        case 2:
            this->animFrame++;
            if ((this->animFrame >= Animation_GetFrameCount(&aAqSquidAnim)) && (this->fwork[8] < 1.0f)) {
                this->animFrame = 0;
            }
            if (this->animFrame == 40) {
                this->fwork[8] = 700.0f;
                Aquas_801A9728(this, 50.0f, 10.0f, 8);
            }

            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[7] + this->fwork[8], 0.1f, 10.0f, 0.00001f);
            Math_SmoothStepToF(&this->fwork[8], 0.0f, 0.1f, 10.0f, 0.0001f);

            if (this->animFrame >= 40) {
                Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(70.0f),
                                      this->obj.pos.y - 50.0f + RAND_FLOAT_CENTERED(50.0f),
                                      this->obj.pos.z + RAND_FLOAT_CENTERED(100.0f), 1.0f, 0);
            }

            if (this->animFrame >= 37) {
                this->obj.rot.y += 20.0f;
                this->fwork[2] += 20.0f;
                if ((gGameFrameCount % 4) == 0) {
                    Matrix_RotateY(gCalcMatrix, this->fwork[2] * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->vwork[27].x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, this->vwork[27].z * M_DTOR, MTXF_APPLY);
                    Aquas_Effect366_Spawn(this->vwork[11].x + RAND_FLOAT_CENTERED(120.0f),
                                          this->vwork[11].y + RAND_FLOAT_CENTERED(50.0f),
                                          this->vwork[11].z + RAND_FLOAT_CENTERED(100.0f), 2.0f, 0);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spDC, &spD0);
                    func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, this->vwork[26].x + spD0.x,
                                         this->vwork[26].y + spD0.y, this->vwork[26].z + spD0.z, this->vwork[27].x,
                                         this->fwork[2], this->vwork[27].z, 0.0f, 0.0f, 0.0f, spD0.x, spD0.y, spD0.z,
                                         1.0f);
                }
            }
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if ((this->health != 0) && (this->state != 0)) {
            this->timer_0C6 = 15;
            this->health -= this->damage;
            AUDIO_PLAY_SFX(NA_SE_EN_AQ_ZAKO_DAMAGE, this->sfxSource, 4);
            if (this->health <= 0) {
                this->health = 0;
                if (this->scale > 1.0f) {
                    BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 2);
                    gHitCount += 2;
                    D_ctx_80177850 = 15;
                }
            }
        }
    }
}

void Aquas_AqSquid_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp34 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp28 = { -27.0f, 7.0f, 5.0f };
    AqSquid* this = (AqSquid*) thisx;

    if ((this->health == 0) || (limbIndex == 12)) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[13]);
                break;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[14]);
                break;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
                break;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[16]);
                break;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[17]);
                break;
            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[18]);
                break;
            case 7:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[19]);
                break;
            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[20]);
                break;
            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[8]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[21]);
                break;
            case 10:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[9]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[22]);
                break;
            case 11:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[10]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[23]);
                break;

            case 12:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[11]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[24]);
                Matrix_Push(&gCalcMatrix);
                switch (gGameFrameCount % 4U) {
                    case 0:
                        break;
                    case 1:
                        Matrix_RotateX(gCalcMatrix, M_PI / 2, MTXF_APPLY);
                        break;
                    case 2:
                        Matrix_RotateX(gCalcMatrix, M_PI, MTXF_APPLY);
                        break;
                    case 3:
                        Matrix_RotateX(gCalcMatrix, 3 * M_PI / 2, MTXF_APPLY);
                        break;
                }

                Matrix_MultVec3f(gCalcMatrix, &sp28, &this->vwork[26]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[27]);
                Matrix_Pop(&gCalcMatrix);
                break;

            case 21:
                Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[12]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[25]);
                break;
        }
    }
}

void Aquas_AqSquid_Draw(AqSquid* this) {
    Vec3f frameTable[30];

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    if ((this->timer_0C6 % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_30);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    } else if (this->state == 2) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_30);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 95, 31, 255);
    }

    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);

    if (this->state == 1) {
        Matrix_RotateX(gCalcMatrix, (this->obj.rot.x + 90.0f) * M_DTOR, MTXF_APPLY);
    }

    Animation_GetFrameData(&aAqSquidAnim, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, aAqSquidSkel, frameTable, NULL, Aquas_AqSquid_PostLimbDraw, this, gCalcMatrix);
}

void Aquas_AqSeaweed_Update(AqSeaweed* this) {
    Vec3f frameTable[30];
    u16 sp3E;

    switch (this->state) {
        case 0:
            this->animFrame = RAND_INT(50.0f);
            this->state++;
            /* fallthrough */
        case 1:
            this->animFrame += 2;
            if (this->animFrame >= Animation_GetFrameCount(&aAqSeaweedAnim)) {
                this->animFrame = 0;
            }

            sp3E = Animation_GetFrameData(&aAqSeaweedAnim, this->animFrame, frameTable);

            if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 150.0f) &&
                (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 500.0f) &&
                (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 700.0f)) {
                this->state = 2;
                this->fwork[0] = 0.0f;
            }
            break;

        case 2:
            this->animFrame += 2;
            if (this->animFrame >= Animation_GetFrameCount(&D_AQ_601DE50)) {
                this->animFrame = 0;
            }
            sp3E = Animation_GetFrameData(&D_AQ_601DE50, this->animFrame, frameTable);
            if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) > 150.0f) ||
                (fabsf(this->obj.pos.y - gPlayer[0].pos.y) > 500.0f) ||
                (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) > 700.0f)) {
                this->state = 1;
                this->fwork[0] = 0.0f;
            }
            break;
    }
    Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, sp3E, this->fwork[0], 100.0f, 0.0f);
    Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.008f, 0.0f);
}

void Aquas_AqSeaweed_Draw(AqSeaweed* this) {
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Animation_DrawSkeleton(1, aAqSeaweedSkel, this->vwork, NULL, NULL, &this->index, &gIdentityMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Aquas_AqBoulder_Init(AqBoulder* this) {
    if (this->state == 0) {
        this->scale = 1.0f;
        this->gravity = 0.3f;
        this->health = 10;
        this->fwork[2] = RAND_FLOAT_CENTERED((s32) (this->index % 8U) + 3.0f);
    } else {
        this->info.bonus = 0;
        this->scale = 0.5f;
        this->gravity = 0.1f;
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_AQ_603151C);
        this->fwork[2] = RAND_FLOAT_CENTERED((s32) (this->index % 4U) + 1.0f);
    }
    this->fwork[1] = RAND_FLOAT(50.0f);
}

void Aquas_AqBoulder_Update(AqBoulder* this) {
    s32 i;
    s32 var_s2;
    Actor* boulder;

    switch (this->state) {
        case 0:
            if (this->iwork[1] == 0) {
                this->obj.rot.z += this->fwork[2];
                if (((gGameFrameCount % 2) == 0)) {
                    Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(120.0f),
                                          this->obj.pos.y + RAND_FLOAT_CENTERED(50.0f),
                                          this->obj.pos.z + RAND_FLOAT_CENTERED(100.0f), 2.0f, 0);
                }

                this->fwork[1] += 10.0f;
                this->vel.x = SIN_DEG(this->fwork[1]) * 10.0f;

                if (this->obj.pos.y < (gGroundHeight + 30.0f)) {
                    AUDIO_PLAY_SFX(NA_SE_OB_AQ_ROCK_BOUND, this->sfxSource, 4);
                    this->iwork[1] = 1;
                    this->vel.x = this->vel.y = this->vel.z = 0.0f;
                    this->gravity = 0.0f;
                    Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 100.0f,
                                           this->scale * 30.0f);
                    Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 100.0f,
                                           this->scale * 30.0f);
                }
            }
            break;

        case 1:
            if (this->iwork[1] == 0) {
                this->obj.rot.z += this->fwork[2];
                if (((gGameFrameCount % 4) == 0)) {
                    Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(70.0f),
                                          this->obj.pos.y + RAND_FLOAT_CENTERED(50.0f),
                                          this->obj.pos.z + RAND_FLOAT_CENTERED(50.0f), 1.0f, 0);
                }

                Math_SmoothStepToF(&this->vel.y, -7.0f, 0.1f, 1.0f, 0.0001f);

                if (this->obj.pos.y < (gGroundHeight + 20.0f)) {
                    this->gravity = 0.0f;
                    if (this->vel.y < 0.0f) {
                        this->vel.y = 0.0f;
                    }
                    this->iwork[1] = 1;
                    AUDIO_PLAY_SFX(NA_SE_OB_AQ_ROCK_BOUND, this->sfxSource, 4);
                    Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 100.0f,
                                           this->scale * 30.0f);
                }
            } else {
                Math_SmoothStepToF(&this->vel.y, 0.0f, 0.1f, 1.0f, 0.0001f);
            }
            Math_SmoothStepToF(&this->vel.x, 0.0f, 0.1f, 1.0f, 0.0001f);
            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.1f, 1.0f, 0.0001f);
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        this->health -= this->damage;
        if (this->health <= 0) {
            this->health = this->itemDrop = 0;
            Actor_Despawn(this);
            if (this->state == 0) {
                for (i = 0, var_s2 = 0, boulder = &gActors[0]; (i < ARRAY_COUNT(gActors)) && (var_s2 < 4);
                     i++, boulder++) {
                    if (boulder->obj.status == OBJ_FREE) {
                        Actor_Initialize(boulder);
                        boulder->obj.status = OBJ_INIT;
                        boulder->obj.id = OBJ_ACTOR_AQ_BOULDER;
                        boulder->obj.pos.x = this->obj.pos.x;
                        boulder->obj.pos.y = this->obj.pos.y + 20.0f;
                        boulder->obj.pos.z = this->obj.pos.z;
                        boulder->vel.x = RAND_FLOAT_CENTERED(50.0f);
                        boulder->vel.y = RAND_FLOAT(5.0f);
                        boulder->vel.z = RAND_FLOAT_CENTERED(50.0f);
                        boulder->state = 1;

                        Object_SetInfo(&boulder->info, boulder->obj.id);
                        var_s2++;
                    }
                }
                if (i >= ARRAY_COUNT(gActors)) {
                    boulder->obj.status = OBJ_FREE;
                }
            } else {
                for (i = 0; i < 4; i++) {
                    Aquas_SpawnDebris(&this->obj.pos, &this->obj.rot, RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT(5.0f),
                                      RAND_FLOAT_CENTERED(10.0f), 54, 0.1f, 200, i);
                }
            }
            Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 130.0f, this->scale * 30.0f);
            Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 130.0f, this->scale * 30.0f);
            Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 130.0f, this->scale * 30.0f);
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        }
    }
}

void Aquas_AqBoulder_Draw(AqBoulder* this) {
    Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aAqBoulderDL);
}

void Aquas_AqCoral_Update(AqCoral* this) {
    s32 i;

    switch (this->state) {
        case 0:
            for (i = 0; i < 5; i++) {
                this->vwork[0 + i].x = this->obj.pos.x;
                this->vwork[0 + i].y = this->obj.pos.y;
                this->vwork[0 + i].z = this->obj.pos.z;
                this->vwork[5 + i].x = this->obj.rot.x;
                this->vwork[5 + i].y = this->obj.rot.y;
                this->vwork[5 + i].z = this->obj.rot.z;
            }
            this->state++;
            break;

        case 1:
            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                if (this->damage == 0) {
                    gPlayer[0].hitTimer = 6;
                    gPlayer[0].hitDirection = 0;
                }
                this->state++;
            }
            break;

        case 2:
            for (i = 0; i < 5; i++) {
                Aquas_SpawnDebris(&this->vwork[0 + i], &this->vwork[5 + i], RAND_FLOAT_CENTERED(20.0f),
                                  RAND_FLOAT(5.0f), RAND_FLOAT_CENTERED(10.0f), 55, this->scale, 200, i);
                Effect_Effect362_Spawn(this->vwork[0 + i].x, this->vwork[0 + i].y, this->vwork[0 + i].z + 100.0f, 6.0f);
            }
            Object_Kill(&this->obj, this->sfxSource);
            break;
    }
}

void Aquas_AqCoral_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    Actor* this = (Actor*) thisx;

    if (this->state != 0) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[5]);
                break;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[6]);
                break;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[7]);
                break;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[8]);
                break;
            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                break;
        }
    }
}

void Aquas_AqCoral_Draw(AqCoral* this) {
    Vec3f frameTable[30];

    Animation_GetFrameData(&aAqCoralAnim, 0, frameTable);
    Animation_DrawSkeleton(3, aAqCoralSkel, frameTable, NULL, Aquas_AqCoral_PostLimbDraw, this, gCalcMatrix);
}

Vec3f D_i3_801C0344[4] = {
    { -6.4f, -4.6f, -7.8f },
    { 6.4f, 4.6f, 7.8f },
    { -5.9f, -7.8f, -7.0f },
    { 5.9f, 7.8f, 7.0f },
};
f32 D_i3_801C0374[51] = {
    // Structured as f32[4 + 4 + 9][3]
    1.0f,  1.0f,  1.0f, 1.3f,  0.8f, 1.3f,  1.0f,  1.2f,  1.0f,  1.3f,  0.8f,  1.3f,  1.0f,  1.0f,  1.0f,  1.3f,  1.0f,
    1.3f,  1.0f,  1.0f, 1.0f,  1.3f, 1.0f,  1.3f,  1.0f,  1.0f,  1.0f,  0.85f, 0.95f, 0.85f, 0.85f, 0.95f, 0.85f, 0.85f,
    0.95f, 0.85f, 1.0f, 1.05f, 1.0f, 0.85f, 0.95f, 0.85f, 0.85f, 0.95f, 0.85f, 0.85f, 0.95f, 0.85f, 0.85f, 0.95f, 0.85f,
};
s32 D_i3_801C0440[24] = {
    0, 30, 60, 90, 0, 0, 0, 0, 0, 15, 30, 45, 0, 0, 0, 0, 0, 15, 30, 45, 60, 75, 90, 105,
};
s32 D_i3_801C04A0[6] = {
    15, -15, 10, -10, 7, -7,
};

void Aquas_AqJellyfish_Init(AqJellyfish* this) {
    s32 sp64;
    s32 sp60;
    Vec3f sp54;
    Vec3f sp48;
    AqJellyfish* jellyfish;
    AqJellyfish* jellyfish2;

    this->fwork[1] = RAND_FLOAT(100.0f);
    this->timer_0BC = RAND_INT(50.0f);
    this->iwork[3] = RAND_INT(10.0f) % 2U;
    this->fwork[11] = this->fwork[14] = this->fwork[17] = this->fwork[12] = this->fwork[15] = this->fwork[18] =
        this->fwork[13] = this->fwork[16] = this->fwork[19] = 1.0f;
    this->fwork[2] = 213.0f;
    this->fwork[3] = 160.0f;
    this->fwork[4] = 255.0f;
    this->fwork[8] = 255.0f;
    this->fwork[7] = 255.0f;
    this->fwork[6] = 197.0f;
    this->fwork[5] = 197.0f;
    this->fwork[10] = 231.0f;
    this->fwork[9] = 231.0f;
    this->fwork[22] = this->obj.pos.x;
    this->fwork[23] = this->obj.pos.y;
    this->fwork[24] = this->obj.pos.z;
    this->iwork[4] = RAND_INT(60.0f);
    this->iwork[5] = 15 + RAND_INT(45.0f);
    this->iwork[6] = 45 + RAND_INT(15.0f);
    this->iwork[7] = RAND_INT(120.0f);
    this->iwork[8] = RAND_INT(120.0f);
    this->iwork[9] = RAND_INT(120.0f);

    this->animFrame = RAND_INT(Animation_GetFrameCount(&aAqJellyfishAnim));

    if (this->iwork[2] == 0) {
        this->iwork[18] = fabsf(this->obj.rot.y / 10.0f);
        if ((this->iwork[18] == 0) || (this->iwork[18] == 2)) {
            this->iwork[19] = 1;
        }
        this->iwork[13] = D_i3_801C4450 * 3;

        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_NEW);

        sp54.x = 0.0f;
        sp54.y = this->obj.rot.x * 10.0f;
        sp54.z = 0.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);

        for (sp64 = 0, jellyfish = &gActors[0]; sp64 < ARRAY_COUNT(gActors); sp64++, jellyfish++) {
            if (jellyfish->obj.status == OBJ_FREE) {
                Actor_Initialize(jellyfish);
                jellyfish->obj.status = OBJ_INIT;
                jellyfish->obj.id = OBJ_ACTOR_AQ_JELLYFISH;
                jellyfish->obj.pos.x = this->obj.pos.x + sp48.x;
                jellyfish->obj.pos.y = this->obj.pos.y + sp48.y;
                jellyfish->obj.pos.z = this->obj.pos.z;
                jellyfish->iwork[0] = this->index + 1;
                jellyfish->iwork[2] = 1;
                jellyfish->iwork[13] = this->iwork[13];
                jellyfish->iwork[18] = this->iwork[18];
                jellyfish->iwork[19] = this->iwork[19];
                this->iwork[0] = sp64 + 1;
                Object_SetInfo(&jellyfish->info, jellyfish->obj.id);
                break;
            }
        }

        Matrix_RotateZ(gCalcMatrix, (this->obj.rot.z + 90.0f) * M_DTOR, MTXF_NEW);

        sp54.x = 0.0f;
        sp54.y = this->obj.rot.x * 10.0f;
        sp54.z = 0.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);

        for (sp60 = 0, jellyfish2 = &gActors[0]; sp60 < ARRAY_COUNT(gActors); sp60++, jellyfish2++) {
            if (jellyfish2->obj.status == OBJ_FREE) {
                Actor_Initialize(jellyfish2);
                jellyfish2->obj.status = OBJ_INIT;
                jellyfish2->obj.id = OBJ_ACTOR_AQ_JELLYFISH;
                jellyfish2->obj.pos.x = this->obj.pos.x + sp48.x;
                jellyfish2->obj.pos.y = this->obj.pos.y + sp48.y;
                jellyfish2->obj.pos.z = this->obj.pos.z;
                jellyfish2->iwork[0] = this->index + 1;
                jellyfish2->iwork[1] = jellyfish->index + 1;
                jellyfish2->iwork[2] = 2;
                jellyfish2->iwork[13] = this->iwork[13];
                jellyfish2->iwork[18] = this->iwork[18];
                jellyfish2->iwork[19] = this->iwork[19];
                jellyfish->iwork[1] = sp60 + 1;
                this->iwork[1] = sp60 + 1;
                Object_SetInfo(&jellyfish2->info, jellyfish2->obj.id);
                break;
            }
        }
        this->fwork[21] = this->obj.rot.x * 10.0f;
        this->iwork[17] = fabsf(Math_ModF(this->obj.rot.y, 10.0f));
        this->fwork[20] = this->obj.rot.z;

        this->obj.rot.x = this->obj.rot.y = this->obj.rot.z = 0.0f;
        D_i3_801C4450++;
        if (D_i3_801C4450 > 20) {
            D_i3_801C4450 = 0;
        }
    }
}

void Aquas_AqJellyfish_Update(AqJellyfish* this) {
    s32 i;
    s32 it0;
    s32 it1;
    Vec3f sp80;
    Vec3f sp74;
    Actor* sp70;
    Actor* sp6C;
    AqWall1* wall1;

    if (this->timer_0C0 == 0) {
        switch (this->iwork[18]) {
            case 1:
            case 2:
                i = this->iwork[19] + (this->iwork[2] * 2);
                this->vel.x = D_i3_801C04A0[i];
                if ((gGameFrameCount % 4) == 0) {
                    if (fabsf(this->fwork[22] - this->obj.pos.x) >= 100.0f) {
                        if (this->iwork[20] == 0) {
                            this->iwork[19]++;
                            this->iwork[19] &= 1;
                            this->iwork[20] = 50;
                        }
                    } else {
                        for (i = 0, wall1 = &gScenery[0]; i < ARRAY_COUNT(gScenery); i++, wall1++) {
                            if ((wall1->obj.status == OBJ_ACTIVE) && (wall1->obj.id == OBJ_SCENERY_AQ_WALL_1) &&
                                Object_CheckHitboxCollision(&this->obj.pos, wall1->info.hitbox, &wall1->obj, 0.0f, 0.0f,
                                                            0.0f) &&
                                (this->iwork[20] == 0)) {
                                this->iwork[20] = 50;
                                this->iwork[19]++;
                                this->iwork[19] &= 1;
                            }
                        }
                    }
                }
                break;

            case 3:
            case 4:
                i = this->iwork[19] + (this->iwork[2] * 2);
                this->vel.y = D_i3_801C04A0[i];
                if (((gGameFrameCount % 4) == 0)) {
                    if (fabsf(this->fwork[23] - this->obj.pos.y) >= 100.0f) {
                        if (this->iwork[20] == 0) {
                            this->iwork[19]++;
                            this->iwork[19] &= 1;
                            this->iwork[20] = 50;
                        }
                    } else {
                        for (i = 0, wall1 = gScenery; i < ARRAY_COUNT(gScenery); i++, wall1++) {
                            if ((wall1->obj.status == OBJ_ACTIVE) && (wall1->obj.id == OBJ_SCENERY_AQ_WALL_1) &&
                                (Object_CheckHitboxCollision(&this->obj.pos, wall1->info.hitbox, &wall1->obj, 0.0f,
                                                             0.0f, 0.0f) ||
                                 (this->obj.pos.y < (gGroundHeight + 30.0f))) &&
                                (this->iwork[20] == 0)) {
                                this->iwork[20] = 50;
                                this->iwork[19]++;
                                this->iwork[19] &= 1;
                            }
                        }
                    }
                }
                break;
        }
    } else {
        this->vel.x = this->vel.y = 0.0f;
    }

    if (this->iwork[2] == 0) {
        sp70 = &gActors[this->iwork[0] - 1];
        sp6C = &gActors[this->iwork[1] - 1];

        Math_SmoothStepToF(&this->fwork[21], 200.0f, 0.1f, 2.0f, 0.0001f);

        if ((this->iwork[13] == sp70->iwork[13]) && (this->iwork[14] == 0)) {
            i = 1;
            if (!((sp70->obj.id == OBJ_ACTOR_AQ_JELLYFISH) && (sp70->obj.status == OBJ_ACTIVE))) {
                this->iwork[14] = 1;
                i = 0;
            }
            if (i != 0) {
                if (!this->timer_0C0 && sp70->timer_0C0 >= 2) {
                    this->timer_0C0 = sp70->timer_0C0;
                    this->timer_0C6 = sp70->timer_0C6;
                }
                if (this->timer_0C0 && !sp70->timer_0C0 >= 2) {
                    sp70->timer_0C0 = this->timer_0C0;
                    sp70->timer_0C6 = this->timer_0C6;
                }
            }

            if (((gGameFrameCount % 8) == 0)) {
                Effect_SpawnTimedSfxAtPos(&sp70->obj.pos, NA_SE_EN_WT_SPARK_BEAM);
            }

            Aquas_801A92EC(this, sp70->obj.pos.x, sp70->obj.pos.y, sp70->obj.pos.z, this->iwork[13], i);

            if ((this->fwork[21] > 200.0f) && (this->iwork[17] != 0)) {
                Matrix_RotateZ(gCalcMatrix, this->fwork[20] * M_DTOR, MTXF_NEW);
                sp80.x = 0.0f;
                sp80.y = this->fwork[21];
                sp80.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp80, &sp74);
                sp70->obj.pos.x = this->obj.pos.x + sp74.x;
                sp70->obj.pos.y = this->obj.pos.y + sp74.y;
                sp70->obj.pos.z = this->obj.pos.z;
            }
        }

        if ((this->iwork[13] == sp6C->iwork[13]) && (this->iwork[15] == 0)) {
            i = 1;
            if (!((sp6C->obj.id == OBJ_ACTOR_AQ_JELLYFISH) && (sp6C->obj.status == OBJ_ACTIVE))) {
                this->iwork[15] = 1;
                i = 0;
            }
            if (i != 0) {
                if (!this->timer_0C0 && sp6C->timer_0C0 >= 2) {
                    this->timer_0C0 = sp6C->timer_0C0;
                    this->timer_0C6 = sp6C->timer_0C6;
                }
                if (this->timer_0C0 && !sp6C->timer_0C0 >= 2) {
                    sp6C->timer_0C0 = this->timer_0C0;
                    sp6C->timer_0C6 = this->timer_0C6;
                }
            }
            if (((gGameFrameCount % 4) == 0)) {
                Effect_SpawnTimedSfxAtPos(&sp6C->obj.pos, NA_SE_EN_WT_SPARK_BEAM);
            }

            Aquas_801A92EC(this, sp6C->obj.pos.x, sp6C->obj.pos.y, sp6C->obj.pos.z, this->iwork[13] + 1, i);

            if ((this->fwork[21] > 200.0f) && (this->iwork[17] != 0)) {
                Matrix_RotateZ(gCalcMatrix, (this->fwork[20] + 90.0f) * M_DTOR, MTXF_NEW);
                sp80.x = 0.0f;
                sp80.y = this->fwork[21];
                sp80.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp80, &sp74);
                sp6C->obj.pos.x = this->obj.pos.x + sp74.x;
                sp6C->obj.pos.y = this->obj.pos.y + sp74.y;
                sp6C->obj.pos.z = this->obj.pos.z;
            }
        }
    } else if (this->iwork[2] == 1) {
        sp70 = &gActors[this->iwork[1] - 1];
        if ((this->iwork[13] == sp70->iwork[13]) && (this->iwork[16] == 0)) {
            i = 1;
            if (!((sp70->obj.id == OBJ_ACTOR_AQ_JELLYFISH) && (sp70->obj.status == OBJ_ACTIVE))) {
                this->iwork[16] = 1;
                i = 0;
            }
            if (i != 0) {
                if (!this->timer_0C0 && sp70->timer_0C0 >= 2) {
                    this->timer_0C0 = sp70->timer_0C0;
                    this->timer_0C6 = sp70->timer_0C6;
                }
                if (this->timer_0C0 && !sp70->timer_0C0 >= 2) {
                    sp70->timer_0C0 = this->timer_0C0;
                    sp70->timer_0C6 = this->timer_0C6;
                }
            }

            if (((gGameFrameCount % 16) == 0)) {
                Effect_SpawnTimedSfxAtPos(&sp70->obj.pos, NA_SE_EN_WT_SPARK_BEAM);
            }

            Aquas_801A92EC(this, sp70->obj.pos.x, sp70->obj.pos.y, sp70->obj.pos.z, this->iwork[13] + 2, i);
        }
    }

    if ((gGameFrameCount % 4) == 0) {
        Effect_Effect390_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                               this->obj.pos.y + RAND_FLOAT_CENTERED(100.0f),
                               this->obj.pos.z + RAND_FLOAT_CENTERED(50.0f), this->vel.x, this->vel.y, this->vel.z,
                               0.05f + RAND_FLOAT(0.03f), 10);
    }

    if (this->timer_0BE == 0) {
        D_i3_801C41B8[18] = 255.0f;
        D_i3_801C41B8[19] = 255.0f;
        D_i3_801C41B8[20] = 255.0f;
        this->timer_0BE = 10;
    }

    if (this->iwork[3] == 0) {
        Math_SmoothStepToF(&this->fwork[1], 30.0f, 0.1f, 1.0f, 0.00001f);
    } else {
        Math_SmoothStepToF(&this->fwork[1], 100.0f, 0.1f, 1.0f, 0.00001f);
    }

    if (this->timer_0BC == 0) {
        this->timer_0BC = 100;
        this->iwork[3]++;
        this->iwork[3] &= 1;
    }

    this->animFrame += 2;
    if (this->animFrame >= Animation_GetFrameCount(&aAqJellyfishAnim)) {
        this->animFrame = 0;
    }

    if (this->iwork[4] < 30) {
        this->fwork[2] += D_i3_801C0344[0].x;
        this->fwork[3] += D_i3_801C0344[0].y;
        this->fwork[4] += D_i3_801C0344[0].z;
        if (this->fwork[2] < 0.0f) {
            this->fwork[2] = this->fwork[3] = this->fwork[4] = 0.0f;
        }
    } else {
        this->fwork[2] += D_i3_801C0344[1].x;
        this->fwork[3] += D_i3_801C0344[1].y;
        this->fwork[4] += D_i3_801C0344[1].z;
        if (this->fwork[3] >= 160.0f) {
            this->fwork[2] = 213.0f;
            this->fwork[3] = 160.0f;
            this->fwork[4] = 255.0f;
        }
    }

    for (i = 0; i < 2; i++) {
        if (this->iwork[i + 5] < 30) {
            this->fwork[i + 5] += D_i3_801C0344[2].x;
            this->fwork[i + 7] += D_i3_801C0344[2].y;
            this->fwork[i + 9] += D_i3_801C0344[2].z;
            if (this->fwork[i + 7] < 0.0f) {
                this->fwork[i + 5] = this->fwork[i + 7] = this->fwork[i + 9] = 0.0f;
            }
        } else {
            this->fwork[i + 5] += D_i3_801C0344[3].x;
            this->fwork[i + 7] += D_i3_801C0344[3].y;
            this->fwork[i + 9] += D_i3_801C0344[3].z;
            if (this->fwork[i + 7] >= 255.0f) {
                this->fwork[i + 5] = 197.0f;
                this->fwork[i + 7] = 255.0f;
                this->fwork[i + 9] = 231.0f;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        it0 = i * 12 + 3 * this->iwork[10 + i];
        Math_SmoothStepToF(&this->fwork[11 + i], D_i3_801C0374[it0 + 0], 0.1f, 5.0f, 0.000001f);
        Math_SmoothStepToF(&this->fwork[14 + i], D_i3_801C0374[it0 + 1], 0.1f, 5.0f, 0.000001f);
        Math_SmoothStepToF(&this->fwork[17 + i], D_i3_801C0374[it0 + 2], 0.1f, 5.0f, 0.000001f);

        it0 = 8 * i + this->iwork[10 + i];
        if (this->iwork[7 + i] == D_i3_801C0440[it0]) {
            this->iwork[10 + i]++;
        }
    }

    this->iwork[4]++;
    if (this->iwork[4] >= 60) {
        this->iwork[4] = 0;
    }

    this->iwork[5]++;
    if (this->iwork[5] >= 60) {
        this->iwork[5] = 0;
    }

    this->iwork[6]++;
    if (this->iwork[6] >= 60) {
        this->iwork[6] = 0;
    }

    this->iwork[7]++;
    if (this->iwork[7] >= 120) {
        this->iwork[7] = this->iwork[10] = 0;
    }

    this->iwork[8]++;
    if (this->iwork[8] >= 60) {
        this->iwork[8] = this->iwork[11] = 0;
    }

    this->iwork[9]++;
    if (this->iwork[9] >= 120) {
        this->iwork[9] = this->iwork[12] = 0;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_AQ_ZAKO_DAMAGE, this->sfxSource, 4);
        if (this->damage != 31) {
            this->timer_0C0 = this->timer_0C6 = 40;
        } else {
            this->timer_0C0 = this->timer_0C6 = 80;
        }
    }

    if (this->iwork[20] != 0) {
        this->iwork[20]--;
    }
    Aquas_801A96DC(this);
}

bool Aquas_AqJellyfish_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Vec3f sp64 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp58;
    f32 sp54 = 0.0f;
    f32 sp50 = 0.0f;
    f32 sp4C = 0.0f;
    Actor* this = (Actor*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_41);

    if ((this->timer_0C6 % 2) == 0) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 191, 255, 223, (s32) this->fwork[1]);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
    }

    switch (limbIndex) {
        case 1:
            sp54 = this->fwork[12];
            sp50 = this->fwork[15];
            sp4C = this->fwork[18];
            break;

        case 2:
            sp54 = this->fwork[13];
            sp50 = this->fwork[16];
            sp4C = this->fwork[19];
            break;

        case 3:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[5], (s32) this->fwork[7], (s32) this->fwork[9],
                            255);
            break;

        case 4:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[2], (s32) this->fwork[3], (s32) this->fwork[4],
                            255);
            break;

        case 5:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[6], (s32) this->fwork[8],
                            (s32) this->fwork[10], 255);
            break;

        case 11:
            sp54 = this->fwork[11];
            sp50 = this->fwork[14];
            sp4C = this->fwork[17];
    }

    if (sp54 > 0.0f) {
        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);

        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);

        if (*dList != NULL) {
            Matrix_MultVec3f(gCalcMatrix, &sp64, &sp58);
            Display_SetSecondLight(&sp58);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, sp54, sp50, sp4C, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, *dList);
            Matrix_Pop(&gGfxMatrix);
        }
        return true;
    } else {
        return false;
    }
}

void Aquas_AqJellyfish_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    /* Unimplemented */
}

void Aquas_AqJellyfish_Draw(AqJellyfish* this) {
    Vec3f frameTable[30];

    Animation_GetFrameData(&aAqJellyfishAnim, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, aAqJellyfishSkel, frameTable, Aquas_AqJellyfish_OverrideLimbDraw,
                           Aquas_AqJellyfish_PostLimbDraw, this, gCalcMatrix);
}

s32 D_i3_801C04C4[9] = {
    DROP_SILVER_RING, DROP_BOMB,        DROP_LASERS, DROP_GOLD_RING_1, DROP_GOLD_RING_2,
    DROP_GOLD_RING_3, DROP_GOLD_RING_4, DROP_NONE,   DROP_1UP,
};

void Aquas_AqStoneColumn_Update(AqStoneColumn* this) {
    s32 j;
    s32 i;
    Vec3f spA4;
    Vec3f sp98;
    AqStoneColumn* stoneColumn;

    switch (this->state) {
        case 0:
            this->vwork[0].x = this->obj.pos.x;
            this->vwork[0].y = this->obj.pos.y;
            this->vwork[0].z = this->obj.pos.z;

            this->vwork[1].x = this->obj.pos.x;
            this->vwork[1].y = this->obj.pos.y;
            this->vwork[1].z = this->obj.pos.z;

            this->vwork[4].x = this->obj.pos.x;
            this->vwork[4].y = this->obj.pos.y;
            this->vwork[4].z = this->obj.pos.z;

            this->iwork[1] = this->obj.rot.z;
            if (this->iwork[1] >= 9) {
                this->iwork[1] = 7;
            }

            if (this->obj.rot.y != 0) {
                this->health = 7650;
                this->iwork[3] = 1;
                this->state = 2;
            } else {
                this->health = 10;
                this->info.drawType = 2;
                this->info.bonus = 1;
                this->state++;
            }
            this->obj.rot.y = this->obj.rot.z = 0.0f;
            break;

        case 1:
            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                if ((this->health != 0) && (this->iwork[3] == 0) && (this->damage == 31)) {
                    this->health -= this->damage;
                    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
                    if (this->health <= 0) {
                        this->health = 0;
                        this->state = 3;
                    }
                }
            }
            break;

        case 3:
            for (i = 0; i < 2; i++) {
                for (j = 0; j < ARRAY_COUNT(gActors); j++) {
                    if ((gActors[j].obj.status == OBJ_ACTIVE) && (gActors[j].obj.id == OBJ_ACTOR_DEBRIS) &&
                        (gActors[j].state == 58)) {
                        Object_Kill(&gActors[j].obj, gActors[j].sfxSource);
                        break;
                    }
                }
            }

            for (i = 0; i < 2; i++) {
                for (j = 0, stoneColumn = &gActors[0]; j < ARRAY_COUNT(gActors); j++, stoneColumn++) {
                    if (stoneColumn->obj.status == OBJ_FREE) {
                        Actor_Initialize(stoneColumn);
                        stoneColumn->obj.status = OBJ_INIT;
                        stoneColumn->obj.id = OBJ_ACTOR_AQ_STONE_COLUMN;
                        stoneColumn->obj.pos.x = this->vwork[i].x;
                        stoneColumn->obj.pos.y = this->vwork[i].y;
                        stoneColumn->obj.pos.z = this->vwork[i].z;
                        stoneColumn->iwork[0] = i + 1;

                        Object_SetInfo(&stoneColumn->info, stoneColumn->obj.id);

                        if (i == 0) {
                            stoneColumn->fwork[0] = RAND_FLOAT(360.0f);
                            Matrix_RotateY(gCalcMatrix, stoneColumn->fwork[0] * M_DTOR, MTXF_NEW);
                            spA4.x = spA4.y = spA4.z = 5.0f;
                            Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA4, &sp98);
                            stoneColumn->vel.x = sp98.x;
                            stoneColumn->vel.z = sp98.z;
                            stoneColumn->gravity = 0.4f;
                            stoneColumn->state = 5;
                            stoneColumn->info.hitbox = SEGMENTED_TO_VIRTUAL(D_AQ_6030D3C);
                        } else {
                            stoneColumn->state = 2;
                            stoneColumn->info.hitbox = SEGMENTED_TO_VIRTUAL(D_AQ_6030D58);
                        }
                        break;
                    }
                }
            }

            for (j = 0; j < 10; j++) {
                Aquas_SpawnDebris(&this->vwork[4], &this->vwork[5], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(5.0f),
                                  RAND_FLOAT_CENTERED(10.0f), 58, 0.2f + RAND_FLOAT(1.0f), 200, 0);
                Effect_Effect362_Spawn(this->vwork[4].x, this->vwork[4].y, this->vwork[4].z + 50.0f, 6.0f);
            }

            func_effect_800815DC();
            func_effect_8007D0E0(this->vwork[4].x, this->vwork[4].y, this->vwork[4].z, 10.0f);

            for (j = 0; j < 20; j++) {
                Aquas_Effect366_Spawn(this->vwork[4].x + RAND_FLOAT_CENTERED(100.0f),
                                      this->vwork[4].y + RAND_FLOAT_CENTERED(200.0f),
                                      this->vwork[4].z + 100.0f + RAND_FLOAT_CENTERED(200.0f), 6.0f, 2);
            }

            func_effect_800815DC();
            func_effect_8007D0E0(this->vwork[4].x, this->vwork[4].y, this->vwork[4].z + 150.0f, 10.0f);
            this->timer_0BC = 4;
            this->state = 4;
            break;

        case 4:
            if (this->timer_0BC == 0) {
                this->obj.pos.x = this->vwork[4].x;
                this->obj.pos.y = this->vwork[4].y;
                this->obj.pos.z = this->vwork[4].z;
                this->itemDrop = D_i3_801C04C4[this->iwork[1]];
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_AQ_PILLAR_BROKE);
            }
            break;

        case 5:
            Math_SmoothStepToAngle(&this->obj.rot.y, this->fwork[0], 0.1f, 10.0f, 0.0001f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 90.0f, 0.1f, 1.0f, 0.0001f);
            if (((gGameFrameCount % 2) == 0) && (this->iwork[2] == 0)) {
                Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f),
                                      this->obj.pos.y + RAND_RANGE(-45.0f, 105.0f),
                                      this->obj.pos.z + RAND_FLOAT_CENTERED(200.0f), 6.0f, 2);
            }

            if ((this->obj.pos.y < (gGroundHeight + 30.0f)) && (this->iwork[2] == 0)) {
                this->iwork[2] = 1;
                this->vel.x = this->vel.y = this->vel.z = this->gravity = 0.0f;
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_AQ_ROCK_BOUND);
                for (j = 0; j < 6; j++) {
                    Effect_Effect364_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                                           this->obj.pos.y + RAND_RANGE(-9.0f, 21.0f),
                                           this->obj.pos.z + RAND_FLOAT_CENTERED(200.0f), 20.0f);
                }
            }
            break;
    }
}

void Aquas_AqStoneColumn_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };
    Actor* this = (Actor*) thisx;

    if (this->state == 3) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[5]);
                break;

            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[2]);
                break;

            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[3]);
                break;
        }
    }
}

void Aquas_AqStoneColumn_Draw(AqStoneColumn* this) {
    Vec3f frameTable[30];

    if (this->state != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_55);
        switch (this->iwork[0]) {
            case 0:
                if (this->state != 0) {
                    if ((this->iwork[3] == 0) && (this->info.drawType == 2)) {
                        Animation_GetFrameData(&aAqStoneColumnAnim, 0, frameTable);
                        Animation_DrawSkeleton(3, aAqStoneColumnSkel, frameTable, NULL,
                                               Aquas_AqStoneColumn_PostLimbDraw, this, gCalcMatrix);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_AQ_6014520);
                    }
                }
                break;
            case 1:
                gSPDisplayList(gMasterDisp++, D_AQ_60137F0);
                break;
            case 2:
                gSPDisplayList(gMasterDisp++, D_AQ_6014030);
                break;
        }
    }
}

void Aquas_801BD3B0(AqFishGroup* this, f32 x, f32 y, f32 z) {
    f32 temp;
    Vec3f src;
    Vec3f dest;

    Math_SmoothStepToAngle(&this->obj.rot.y, this->fwork[6], 0.1f, 100.0f, 0.00001f);
    Math_SmoothStepToAngle(&this->obj.rot.x, this->fwork[7], 0.1f, 100.0f, 0.00001f);

    if ((gGameFrameCount % 4) == 0) {
        this->fwork[6] = Math_RadToDeg(Math_Atan2F(x, z));
        temp = sqrtf(SQ(x) + SQ(z));
        this->fwork[7] = Math_RadToDeg(-Math_Atan2F(y, temp));

        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Math_SmoothStepToF(&this->fwork[4], 5.0f, 0.1f, 10.0f, 0);

        src.z = this->fwork[4];
        if (this->iwork[2] != 0) {
            src.z = 50.0f;
        }
        src.x = src.y = 0.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        this->vel.x = dest.x;
        this->vel.y = dest.y;
        this->vel.z = dest.z;
    }
}

f32 D_i3_801C04F4[4] = { 700.0f, 300.0f, 600.0f, 400.0f };

void Aquas_AqFishGroup_Update(AqFishGroup* this) {
    s32 j;
    s32 i;
    s32 fishIndex;
    f32 var_fs0;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    Actor* fishGroup;

    if (this->state == 2) {
        var_fs0 = (this->iwork[3] != 0) ? 2800.0f : 9000.0f;
        if (fabsf(this->fwork[5] - this->obj.pos.z) >= var_fs0) {
            this->state = 3;
            if (this->iwork[0] == 0) {
                AUDIO_PLAY_SFX(NA_SE_OB_FISH_AWAY, this->sfxSource, 4);
            }
        } else {
            // needed to match
        }
    }

    switch (this->state) {
        case 0:
            if (this->obj.rot.z != 0) {
                this->iwork[3] = 1;
                this->obj.rot.z = 0.0f;
            }
            this->state = 1;
            this->fwork[5] = this->obj.pos.z;
            break;

        case 1:
            fishIndex = this->index;
            for (i = 0; i < 15; i++) {
                for (j = 0, fishGroup = &gActors[0]; j < ARRAY_COUNT(gActors); j++, fishGroup++) {
                    if (fishGroup->obj.status == OBJ_FREE) {
                        Actor_Initialize(fishGroup);
                        fishGroup->obj.status = OBJ_INIT;
                        fishGroup->obj.id = OBJ_ACTOR_AQ_FISHGROUP;
                        fishGroup->iwork[4] = fishIndex;
                        fishGroup->iwork[0] = i + 1;
                        fishGroup->iwork[3] = this->iwork[3];

                        fishIndex = j;

                        var_fs0 = 100.0f;
                        if (Rand_ZeroOne() < 0.5f) {
                            var_fs0 = -100.0f;
                        }

                        fishGroup->obj.pos.x = this->obj.pos.x + ((s32) (i % 8U) * var_fs0) + RAND_FLOAT(50.0f);
                        fishGroup->obj.pos.y =
                            this->obj.pos.y + ((s32) (i % 8U) * (var_fs0 / 2.0f)) + RAND_FLOAT(30.0f);
                        fishGroup->obj.pos.z = this->obj.pos.z + (i * 20.0f) + RAND_FLOAT(-18.0f);
                        fishGroup->animFrame = RAND_FLOAT(20.0f);
                        fishGroup->fwork[5] = this->fwork[5];
                        fishGroup->state = 2;

                        Object_SetInfo(&fishGroup->info, fishGroup->obj.id);
                        break;
                    }
                }
            }
            this->state = 2;
            break;

        case 2:
            if (this->obj.pos.y < gGroundHeight + 30.0f) {
                this->obj.pos.y = gGroundHeight + 30.0f;
            }

            if ((this->iwork[2] != 0) || (this->timer_0BE != 0)) {
                this->timer_0BC = 0;
            } else {
                Math_SmoothStepToF(&this->fwork[3], D_i3_801C04F4[this->iwork[1]], 0.1f, 30.0f, 0.0001f);
                Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].cam.eye.z - gPathProgress - this->fwork[3], 0.1f, 30.0f,
                                   0.00001f);
            }

            if ((this->timer_0BC == 0) && (this->iwork[2] == 0) && (this->timer_0BE == 0)) {
                this->timer_0BC = 60;
                this->fwork[1] = RAND_FLOAT_CENTERED(300.0f);
                this->fwork[2] = 50.0f + RAND_FLOAT_CENTERED(100.0f);
                if (this->fwork[2] < gGroundHeight + 30.0f) {
                    this->fwork[2] = gGroundHeight + 30.0f;
                }
                this->iwork[1]++;
                this->iwork[1] &= 3;
            }

            sp5C = gPlayer[0].pos.x - this->obj.pos.x;
            sp58 = gPlayer[0].pos.y - this->obj.pos.y;
            sp54 = gPlayer[0].trueZpos - this->obj.pos.z;

            if (this->timer_0BE == 0) {
                this->iwork[2] = 0;
                if (this->iwork[0] == 0) {
                    if (D_i3_801C4190[5] == 0) {
                        sp5C = gPlayer[0].pos.x + this->fwork[1] - this->obj.pos.x;
                        sp58 = gPlayer[0].pos.y - 100.0f + this->fwork[2] - this->obj.pos.y;
                        sp54 = gPlayer[0].trueZpos - this->fwork[3] - this->obj.pos.z;
                    } else if ((D_i3_801C41B8[21] != 0) && (D_i3_801C41B8[22] != 0) && (D_i3_801C41B8[23] != 0)) {
                        sp5C = D_i3_801C41B8[21] - this->obj.pos.x;
                        sp58 = D_i3_801C41B8[22] - this->obj.pos.y;
                        sp54 = D_i3_801C41B8[23] - this->obj.pos.z;
                        this->iwork[2] = 1;
                    }
                } else if (D_i3_801C4190[5] == 0) {
                    fishGroup = &gActors[this->iwork[4]];
                    if ((this->iwork[0] - 1 == fishGroup->iwork[0]) && (fishGroup->obj.status != OBJ_FREE) &&
                        (fishGroup->obj.id == OBJ_ACTOR_AQ_FISHGROUP)) {
                        sp5C = fishGroup->obj.pos.x + (this->fwork[1] / 2.0f) - this->obj.pos.x;
                        sp58 = fishGroup->obj.pos.y + (this->fwork[2] / 2.0f) - this->obj.pos.y;
                        sp54 = fishGroup->obj.pos.z - this->obj.pos.z;
                    } else {
                        this->iwork[0]--;
                        sp5C = gPlayer[0].pos.x + this->fwork[1] - this->obj.pos.x;
                        sp58 = gPlayer[0].pos.y + this->fwork[2] - this->obj.pos.y;
                        sp54 = gPlayer[0].trueZpos - this->fwork[3] - this->obj.pos.z;
                        if (this->iwork[0] < 0) {
                            this->iwork[0] = 0;
                        }
                    }
                } else if ((D_i3_801C41B8[21] != 0) && (D_i3_801C41B8[22] != 0) && (D_i3_801C41B8[23] != 0)) {
                    i = this->iwork[0];

                    var_fs0 = 50.0f;
                    if (Rand_ZeroOne() < 0.5f) {
                        var_fs0 = -50.0f;
                    }

                    sp5C = D_i3_801C41B8[21] + ((s32) (i % 8U) * var_fs0) + RAND_FLOAT(50.0f) - this->obj.pos.x;
                    sp58 =
                        D_i3_801C41B8[22] + ((s32) (i % 8U) * (var_fs0 / 2.0f)) + RAND_FLOAT(50.0f) - this->obj.pos.y;
                    sp54 = D_i3_801C41B8[23] + RAND_FLOAT(50.0f) - this->obj.pos.z;
                    this->iwork[2] = 1;
                }
                if (1) {}
            }

            if ((this->iwork[2] != 0) && (D_i3_801C4190[5] == 0)) {
                this->iwork[2] = 0;
                this->fwork[4] = 40.0f;
                this->timer_0BE = 20;
            }
            Aquas_801BD3B0(this, sp5C, sp58, sp54);
            break;

        case 3:
            sp5C = gPlayer[0].pos.x + this->fwork[1] - this->obj.pos.x;
            sp58 = gPlayer[0].pos.y + this->fwork[2] - this->obj.pos.y;
            sp54 = gPlayer[0].trueZpos + 10000.0f - this->fwork[3] - this->obj.pos.z;

            this->iwork[2] = 1;

            Aquas_801BD3B0(this, sp5C, sp58, sp54);

            if ((gPlayer[0].trueZpos + 1000.0f) < this->obj.pos.z) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }

    this->animFrame++;
    if (Animation_GetFrameCount(&aAqFishGroupAnim) < this->animFrame) {
        this->animFrame = 0;
    }
}

bool Aquas_AqFishGroup_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    if ((limbIndex == 1) || (limbIndex == 2) || (limbIndex == 5)) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    return false;
}

void Aquas_AqFishGroup_Draw(AqFishGroup* this) {
    Animation_GetFrameData(&aAqFishGroupAnim, this->animFrame, this->vwork);
    if (this->iwork[3] == 0) {
        Animation_DrawSkeleton(1, aAqFishGroupSkel1, this->vwork, Aquas_AqFishGroup_OverrideLimbDraw, NULL, this,
                               &gIdentityMatrix);
    } else {
        Animation_DrawSkeleton(1, aAqFishGroupSkel2, this->vwork, Aquas_AqFishGroup_OverrideLimbDraw, NULL, this,
                               &gIdentityMatrix);
    }
}

Vec3f D_i3_801C0504[50] = {
    { 416.0f, 440.0f, -4182.0f }, { 437.0f, 440.0f, -4178.0f }, { 510.0f, 420.0f, -4156.0f },
    { 168.0f, 361.0f, -4168.0f }, { 434.0f, 440.0f, -4162.0f }, { 465.0f, 465.0f, -4146.0f },
    { 464.0f, 493.0f, -4124.0f }, { 426.0f, 395.0f, -4136.0f }, { 457.0f, 440.0f, -4112.0f },
    { 480.0f, 487.0f, -4110.0f }, { 454.0f, 440.0f, -4256.0f }, { 179.0f, 507.0f, -4272.0f },
    { 442.0f, 392.0f, -4242.0f }, { 450.0f, 481.0f, -4248.0f }, { 474.0f, 420.0f, -4232.0f },
    { 376.0f, 440.0f, -4196.0f }, { 463.0f, 507.0f, -4190.0f }, { 467.0f, 424.0f, -4208.0f },
    { 394.0f, 404.0f, -4186.0f }, { 256.0f, 440.0f, -3680.0f }, { 243.0f, 515.0f, -3648.0f },
    { 277.0f, 390.0f, -3662.0f }, { 234.0f, 457.0f, -3664.0f }, { 561.0f, 440.0f, -4332.0f },
    { 550.0f, 514.0f, -4346.0f }, { 568.0f, 404.0f, -4304.0f }, { 580.0f, 545.0f, -4350.0f },
    { 552.0f, 382.0f, -4292.0f }, { 528.0f, 462.0f, -4322.0f }, { 558.0f, 440.0f, -4294.0f },
    { 396.0f, 440.0f, -4284.0f }, { 391.0f, 363.0f, -4254.0f }, { 379.0f, 501.0f, -4254.0f },
    { 428.0f, 440.0f, -4246.0f }, { 374.0f, 440.0f, -4282.0f }, { 373.0f, 342.0f, -4290.0f },
    { 353.0f, 570.0f, -4266.0f }, { 359.0f, 440.0f, -4232.0f }, { 399.0f, 216.0f, -4246.0f },
    { 406.0f, 251.0f, -4222.0f }, { 380.0f, 189.0f, -4248.0f }, { 370.0f, 278.0f, -4214.0f },
    { 383.0f, 237.0f, -4266.0f }, { 360.0f, 299.0f, -4320.0f }, { 359.0f, 266.0f, -4280.0f },
    { 354.0f, 211.0f, -4256.0f }, { 391.0f, 238.0f, -4192.0f }, { 340.0f, 294.0f, -4216.0f },
    { 423.0f, 242.0f, -4200.0f }, { 429.0f, 311.0f, -4138.0f },
};
f32 D_i3_801C075C[51] = {
    28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f,  28.0f,  28.0f,  28.0f,  28.0f, 28.0f, 28.0f,
    28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 320.0f, 320.0f, 320.0f, 320.0f, 40.0f, 40.0f, 40.0f,
    40.0f, 40.0f, 40.0f, 40.0f, 28.0f, 28.0f, 28.0f,  28.0f,  28.0f,  28.0f,  28.0f, 28.0f, 28.0f,
    28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f,  28.0f,  28.0f,  10.0f,  28.0f, 28.0f,
};
f32 D_i3_801C0828[51] = {
    210.0f, 250.0f, 170.0f, 200.0f, 225.0f, 240.0f, 220.0f, 180.0f, 210.0f, 230.0f, 355.0f, 349.0f, 357.0f,
    12.0f,  357.0f, 65.0f,  256.0f, 250.0f, 88.0f,  0.0f,   0.0f,   0.0f,   9.0f,   14.0f,  35.0f,  40.0f,
    5.0f,   92.0f,  56.0f,  71.0f,  355.0f, 326.0f, 30.0f,  5.0f,   30.0f,  30.0f,  60.0f,  69.0f,  1.0f,
    346.0f, 30.0f,  97.0f,  30.0f,  30.0f,  30.0f,  30.0f,  162.0f, 98.0f,  10.0f,  213.0f, 30.0f,
};

void Aquas_801BDF14(void) {
    ActorCutscene* actor = &gActors[1];
    s32 i;

    for (i = 0; i < 50; i++, actor++) {
        Actor_Initialize(actor);
        actor->obj.status = OBJ_INIT;
        actor->obj.id = OBJ_ACTOR_CUTSCENE;
        actor->obj.pos.x = D_i3_801C0504[i].x;
        actor->obj.pos.y = D_i3_801C0504[i].y;
        actor->obj.pos.z = D_i3_801C0504[i].z;
        actor->rot_0F4.y = D_i3_801C075C[i];
        actor->animFrame = ACTOR_CS_AQ_FISHGROUP;
        actor->iwork[0] = RAND_INT(20.0f);
        actor->iwork[2] = i;
        actor->timer_0BC = 231;
        actor->fwork[0] = 4.5f;
        Object_SetInfo(&actor->info, actor->obj.id);
    }
}

void Aquas_CsAqFishGroup_Update(AqFishGroup* this) {
    f32 temp;

    if (this->timer_0BC == 0) {
        this->fwork[0] = 10.0f;
        temp = D_i3_801C0828[this->iwork[2]];
        Math_SmoothStepToAngle(&this->rot_0F4.y, temp, 1.0f, 100.0f, 0.00001f);
    }

    this->iwork[0]++;
    if (this->iwork[0] >= Animation_GetFrameCount(&aAqFishGroupAnim)) {
        this->iwork[0] = 0;
    }

    if (gPlayer[0].csState >= 5) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Aquas_801BE0F0(ActorCutscene* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_61);
    Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 255, 255);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_SetGfxMtx(&gMasterDisp);
    Animation_GetFrameData(&aAqFishGroupAnim, this->iwork[0], this->vwork);
    Animation_DrawSkeleton(1, aAqFishGroupSkel1, this->vwork, NULL, NULL, this, &gIdentityMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Aquas_AqBump2_Draw(AqBump2* this) {
    Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aAqBump2DL);
}

void Aquas_801BE274(AqOyster* this, f32 yRot, f32 xRot) {
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp40;

    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);

    sp40.x = sp40.y = 0.0f;
    sp40.z = 50.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp40, &sp64);

    sp64.x += this->obj.pos.x;
    sp64.y += this->obj.pos.y + 8.0f;
    sp64.z = this->obj.pos.z;

    sp40.x = sp40.y = 0.0f;
    sp40.z = 80.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp40, &sp58);
    func_effect_8007F04C(OBJ_EFFECT_355, sp64.x, sp64.y, sp64.z, xRot, yRot, 0.0f, 0.0f, 0.0f, 0.0f, sp58.x, sp58.y,
                         sp58.z, 1.0f);
}

void Aquas_AqOyster_Update(AqOyster* this) {
    s32 i;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;

    switch (this->state) {
        case 0:
            this->health = 30;
            this->fwork[0] = 1.0f;
            this->fwork[1] = 0.9f;
            this->fwork[2] = 0.8f;
            this->state++;
            break;

        case 1:
            if (fabsf(gPlayer[0].pos.z - this->obj.pos.z) <= 3000.0f) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_AQ_60314E4);
                this->info.damage = 0;
                this->info.bonus = 1;
                this->timer_0BC = 40.0f + RAND_FLOAT(30.0f);
                this->state++;
            }
            break;

        case 2:
            this->animFrame++;
            if (this->animFrame == 10) {
                for (i = 0; i < 10; i++) {
                    Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f),
                                          this->obj.pos.y + 50.0f + RAND_FLOAT_CENTERED(70.0f),
                                          this->obj.pos.z + 100.0f, 3.0f, 2);
                }
            }

            if ((this->animFrame == 18) && (this->health != 0)) {
                this->animFrame = 17;
                if ((fabsf(this->obj.pos.z - gPlayer[0].trueZpos) > 1000.0f) && (this->timer_0BC < 20) &&
                    ((this->timer_0BC & 3) == 0)) {
                    sp68 = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(200.0f) - this->obj.pos.x;
                    sp64 = gPlayer[0].pos.y + RAND_FLOAT_CENTERED(200.0f) - this->obj.pos.y;
                    sp60 = gPlayer[0].trueZpos - this->obj.pos.z;

                    sp58 = Math_RadToDeg(Math_Atan2F(sp68, sp60));
                    sp5C = Math_RadToDeg(-Math_Atan2F(sp64, sqrtf(SQ(sp68) + SQ(sp60))));

                    Aquas_801BE274(this, sp58, sp5C);

                    if (this->timer_0BC == 0) {
                        this->timer_0BC = 40.0f + RAND_FLOAT(30.0f);
                    }
                }
            }

            if (this->animFrame >= Animation_GetFrameCount(&aAqOysterAnim)) {
                this->info.bonus = 0;
                this->animFrame = Animation_GetFrameCount(&aAqOysterAnim) - 1;
                this->state++;
            }
            break;

        case 3:
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->health != 0) {
            if (this->state == 2) {
                this->health -= this->damage;
                if (this->health <= 0) {
                    this->health = this->itemDrop = 0;
                    Actor_Despawn(this);

                    for (i = 0; i < 10; i++) {
                        Aquas_Effect366_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f),
                                              this->obj.pos.y + 50.0f + RAND_FLOAT_CENTERED(70.0f),
                                              this->obj.pos.z + 100.0f, 3.0f, 2);
                    }

                    for (i = 0; i < 3; i++) {
                        func_effect_80081A8C(this->obj.pos.x + RAND_FLOAT(15.0f), this->obj.pos.y + RAND_FLOAT(3.0f),
                                             this->obj.pos.z + RAND_FLOAT(5.0f), 1.0f + RAND_FLOAT(0.5f), 7);
                    }
                    func_effect_800815DC();
                    Effect_FireSmoke_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 51.0f, 10.0f);
                }
            }

            if (this->state == 1) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_AQ_60314E4);
                this->info.damage = 0;
                this->info.bonus = 1;
                this->state = 2;
            }
        }
    }
}

void Aquas_AqOyster_Draw(AqOyster* this) {
    Graphics_SetScaleMtx(3.0f);
    RCP_SetupDL(&gMasterDisp, SETUPDL_56);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 143, 143, 255);
    Animation_GetFrameData(&aAqOysterAnim, this->animFrame, this->vwork);
    Animation_DrawSkeleton(1, aAqOysterSkel, this->vwork, NULL, NULL, &this->index, &gIdentityMatrix);

    if (this->health != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_55);
        Matrix_Scale(gGfxMatrix, this->fwork[0], this->fwork[1], this->fwork[2], MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, -8.0f, 51.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aAqOysterDL);
    }
}

// OBJ_BOSS_AQ_UNK_301 action
void Aquas_Boss301_Update(Boss301* this) {
    /* Unimplemented */
}

// OBJ_BOSS_AQ_UNK_301 draw
void Aquas_Boss301_Draw(Boss301* this) {
    /* Unimplemented */
}

// OBJ_ACTOR_AQ_UNK_188 action
void Aquas_Actor188_Update(Actor188* this) {
    /* Unimplemented */
}

// OBJ_ACTOR_AQ_UNK_188 draw
void Aquas_Actor188_Draw(Actor188* this) {
    /* Unimplemented */
}

void Aquas_Update360(Player* player) {
    /* Unimplemented */
}

void Aquas_801BEC8C(void* arg0) {
    /* Unimplemented */
}
