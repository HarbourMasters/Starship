#include "global.h"
#include "assets/ast_titania.h"
#include "prevent_bss_reordering.h"

void Ground_801B5244(s32 arg0, s32 arg1);
void Ground_801B5FE0(s32 arg0, s32 arg1, s32 arg2);
void Ground_801B68A8(Gfx** dlist, s32 arg1, s32 arg2);

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x20 */ f32 unk_20;
} UnkStruct_801C62E8; // size = 0x24

typedef union {
    f32 a[3];
    Vec3f v;
} Vec3fa;

Vtx D_i5_801BA910[4] = {
    VTX(-3410, 0, -5720, 0, 0, 0, 127, 0, 255),
    VTX(-3410, 0, 0, 0, 26624, 0, 127, 0, 255),
    VTX(3410, 0, 0, -32768, 26624, 0, 127, 0, 255),
    VTX(3410, 0, -5720, -32768, 0, 0, 127, 0, 255),
};
Gfx D_i5_801BA950[4] = {
    gsSPVertex(D_i5_801BA910, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
u8 D_i5_801BA970[12] = {
    0, 0, 0, 0, 4, 5, 6, 7, 0, 0, 0, 0,
};
s32 D_i5_801BA97C[6] = {
    1, 0, 0, 1, 1, 0,
};
s32 D_i5_801BA994[6] = {
    0, 0, 1, 1, 0, 0,
};
f32 D_i5_801BA9AC[6] = {
    220.0f, 0.0f, 0.0f, 220.0f, 220.0f, 0.0f,
};
f32 D_i5_801BA9C4[6] = {
    0.0f, 0.0f, 220.0f, 220.0f, 0.0f, 0.0f,
};

f32 D_i5_801BE740;
f32 D_i5_801BE744;
Vtx D_i5_801BE748[27][16][2];
s32 D_i5_801C1D48[28][16];
f32 D_i5_801C2448[28];
f32 D_i5_801C24B8[28];
Gfx D_i5_801C2528[27][65];
Gfx* D_i5_801C5C00;
s32 D_i5_801C5C04;
s32 D_i5_801C5C08;
s32 D_i5_801C5C0C;
f32 D_i5_801C5C10;
s32 D_i5_801C5C14;
Mtx D_i5_801C5C18[27];
Vec3f D_i5_801C62D8;
UnkStruct_801C62E8 D_i5_801C62E8[20];
Vec3fa D_i5_801C65B8[3][15][4];
s32 D_i5_801C6E28[4][3];

bool Ground_801B49D0(Actor* actor) {
    s32 i;
    bool found = false;
    UnkStruct_801C62E8* var_v0 = D_i5_801C62E8;

    for (i = 0; i < ARRAY_COUNT(D_i5_801C62E8); i++, var_v0++) {
        if (var_v0->unk_00 == 0) {
            found = true;
            var_v0->unk_00 = 1;
            var_v0->unk_04 = actor->obj.pos.y;
            var_v0->unk_08 = actor->obj.pos.x;
            var_v0->unk_0C = actor->obj.pos.z;
            var_v0->unk_10 = actor->obj.rot.x;
            var_v0->unk_14 = actor->obj.rot.y;
            var_v0->unk_18 = actor->obj.rot.z;
            break;
        }
    }
    actor->obj.status = 0;
    return found;
}

void Ground_801B4A54(UnkStruct_801C62E8* arg0) {
    // Lots of conversions between floats, and ints unnecessarily here because of this chain assignment.
    arg0->unk_00 = arg0->unk_04 = arg0->unk_08 = arg0->unk_0C = arg0->unk_10 = arg0->unk_14 = arg0->unk_18 =
        arg0->unk_1C = arg0->unk_20 = 0;
}

void Ground_801B4AA8(s32* arg0, s32* arg1) {
    Actor actor;
    UnkStruct_801C62E8* var_s2 = D_i5_801C62E8;
    s32* var_s1;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 var_fv0;
    f32 var_fv1;
    s32 unk_04;
    f32 unk_08;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(D_i5_801C62E8); i++, var_s2++) {
        if (var_s2->unk_00 != 0) {
            unk_04 = var_s2->unk_04;
            unk_08 = var_s2->unk_08;
            unk_10 = var_s2->unk_10;
            unk_14 = var_s2->unk_14;
            unk_18 = var_s2->unk_18;
            var_s1 = arg0;

            if (arg0 == NULL) {
                unk_04 = D_i5_801BA970[unk_04];
            }

            if (var_s2->unk_00 == 1) {
                switch (unk_04) {
                    case 0:
                        break;

                    case 1:
                    case 3:
                        var_s2->unk_20 = var_s2->unk_18;
                        break;

                    case 4:
                        PRINTF("ICHIMAI POLYGON ON\n"); // ONE PLANE POLYGON ON
                        *arg1 |= 2;
                        break;

                    case 5:
                        PRINTF("CHIKEI POLYGON OFF\n"); // TERRAIN POLYGON OFF
                        *arg1 &= ~1;
                        break;

                    case 6:
                        PRINTF("CHIKEI POLYGON ON\n"); // TERRAIN POLYGON ON
                        *arg1 |= 1;
                        break;

                    case 7:
                        PRINTF("ICHIMAI POLYGON OFF\n"); // ONE PLANE POLYGON OFF
                        *arg1 &= ~2;
                        break;

                    case 8:
                        PRINTF("RANDAMU YAMA\n"); // RANDOM MOUNTAIN
                        var_s2->unk_20 = 5000.0f;
                        break;
                }
                var_s2->unk_00 = 2;
            }

            switch (unk_04) {
                case 0:
                    break;

                case 1:
                    for (j = 0; j < 16; j++, var_s1++) {
                        temp_fs0 = (j * 220.0f * D_i5_801BE740) - 1760.0f - unk_08;
                        if (fabsf(temp_fs0) <= unk_10) {
                            temp_fs1 = __sinf((var_s2->unk_20 / unk_18) * (M_DTOR * 180.0f));
                            var_fv0 = __cosf((temp_fs0 / unk_10) * (M_DTOR * 90.0f));
                            *var_s1 += var_fv0 * unk_14 * temp_fs1;
                        }
                    }

                    var_s2->unk_20 -= 220.0f;
                    if (var_s2->unk_20 <= 0.0f) {
                        Ground_801B4A54(var_s2);
                    }
                    break;

                case 2:
                    unk_08 += (1760.0f - (unk_10 * 0.5f));
                    var_fv1 = unk_14;

                    if (var_s2->unk_20 <= var_fv1 / (70.0f * M_DTOR)) {
                        var_fv1 = var_s2->unk_20 * (70.0f * M_DTOR);
                    } else if (var_fv1 / (70.0f * M_DTOR) >= (unk_18 - var_s2->unk_20)) {
                        var_fv1 = (unk_18 - var_s2->unk_20) * (70.0f * M_DTOR);
                    }

                    for (j = 0, var_fv0 = 0.0f; j < 16; j++, var_fv0 += 220.0f, var_s1++) {
                        if (unk_08 <= var_fv0 && var_fv0 <= (unk_08 + unk_10) && *var_s1 < var_fv1) {
                            *var_s1 = var_fv1;
                        }
                    }

                    var_s2->unk_20 += 220.0f;
                    if (unk_18 <= var_s2->unk_20) {
                        Ground_801B4A54(var_s2);
                    }
                    break;

                case 3:
                    for (j = 0; j < 16; j++, var_s1++) {
                        temp_fs0 =
                            (j * 220.0f * D_i5_801BE740) - 1760.0f - var_s2->unk_08 +
                            (__sinf(((var_s2->unk_20 * 8.0f) / var_s2->unk_18) * 2 * (M_DTOR * 180.0f)) * 500.0f);
                        if (fabsf(temp_fs0) <= var_s2->unk_10) {
                            temp_fa0 = __cosf((temp_fs0 / var_s2->unk_10) * (M_DTOR * 90.0f));
                            if (temp_fa0 >= 0.7) {
                                temp_fa0 = 0.7f;
                            }
                            *var_s1 -=
                                temp_fa0 * var_s2->unk_14 * 4.0f * ((var_s2->unk_18 - var_s2->unk_20) / var_s2->unk_18);
                        }
                        *var_s1 +=
                            (var_s2->unk_14 - ((var_s2->unk_20 / var_s2->unk_18) * var_s2->unk_14)) * 4.0f * 0.7f;
                    }

                    var_s2->unk_20 -= 220.0f;
                    if (var_s2->unk_20 <= 0.0f) {
                        Ground_801B4A54(var_s2);
                    }
                    break;

                case 8:
                    if (var_s2->unk_1C <= 0) {
                        for (j = 0; j < (s32) var_s2->unk_18; j++) {
                            var_s2->unk_1C = 1;
                            actor.obj.pos.x = RAND_FLOAT(3300.0f) - 1650.0f;
                            actor.obj.pos.z = 0.0f;
                            actor.obj.pos.y = 1.0f;
                            actor.obj.rot.x = var_s2->unk_10 + RAND_FLOAT(var_s2->unk_10) * 0.25f;
                            actor.obj.rot.z = 2.0f * actor.obj.rot.x; // Should this have been obj.rot.y?
                            actor.obj.rot.z = var_s2->unk_14 + RAND_FLOAT(var_s2->unk_14) * 0.25f;
                            Ground_801B49D0(&actor);
                        }

                        var_s2->unk_20 -= 220.0f;
                        if (var_s2->unk_20 <= 0.0f) {
                            Ground_801B4A54(var_s2);
                        }
                    } else {
                        var_s2->unk_1C--;
                    }
                    break;

                default:
                    Ground_801B4A54(var_s2);
                    break;
            }
        }
    }
}

void Ground_801B5110(f32 arg0, f32 arg1, f32 arg2) {
    UnkStruct_801C62E8* ptr;
    s32 i;
    s32 k;

    D_i5_801C5C04 = 0;
    D_i5_801C5C08 = 0;
    D_i5_801C5C0C = 0;
    D_i5_801C5C10 = 0.0f;
    D_i5_801BE740 = D_i5_801BE744 = 1.0f;
    D_i5_801C62D8.x = arg0;
    D_i5_801C62D8.y = arg1;
    D_i5_801C62D8.z = 200.0f; // Probably used to be arg2
    D_i5_801C5C14 = 1;

    for (i = 0, ptr = D_i5_801C62E8; i < ARRAY_COUNT(D_i5_801C62E8); i++, ptr++) {
        Ground_801B4A54(ptr);
    }

    for (i = 0; i < ARRAY_COUNT(D_i5_801C1D48); i++) {
        for (k = 0; k < ARRAY_COUNT(D_i5_801C1D48[0]); k++) {
            D_i5_801C1D48[i][k] = 0;
        }
        D_i5_801C2448[i] = D_i5_801C24B8[i] = 1.0f;
    }
    Ground_801B5244(D_i5_801C5C04, D_i5_801C5C08);
}

void Ground_801B5244(s32 arg0, s32 arg1) {
    s32 var_s5;
    s32 var_s6;
    s32 sp6C;
    s32 ia2;
    s32 iv1;
    s32 sp60 = arg0;
    s32 sp5C = arg1;
    Vtx* v0;
    Vtx* v1;

    for (sp6C = 0; sp6C < 27; sp6C++) {
        for (ia2 = 0; ia2 < 16; ia2++) {
            v0 = &D_i5_801BE748[sp60][ia2][0];
            v1 = &D_i5_801BE748[sp60][ia2][1];

            if (ia2 != 0) {
                v0->n.ob[0] = (D_i5_801C2448[sp5C] * ((ia2 * 220.0f) - 1760.0f));
            } else {
                v0->n.ob[0] = -4000;
            }

            if (ia2 != 15) {
                v1->n.ob[0] = (D_i5_801C2448[(sp5C + 1) % 28] * ((ia2 * 220.0f) - 1760.0f));
            } else {
                v0[1].n.ob[0] = 4000;
            }

            v0 = &D_i5_801BE748[sp60][ia2][0];
            v0->n.ob[2] = D_i5_801C24B8[sp5C] * -220.0f;
            v1->n.ob[2] = 0;
            v0->n.ob[1] = D_i5_801C1D48[sp5C][ia2];
            v1->n.ob[1] = D_i5_801C1D48[(sp5C + 1) % 28][ia2];

            for (iv1 = 0; iv1 < 2; iv1++) {
                D_i5_801BE748[sp60][ia2][iv1].n.tc[0] = (ia2 % 2) * 0x400;
                D_i5_801BE748[sp60][ia2][iv1].n.tc[1] = iv1 * 0x400;
            }
        }
        sp60 = (sp60 + 1) % 27;
        sp5C = (sp5C + 1) % 28;
    }

    sp60 = arg0;
    sp5C = arg1;

    for (sp6C = 0; sp6C < 27; sp6C++) {
        D_i5_801C5C00 = D_i5_801C2528[sp60];

        for (ia2 = 0, var_s6 = 15; var_s6 < 30; ia2++, var_s6 += 15) {
            var_s5 = (var_s6 < 15) ? 15 : 14;
            gSPVertex(D_i5_801C5C00++, &D_i5_801BE748[sp60][ia2 * 15][0], (var_s5 + 2) * 2, 0);
            for (iv1 = 0; iv1 <= var_s5; iv1++) {
                gSP1Triangle(D_i5_801C5C00++, (iv1 << 1), (iv1 << 1) + 1, (iv1 << 1) + 3, 0);
                gSP1Triangle(D_i5_801C5C00++, (iv1 << 1), (iv1 << 1) + 3, (iv1 << 1) + 2, 0);
            }
        }
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, D_i5_801C24B8[sp5C] * -220.0f, MTXF_NEW);
        Matrix_ToMtx(&D_i5_801C5C18[sp60]);
        gSPMatrix(D_i5_801C5C00++, &D_i5_801C5C18[sp60], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPEndDisplayList(D_i5_801C5C00++);
        sp5C = (sp5C + 1) % 28;
        sp60 = (sp60 + 1) % 27;
    }
    Ground_801B5FE0(arg1, arg0, 27);
}

void Ground_801B58AC(Gfx** dList, f32 arg1) {
    s32 spC4;
    s32 temp_hi;
    s32 i;
    Vtx* temp_t1;
    Vtx* temp_v0;

    RCP_SetupDL(dList, 0x1D);
    RCP_SetFog(dList, gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

    spC4 = D_i5_801C5C14;

    if (D_i5_801C5C14 & 2) {
        gDPSetupTile((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, G_TX_MIRROR | G_TX_WRAP,
                     G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPLoadTileTexture((*dList)++, D_TI_6001BA8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
        gSPMatrix((*dList)++, &gIdentityMtx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        Matrix_Translate(gGfxMatrix, D_i5_801C62D8.x, D_i5_801C62D8.y, D_i5_801C62D8.z + D_i5_801C5C10, MTXF_NEW);
        Matrix_ToMtx(gGfxMtx);
        gSPMatrix((*dList)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList((*dList)++, D_i5_801BA950);
        gSPPopMatrix((*dList)++, G_MTX_MODELVIEW);
        Ground_801B4AA8(NULL, &spC4);
    }

    if (D_i5_801C5C14 & 1) {
        if (D_i5_801C5C0C == 1) {
            D_i5_801C5C0C = 0;
            temp_hi = (D_i5_801C5C08 + 27) % 28;
            for (i = 0; i < ARRAY_COUNT(D_i5_801C1D48[0]); i++) {
                D_i5_801C1D48[temp_hi][i] = 0;
            }
            D_i5_801C2448[temp_hi] = D_i5_801BE740;
            D_i5_801C24B8[temp_hi] = D_i5_801BE744;
            Ground_801B4AA8(D_i5_801C1D48[temp_hi], &spC4);
            for (i = 0; i < 16; i++) {
                temp_v0 = &D_i5_801BE748[D_i5_801C5C04][i][0];
                temp_t1 = &D_i5_801BE748[D_i5_801C5C04][i][1];
                if ((i != 0) && (i != 15)) {
                    temp_v0->v.ob[0] = D_i5_801C2448[D_i5_801C5C08] * ((i * 220.0f) - 1760.0f);
                } else if (i == 0) {
                    temp_v0->v.ob[0] = -4000;
                } else { // i == 15
                    temp_v0->v.ob[0] = 4000;
                }
                if ((i != 0) && (i != 15)) {
                    temp_t1->v.ob[0] = D_i5_801C2448[(D_i5_801C5C08 + 1) % 28] * ((i * 220.0f) - 1760.0f);
                } else if (i == 0) {
                    temp_t1->v.ob[0] = -4000;
                } else { // i == 15
                    temp_t1->v.ob[0] = 4000;
                }
                temp_v0->v.ob[1] = D_i5_801C1D48[D_i5_801C5C08][i];
                temp_t1->v.ob[1] = D_i5_801C1D48[(D_i5_801C5C08 + 1) % 28][i];

                D_i5_801BE748[(D_i5_801C5C04 + 27) % 27][i][0].v.ob[2] =
                    D_i5_801C24B8[(D_i5_801C5C08 + 29) % 28] * -220.0f;
                D_i5_801BE748[(D_i5_801C5C04 + 27) % 27][i][1].v.ob[2] = 0;

                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, D_i5_801C24B8[D_i5_801C5C08] * -220.0f, MTXF_NEW);
                Matrix_ToMtx(&D_i5_801C5C18[D_i5_801C5C04]);
            }
            Ground_801B5FE0(D_i5_801C5C08, D_i5_801C5C04, 1);
        }
        gSPMatrix((*dList)++, &gIdentityMtx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        Ground_801B68A8(dList, D_i5_801C5C04, 1);
        gSPPopMatrix((*dList)++, G_MTX_MODELVIEW);
    }

    D_i5_801C5C10 += arg1;

    if ((D_i5_801C5C14 & 1) && (D_i5_801C24B8[(D_i5_801C5C08 + 25) % 28] * 220.0f <= D_i5_801C5C10)) {
        D_i5_801C5C0C = 1;
        D_i5_801C5C10 = Math_ModF(D_i5_801C5C10, D_i5_801C24B8[(D_i5_801C5C08 + 25) % 28] * 220.0f);
        D_i5_801C5C04 = (D_i5_801C5C04 + 26) % 27;
        D_i5_801C5C08 = (D_i5_801C5C08 + 27) % 28;
    }

    if (D_i5_801C5C14 & 2) {
        D_i5_801C5C10 = Math_ModF(D_i5_801C5C10, 220.0f * D_i5_801BE744);
    }

    D_i5_801C5C14 = spC4;
}

void Ground_801B5FE0(s32 arg0, s32 arg1, s32 arg2) {
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    Vec3f v1;
    Vec3f v2;
    Vec3f v3;
    f32 var_fv0;
    s32 j1;
    s32 j3;
    s32 j2;
    s32 sp9C;
    s32 i1;
    s32 i2;
    s32 sp90;
    s32 i0 = 0;
    s32 var_s1 = (arg0 + 27) % 28;

    for (sp9C = 0; sp9C < arg2 + 2; sp9C++, var_s1++) {
        for (i1 = 0; i1 < 15; i1++) {
            for (i2 = 0; i2 < 4; i2++) {
                spF4 = D_i5_801BA9AC[i2 + 0] * D_i5_801C2448[(D_i5_801BA994[i2 + 0] + var_s1) % 28];
                spF0 = D_i5_801BA9AC[i2 + 1] * D_i5_801C2448[(D_i5_801BA994[i2 + 1] + var_s1) % 28];
                spEC = D_i5_801BA9AC[i2 + 2] * D_i5_801C2448[(D_i5_801BA994[i2 + 2] + var_s1) % 28];

                spE8 = D_i5_801C1D48[(D_i5_801BA994[i2 + 0] + var_s1) % 28][i1 + D_i5_801BA97C[i2 + 0]];
                spE4 = D_i5_801C1D48[(D_i5_801BA994[i2 + 1] + var_s1) % 28][i1 + D_i5_801BA97C[i2 + 1]];
                spE0 = D_i5_801C1D48[(D_i5_801BA994[i2 + 2] + var_s1) % 28][i1 + D_i5_801BA97C[i2 + 2]];

                spDC = D_i5_801BA9C4[i2 + 0] * D_i5_801C24B8[(D_i5_801BA994[i2 + 0] + var_s1) % 28];
                spD8 = D_i5_801BA9C4[i2 + 1] * D_i5_801C24B8[(D_i5_801BA994[i2 + 1] + var_s1) % 28];
                spD4 = D_i5_801BA9C4[i2 + 2] * D_i5_801C24B8[(D_i5_801BA994[i2 + 2] + var_s1) % 28];

                v1.x = spF0 - spF4;
                v2.x = spEC - spF0;
                v1.y = spE4 - spE8;
                v2.y = spE0 - spE4;
                v1.z = spD8 - spDC;
                v2.z = spD4 - spD8;

                v3.x = (v1.y * v2.z) - (v1.z * v2.y);
                v3.y = (v1.z * v2.x) - (v1.x * v2.z);
                v3.z = (v1.x * v2.y) - (v1.y * v2.x);

                var_fv0 = VEC3F_MAG(&v3);

                D_i5_801C65B8[i0][i1][i2].a[0] = (v3.x * 127.0f) / var_fv0;
                D_i5_801C65B8[i0][i1][i2].a[1] = (v3.y * 127.0f) / var_fv0;
                D_i5_801C65B8[i0][i1][i2].a[2] = (v3.z * 127.0f) / var_fv0;
            }
        }

        if (i0 < 2) {
            i0++;
        }

        if (sp9C >= 2) {
            if (sp9C == 2) {
                sp90 = (arg1 + 27) % 27;
            }

            for (i1 = 0; i1 < 15; i1++) {
                j1 = ((i1 + 1) * (i1 != 14)) + ((i1 == 14) * 14);
                j3 = i1;
                j2 = (i1 - 1) * (i1 != 0);

                for (i2 = 0; i2 < 3; i2++) {
                    D_i5_801C6E28[0][i2] = (D_i5_801C65B8[0][j2][2].a[i2] + D_i5_801C65B8[1][j2][3].a[i2] +
                                            D_i5_801C65B8[1][j3][0].a[i2] + D_i5_801C65B8[0][j3][1].a[i2]) /
                                           4.0f;
                    D_i5_801C6E28[1][i2] = (D_i5_801C65B8[1][j2][2].a[i2] + D_i5_801C65B8[2][j2][3].a[i2] +
                                            D_i5_801C65B8[2][j3][0].a[i2] + D_i5_801C65B8[1][j3][1].a[i2]) /
                                           4.0f;
                    D_i5_801C6E28[2][i2] = (D_i5_801C65B8[1][j3][2].a[i2] + D_i5_801C65B8[2][j3][3].a[i2] +
                                            D_i5_801C65B8[2][j1][0].a[i2] + D_i5_801C65B8[1][j1][1].a[i2]) /
                                           4.0f;
                    D_i5_801C6E28[3][i2] = (D_i5_801C65B8[0][j3][2].a[i2] + D_i5_801C65B8[1][j3][3].a[i2] +
                                            D_i5_801C65B8[1][j1][0].a[i2] + D_i5_801C65B8[0][j1][1].a[i2]) /
                                           4.0f;
                }

                for (i2 = 0; i2 < 4; i2++) {
                    var_fv0 = sqrtf(SQ(D_i5_801C6E28[i2][0]) + SQ(D_i5_801C6E28[i2][1]) + SQ(D_i5_801C6E28[i2][2]));
                    D_i5_801C6E28[i2][0] = (D_i5_801C6E28[i2][0] / var_fv0) * 127.0f;
                    D_i5_801C6E28[i2][1] = (D_i5_801C6E28[i2][1] / var_fv0) * 127.0f;
                    D_i5_801C6E28[i2][2] = (D_i5_801C6E28[i2][2] / var_fv0) * 127.0f;
                }

                for (i2 = 0; i2 < 3; i2++) {
                    D_i5_801BE748[sp90][i1][0].n.n[i2] = D_i5_801C6E28[0][i2];
                    D_i5_801BE748[sp90][i1][1].n.n[i2] = D_i5_801C6E28[1][i2];
                    D_i5_801BE748[sp90][i1 + 1][1].n.n[i2] = D_i5_801C6E28[2][i2];
                    D_i5_801BE748[sp90][i1 + 1][0].n.n[i2] = D_i5_801C6E28[3][i2];
                }
            }

            sp90 = (sp90 + 1) % 27;

            for (i1 = 0; i1 < 15; i1++) {
                for (i2 = 0; i2 < 3; i2++) {
                    D_i5_801C65B8[1][i1][i2] = D_i5_801C65B8[2][i1][i2];
                    D_i5_801C65B8[0][i1][i2] = D_i5_801C65B8[1][i1][i2];
                }
            }
        }
    }
}

void Ground_801B68A8(Gfx** dlist, s32 arg1, s32 arg2) {
    s32 var_a0;
    s32 var_a1;
    s32 var;

    gDPSetupTile((*dlist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, G_TX_MIRROR | G_TX_WRAP,
                 G_TX_MIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadTileTexture((*dlist)++, D_TI_6001BA8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
    Matrix_Translate(gGfxMatrix, D_i5_801C62D8.x, D_i5_801C62D8.y, D_i5_801C62D8.z + D_i5_801C5C10, MTXF_NEW);
    Matrix_ToMtx(gGfxMtx);
    gSPMatrix((*dlist)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    var = 1;
    var_a0 = (arg1 + 25) % 27;
    for (var_a1 = 26; var_a1 >= var; var_a1--) {
        gSPDisplayList((*dlist)++, &D_i5_801C2528[var_a0]);
        var_a0 = (var_a0 + 26) % 27;
    }
}

bool Ground_801B6AEC(f32 arg0, f32 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    Ground_801B6E20(arg0, arg2, &sp2C, &sp28, &sp24);
    if (arg1 < sp28) {
        return true;
    } else {
        return false;
    }
}

s32 Ground_801B6B40(f32 arg0, f32 arg1, Vec3f* arg2, PlaneF* arg3) {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 x3;
    f32 y3;
    f32 z3;
    f32 x4;
    f32 y4;
    f32 z4;
    f32 temp;
    f32 temp2;
    f32 temp3;
    s32 var_v1 = 0;

    x1 = arg2->x;
    y1 = arg2->y;
    z1 = arg2->z;
    arg2++;
    x2 = arg2->x;
    y2 = arg2->y;
    z2 = arg2->z;
    arg2++;
    x3 = arg2->x;
    y3 = arg2->y;
    z3 = arg2->z;
    arg2++;
    x4 = arg2->x;
    y4 = arg2->y;
    z4 = arg2->z;
    arg2++;

    temp = ((z2 - z1) * (arg0 - x2)) - ((x2 - x1) * (arg1 - z2));
    if (temp >= 0.0f) {
        temp2 = ((z3 - z2) * (arg0 - x3)) - ((x3 - x2) * (arg1 - z3));
        if (temp2 >= 0.0f) {
            temp3 = ((z1 - z3) * (arg0 - x1)) - ((x1 - x3) * (arg1 - z1));
            if (temp3 >= 0.0f) {

                arg3->normal.x = ((y2 - y1) * (z3 - z2)) - ((z2 - z1) * (y3 - y2));
                arg3->normal.y = ((z2 - z1) * (x3 - x2)) - ((x2 - x1) * (z3 - z2));
                arg3->normal.z = ((x2 - x1) * (y3 - y2)) - ((y2 - y1) * (x3 - x2));

                if ((arg3->normal.x != 0.0f) || (arg3->normal.y != 0.0f) || (arg3->normal.z != 0.0f)) {
                    var_v1 = 1;
                }
            }
        }
    }

    if (var_v1 == 0) {
        temp = ((z3 - z1) * (arg0 - x3)) - ((x3 - x1) * (arg1 - z3));
        if (temp >= 0.0f) {
            temp2 = ((z4 - z3) * (arg0 - x4)) - ((x4 - x3) * (arg1 - z4));
            if (temp2 >= 0.0f) {
                temp3 = ((z1 - z4) * (arg0 - x1)) - ((x1 - x4) * (arg1 - z1));
                if (temp3 >= 0.0f) {

                    arg3->normal.x = ((y3 - y1) * (z4 - z3)) - ((z3 - z1) * (y4 - y3));
                    arg3->normal.y = ((z3 - z1) * (x4 - x3)) - ((x3 - x1) * (z4 - z3));
                    arg3->normal.z = ((x3 - x1) * (y4 - y3)) - ((y3 - y1) * (x4 - x3));

                    if ((arg3->normal.x != 0.0f) || (arg3->normal.y != 0.0f) || (arg3->normal.z != 0.0f)) {
                        var_v1 = 2;
                    }
                }
            }
        }
    }

    if (var_v1 != 0) {
        arg3->dist = (-arg3->normal.x * x3) - (arg3->normal.y * y3) - (arg3->normal.z * z3);
    }
    return var_v1;
}

s32 Ground_801B6E20(f32 arg0, f32 arg1, f32* arg2, f32* arg3, f32* arg4) {
    s32 var_s1;
    s32 var_s6;
    s32 var_s7;
    s32 var_v1;
    Vtx(*var_s2)[2];
    Vec3f spA4[4];
    f32 var_fs0;
    f32 var_fs0_2;
    f32 var_fs1;
    f32 var_fs2;
    PlaneF sp84;
    f32 temp;
    f32 temp_fs2;
    s32 pad[4];

    *arg3 = 0.0f;
    *arg4 = 0.0f;
    *arg2 = 0.0f;

    if (D_i5_801C5C14 & 1) {
        temp_fs2 = arg1 - D_i5_801C5C10 - D_i5_801C62D8.z;
        var_v1 = 0;
        var_s6 = (D_i5_801C5C04 + 25) % 27;
        var_fs0 = 0;

        for (var_s7 = 0; var_v1 == 0 && var_s7 < 26; var_s7++) {
            var_s2 = &D_i5_801BE748[var_s6][0];
            if (((var_s2[0][0].v.ob[2] + var_fs0) <= temp_fs2) && (temp_fs2 <= (var_s2[0][1].v.ob[2] + var_fs0))) {
                for (var_s1 = 0; var_v1 == 0 && var_s1 < 15; var_s1++) {
                    var_s2 = &D_i5_801BE748[var_s6][var_s1];

                    spA4[0].x = var_s2[0][0].v.ob[0];
                    spA4[0].y = var_s2[0][0].v.ob[1];
                    spA4[0].z = var_s2[0][0].v.ob[2] + var_fs0;
                    spA4[1].x = var_s2[0][1].v.ob[0];
                    spA4[1].y = var_s2[0][1].v.ob[1];
                    spA4[1].z = var_s2[0][1].v.ob[2] + var_fs0;
                    spA4[2].x = var_s2[1][1].v.ob[0];
                    spA4[2].y = var_s2[1][1].v.ob[1];
                    spA4[2].z = var_s2[1][1].v.ob[2] + var_fs0;
                    spA4[3].x = var_s2[1][0].v.ob[0];
                    spA4[3].y = var_s2[1][0].v.ob[1];
                    spA4[3].z = var_s2[1][0].v.ob[2] + var_fs0;

                    if (((spA4[0].x <= arg0) || (spA4[1].x <= arg0)) && ((arg0 <= spA4[2].x) || (arg0 <= spA4[3].x))) {
                        var_v1 = Ground_801B6B40(arg0, temp_fs2, spA4, &sp84);
                    }
                }
            }
            var_fs0 += var_s2[0][0].v.ob[2];
            var_s6 = (var_s6 + 26) % 27;
        }

        if (var_v1 != 0) {
            temp = ((-sp84.normal.x * arg0) - (sp84.normal.z * temp_fs2) - sp84.dist) / sp84.normal.y;
            if (*arg3 < temp) {
                *arg3 = temp;
            }

            if (sp84.normal.x != 0.0f) {
                var_fs2 = -sp84.dist / sp84.normal.x;
            } else {
                var_fs2 = 0.0f;
            }

            if (sp84.normal.y != 0.0f) {
                var_fs1 = -sp84.dist / sp84.normal.y;
            } else {
                var_fs1 = 0.0f;
            }

            if (sp84.normal.z != 0.0f) {
                var_fs0_2 = -sp84.dist / sp84.normal.z;
            } else {
                var_fs0_2 = 0.0f;
            }

            *arg2 = -Math_Atan2F_XYAlt(var_fs1, var_fs0_2);
            if (var_fs0_2 != 0.0f) {
                *arg4 = -Math_Atan2F_XYAlt(__sinf(Math_Atan2F_XYAlt(var_fs1, var_fs0_2)) * var_fs0_2, var_fs2);
            } else {
                *arg4 = Math_Atan2F_XYAlt(var_fs1, var_fs2);
            }
        } else {
            *arg3 = 0.0f;
            *arg2 = 0.0f;
            *arg4 = 0.0f;
        }
    }
    return 1;
}

void Ground_801B7240(f32 arg0, f32 arg1, f32* arg2, f32* arg3, f32* arg4) {
    s32 pad;
    f32 sp28;
    f32 sp24;

    Ground_801B6E20(arg0, arg1, &sp28, arg3, &sp24);
    *arg2 = sp28 * M_RTOD;
    *arg4 = sp24 * M_RTOD;
}
