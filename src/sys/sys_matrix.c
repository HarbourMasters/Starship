#include "sys.h"

#define qs1616(e) ((s32) ((e) * 0x00010000))

#define IPART(x) ((qs1616(x) >> 16) & 0xFFFF)
#define FPART(x) (qs1616(x) & 0xFFFF)

#define gdSPDefMtx(xx, yx, zx, wx, xy, yy, zy, wy, xz, yz, zz, wz, xw, yw, zw, ww)                                 \
    {                                                                                                              \
        {                                                                                                          \
            (IPART(xx) << 0x10) | IPART(xy), (IPART(xz) << 0x10) | IPART(xw), (IPART(yx) << 0x10) | IPART(yy),     \
                (IPART(yz) << 0x10) | IPART(yw), (IPART(zx) << 0x10) | IPART(zy), (IPART(zz) << 0x10) | IPART(zw), \
                (IPART(wx) << 0x10) | IPART(wy), (IPART(wz) << 0x10) | IPART(ww), (FPART(xx) << 0x10) | FPART(xy), \
                (FPART(xz) << 0x10) | FPART(xw), (FPART(yx) << 0x10) | FPART(yy), (FPART(yz) << 0x10) | FPART(yw), \
                (FPART(zx) << 0x10) | FPART(zy), (FPART(zz) << 0x10) | FPART(zw), (FPART(wx) << 0x10) | FPART(wy), \
                (FPART(wz) << 0x10) | FPART(ww),                                                                   \
        }                                                                                                          \
    }

Mtx gIdentityMtx = gdSPDefMtx(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

Matrix gIdentityMatrix = { {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
} };

Matrix* gGfxMatrix;
Matrix sGfxMatrixStack[0x150];
Matrix* gCalcMatrix;
Matrix sCalcMatrixStack[0x150];

// Copies src Matrix into dst
void Matrix_Copy(Matrix* dst, Matrix* src) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dst->m[i][0] = src->m[i][0];
        dst->m[i][1] = src->m[i][1];
        dst->m[i][2] = src->m[i][2];
        dst->m[i][3] = src->m[i][3];
    }
}

// Makes a copy of the stack's current matrix and puts it on the top of the stack
void Matrix_Push(Matrix** mtxStack) {
    Matrix_Copy(*mtxStack + 1, *mtxStack);
    (*mtxStack)++;
}

// Removes the top matrix of the stack
void Matrix_Pop(Matrix** mtxStack) {
    (*mtxStack)--;
}

// Copies tf into mtx (MTXF_NEW) or applies it to mtx (MTXF_APPLY)
void Matrix_Mult(Matrix* mtx, Matrix* tf, u8 mode) {
    f32 rx;
    f32 ry;
    f32 rz;
    f32 rw;

    //---COL1---
    f32 cx = mfB->xx;
    f32 cy = mfB->xy;
    f32 cz = mfB->xz;
    f32 cw = mfB->xw;
    //--------

    rx = mfA->xx;
    ry = mfA->yx;
    rz = mfA->zx;
    rw = mfA->wx;
    dest->xx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xy;
    ry = mfA->yy;
    rz = mfA->zy;
    rw = mfA->wy;
    dest->xy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xz;
    ry = mfA->yz;
    rz = mfA->zz;
    rw = mfA->wz;
    dest->xz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xw;
    ry = mfA->yw;
    rz = mfA->zw;
    rw = mfA->ww;
    dest->xw = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    //---2Col---
    cx = mfB->yx;
    cy = mfB->yy;
    cz = mfB->yz;
    cw = mfB->yw;
    //--------
    rx = mfA->xx;
    ry = mfA->yx;
    rz = mfA->zx;
    rw = mfA->wx;
    dest->yx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xy;
    ry = mfA->yy;
    rz = mfA->zy;
    rw = mfA->wy;
    dest->yy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xz;
    ry = mfA->yz;
    rz = mfA->zz;
    rw = mfA->wz;
    dest->yz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xw;
    ry = mfA->yw;
    rz = mfA->zw;
    rw = mfA->ww;
    dest->yw = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    //---3Col---
    cx = mfB->zx;
    cy = mfB->zy;
    cz = mfB->zz;
    cw = mfB->zw;
    //--------
    rx = mfA->xx;
    ry = mfA->yx;
    rz = mfA->zx;
    rw = mfA->wx;
    dest->zx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xy;
    ry = mfA->yy;
    rz = mfA->zy;
    rw = mfA->wy;
    dest->zy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xz;
    ry = mfA->yz;
    rz = mfA->zz;
    rw = mfA->wz;
    dest->zz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xw;
    ry = mfA->yw;
    rz = mfA->zw;
    rw = mfA->ww;
    dest->zw = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    //---4Col---
    cx = mfB->wx;
    cy = mfB->wy;
    cz = mfB->wz;
    cw = mfB->ww;
    //--------
    rx = mfA->xx;
    ry = mfA->yx;
    rz = mfA->zx;
    rw = mfA->wx;
    dest->wx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xy;
    ry = mfA->yy;
    rz = mfA->zy;
    rw = mfA->wy;
    dest->wy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xz;
    ry = mfA->yz;
    rz = mfA->zz;
    rw = mfA->wz;
    dest->wz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->xw;
    ry = mfA->yw;
    rz = mfA->zw;
    rw = mfA->ww;
    dest->ww = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);
}

void Matrix_MtxFCopy(MtxF* dest, MtxF* src) {
    dest->xx = src->xx;
    dest->yx = src->yx;
    dest->zx = src->zx;
    dest->wx = src->wx;
    dest->xy = src->xy;
    dest->yy = src->yy;
    dest->zy = src->zy;
    dest->wy = src->wy;
    dest->xx = src->xx;
    dest->yx = src->yx;
    dest->zx = src->zx;
    dest->wx = src->wx;
    dest->xy = src->xy;
    dest->yy = src->yy;
    dest->zy = src->zy;
    dest->wy = src->wy;
    dest->xz = src->xz;
    dest->yz = src->yz;
    dest->zz = src->zz;
    dest->wz = src->wz;
    dest->xw = src->xw;
    dest->yw = src->yw;
    dest->zw = src->zw;
    dest->ww = src->ww;
    dest->xz = src->xz;
    dest->yz = src->yz;
    dest->zz = src->zz;
    dest->wz = src->wz;
    dest->xw = src->xw;
    dest->yw = src->yw;
    dest->zw = src->zw;
    dest->ww = src->ww;
}

// Copies tf into mtx (MTXMODE_NEW) or applies it to mtx (MTXMODE_APPLY)
void Matrix_Mult(Matrix* mtx, Matrix* tf, u8 mode) {
    MtxF* cmf = mtx->m;

    if (mode == 1) {
        MtxFMtxFMult(cmf, tf->m, cmf);
    } else {
        Matrix_MtxFCopy(cmf, tf->m);
    }
}

// Creates a translation matrix in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_Translate(Matrix* mtx, f32 x, f32 y, f32 z, u8 mode) {
    MtxF* cmf = mtx->m;
    f32 tempX;
    f32 tempY;

    if (mode == 1) {
        tempX = cmf->xx;
        tempY = cmf->xy;
        cmf->xw += tempX * x + tempY * y + cmf->xz * z;
        tempX = cmf->yx;
        tempY = cmf->yy;
        cmf->yw += tempX * x + tempY * y + cmf->yz * z;
        tempX = cmf->zx;
        tempY = cmf->zy;
        cmf->zw += tempX * x + tempY * y + cmf->zz * z;
        tempX = cmf->wx;
        tempY = cmf->wy;
        cmf->ww += tempX * x + tempY * y + cmf->wz * z;
    } else {
        cmf->yx = 0.0f;
        cmf->zx = 0.0f;
        cmf->wx = 0.0f;
        cmf->xy = 0.0f;
        cmf->zy = 0.0f;
        cmf->wy = 0.0f;
        cmf->xz = 0.0f;
        cmf->yz = 0.0f;
        cmf->wz = 0.0f;
        cmf->xx = 1.0f;
        cmf->yy = 1.0f;
        cmf->zz = 1.0f;
        cmf->ww = 1.0f;
        cmf->xw = x;
        cmf->yw = y;
        cmf->zw = z;
    }
}

// Creates a scale matrix in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_Scale(Matrix* mtx, f32 xScale, f32 yScale, f32 zScale, u8 mode) {
    f32 rx;
    f32 ry;
    s32 i;

    if (mode == 1) {
        cmf->xx *= x;
        cmf->yx *= x;
        cmf->zx *= x;
        cmf->xy *= y;
        cmf->yy *= y;
        cmf->zy *= y;
        cmf->xz *= z;
        cmf->yz *= z;
        cmf->zz *= z;
        cmf->wx *= x;
        cmf->wy *= y;
        cmf->wz *= z;
    } else {
        cmf->yx = 0.0f;
        cmf->zx = 0.0f;
        cmf->wx = 0.0f;
        cmf->xy = 0.0f;
        cmf->zy = 0.0f;
        cmf->wy = 0.0f;
        cmf->xz = 0.0f;
        cmf->yz = 0.0f;
        cmf->wz = 0.0f;
        cmf->xw = 0.0f;
        cmf->yw = 0.0f;
        cmf->zw = 0.0f;
        cmf->ww = 1.0f;
        cmf->xx = x;
        cmf->yy = y;
        cmf->zz = z;
    }
}

// Creates rotation matrix about the X axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateX(Matrix* mtx, f32 angle, u8 mode) {
    f32 cs;
    f32 sn;
    f32 ry;
    f32 rz;
    s32 i;

    if (mode == 1) {
        if (x != 0) {
            cmf = mtx->m;

            sin = __sinf(x);
            cos = __cosf(x);

            tempY = cmf->xy;
            tempZ = cmf->xz;
            cmf->xy = tempY * cos + tempZ * sin;
            cmf->xz = tempZ * cos - tempY * sin;

            tempY = cmf->yy;
            tempZ = cmf->yz;
            cmf->yy = tempY * cos + tempZ * sin;
            cmf->yz = tempZ * cos - tempY * sin;

            tempY = cmf->zy;
            tempZ = cmf->zz;
            cmf->zy = tempY * cos + tempZ * sin;
            cmf->zz = tempZ * cos - tempY * sin;

            tempY = cmf->wy;
            tempZ = cmf->wz;
            cmf->wy = tempY * cos + tempZ * sin;
            cmf->wz = tempZ * cos - tempY * sin;
        }
    } else {
        cmf = mtx->m;

        if (x != 0) {
            sin = __sinf(x);
            cos = __cosf(x);
        } else {
            sin = zero;
            cos = one;
        }

        cmf->xx = one;
        cmf->yx = zero;
        cmf->zx = zero;
        cmf->wx = zero;
        cmf->xy = zero;
        cmf->yy = cos;
        cmf->zy = sin;
        cmf->wy = zero;
        cmf->xz = zero;
        cmf->yz = -sin;
        cmf->zz = cos;
        cmf->wz = zero;
        cmf->xw = zero;
        cmf->yw = zero;
        cmf->zw = zero;
        cmf->ww = one;
    }
}

// Creates rotation matrix about the Y axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateY(Matrix* mtx, f32 angle, u8 mode) {
    f32 cs;
    f32 sn;
    f32 rx;
    f32 rz;
    s32 i;

    if (mode == 1) {
        if (y != 0.0f) {
            cmf = mtx->m;

            sin = __sinf(y);
            cos = __cosf(y);

            tempX = cmf->xx;
            tempZ = cmf->xz;
            cmf->xx = tempX * cos - tempZ * sin;
            cmf->xz = tempX * sin + tempZ * cos;

            tempX = cmf->yx;
            tempZ = cmf->yz;
            cmf->yx = tempX * cos - tempZ * sin;
            cmf->yz = tempX * sin + tempZ * cos;

            tempX = cmf->zx;
            tempZ = cmf->zz;
            cmf->zx = tempX * cos - tempZ * sin;
            cmf->zz = tempX * sin + tempZ * cos;

            tempX = cmf->wx;
            tempZ = cmf->wz;
            cmf->wx = tempX * cos - tempZ * sin;
            cmf->wz = tempX * sin + tempZ * cos;
        }
    } else {
        cmf = mtx->m;

        if (y != 0.0f) {
            sin = __sinf(y);
            cos = __cosf(y);
        } else {
            cos = one;
            sin = zero;
        }

        cmf->yx = zero;
        cmf->wx = zero;
        cmf->xy = zero;
        cmf->zy = zero;
        cmf->wy = zero;
        cmf->yz = zero;
        cmf->wz = zero;
        cmf->xw = zero;
        cmf->yw = zero;
        cmf->zw = zero;
        cmf->yy = one;
        cmf->ww = one;
        cmf->xx = cos;
        cmf->zz = cos;
        cmf->zx = -sin;
        cmf->xz = sin;
    }
}

// Creates rotation matrix about the Z axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateZ(Matrix* mtx, f32 angle, u8 mode) {
    f32 cs;
    f32 sn;
    f32 rx;
    f32 ry;
    s32 i;

    if (mode == 1) {
        if (z != 0) {
            cmf = mtx->m;

            sin = __sinf(z);
            cos = __cosf(z);

            tempX = cmf->xx;
            tempY = cmf->xy;
            cmf->xx = tempX * cos + tempY * sin;
            cmf->xy = tempY * cos - tempX * sin;

            tempX = cmf->yx;
            tempY = cmf->yy;
            cmf->yx = tempX * cos + tempY * sin;
            cmf->yy = tempY * cos - tempX * sin;

            tempX = cmf->zx;
            tempY = cmf->zy;
            cmf->zx = tempX * cos + tempY * sin;
            cmf->zy = tempY * cos - tempX * sin;

            tempX = cmf->wx;
            tempY = cmf->wy;
            cmf->wx = tempX * cos + tempY * sin;
            cmf->wy = tempY * cos - tempX * sin;
        }
    } else {
        cmf = mtx->m;

        if (z != 0) {
            sin = __sinf(z);
            cos = __cosf(z);
        } else {
            sin = 0.0f;
            cos = 1.0f;
        }

        cmf->zx = 0.0f;
        cmf->wx = 0.0f;
        cmf->zy = 0.0f;
        cmf->wy = 0.0f;
        cmf->xz = 0.0f;
        cmf->yz = 0.0f;
        cmf->wz = 0.0f;
        cmf->xw = 0.0f;
        cmf->yw = 0.0f;
        cmf->zw = 0.0f;
        cmf->zz = 1.0f;
        cmf->ww = 1.0f;
        cmf->xx = cos;
        cmf->yy = cos;
        cmf->yx = sin;
        cmf->xy = -sin;
    }
}

// Creates rotation matrix about a given vector axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY).
// The vector specifying the axis does not need to be a unit vector.
void Matrix_RotateAxis(Matrix* mtx, f32 angle, f32 x, f32 y, f32 z, u8 mode) {
    MtxF* cmf;
    f32 sin;
    f32 cos;
    f32 versin;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    if (mode == 1) {
        if (angle != 0) {
            cmf = mtx->m;

            sin = __sinf(angle);
            cos = __cosf(angle);

            temp1 = cmf->xx;
            temp2 = cmf->xy;
            temp3 = cmf->xz;
            temp4 = (x * temp1 + y * temp2 + z * temp3) * (1.0f - cos);
            cmf->xx = temp1 * cos + x * temp4 + sin * (temp2 * z - temp3 * y);
            cmf->xy = temp2 * cos + y * temp4 + sin * (temp3 * x - temp1 * z);
            cmf->xz = temp3 * cos + z * temp4 + sin * (temp1 * y - temp2 * x);

            temp1 = cmf->yx;
            temp2 = cmf->yy;
            temp3 = cmf->yz;
            temp4 = (x * temp1 + y * temp2 + z * temp3) * (1.0f - cos);
            cmf->yx = temp1 * cos + x * temp4 + sin * (temp2 * z - temp3 * y);
            cmf->yy = temp2 * cos + y * temp4 + sin * (temp3 * x - temp1 * z);
            cmf->yz = temp3 * cos + z * temp4 + sin * (temp1 * y - temp2 * x);

            temp1 = cmf->zx;
            temp2 = cmf->zy;
            temp3 = cmf->zz;
            temp4 = (x * temp1 + y * temp2 + z * temp3) * (1.0f - cos);
            cmf->zx = temp1 * cos + x * temp4 + sin * (temp2 * z - temp3 * y);
            cmf->zy = temp2 * cos + y * temp4 + sin * (temp3 * x - temp1 * z);
            cmf->zz = temp3 * cos + z * temp4 + sin * (temp1 * y - temp2 * x);
        }
    } else {
        cmf = mtx->m;

        if (angle != 0) {
            sin = __sinf(angle);
            cos = __cosf(angle);
            versin = 1.0f - cos;

            cmf->xx = x * x * versin + cos;
            cmf->yy = y * y * versin + cos;
            cmf->zz = z * z * versin + cos;

            if (0) {}

            temp2 = x * versin * y;
            temp3 = z * sin;
            cmf->yx = temp2 + temp3;
            cmf->xy = temp2 - temp3;

            temp2 = x * versin * z;
            temp3 = y * sin;
            cmf->zx = temp2 - temp3;
            cmf->xz = temp2 + temp3;

            temp2 = y * versin * z;
            temp3 = x * sin;
            cmf->zy = temp2 + temp3;
            cmf->yz = temp2 - temp3;

            cmf->wx = cmf->wy = cmf->wz = cmf->xw = cmf->yw = cmf->zw = 0.0f;
            cmf->ww = 1.0f;
        } else {
            cmf->xx = 1.0f;
            cmf->yx = 0.0f;
            cmf->zx = 0.0f;
            cmf->wx = 0.0f;
            cmf->xy = 0.0f;
            cmf->yy = 1.0f;
            cmf->zy = 0.0f;
            cmf->wy = 0.0f;
            cmf->xz = 0.0f;
            cmf->yz = 0.0f;
            cmf->zz = 1.0f;
            cmf->wz = 0.0f;
            cmf->xw = 0.0f;
            cmf->yw = 0.0f;
            cmf->zw = 0.0f;
            cmf->ww = 1.0f;
        }
    }
}

// Converts the current Gfx matrix to a Mtx
void Matrix_ToMtx(Mtx* dest) {
    // LTODO: We need to validate this
    guMtxF2L(gGfxMatrix->m, dest);
}

// Converts the Mtx src to a Matrix, putting the result in dest
void Matrix_FromMtx(Mtx* src, Matrix* dest) {
    guMtxF2L(src->m, dest->m);
}

// Applies the transform matrix mtx to the vector src, putting the result in dest
void Matrix_MultVec3f(Matrix* mtx, Vec3f* src, Vec3f* dest) {
    dest->x = (mtx->m[0][0] * src->x) + (mtx->m[1][0] * src->y) + (mtx->m[2][0] * src->z) + mtx->m[3][0];
    dest->y = (mtx->m[0][1] * src->x) + (mtx->m[1][1] * src->y) + (mtx->m[2][1] * src->z) + mtx->m[3][1];
    dest->z = (mtx->m[0][2] * src->x) + (mtx->m[1][2] * src->y) + (mtx->m[2][2] * src->z) + mtx->m[3][2];
}

// Applies the linear part of the transformation matrix mtx to the vector src, ignoring any translation that mtx might
// have. Puts the result in dest.
void Matrix_MultVec3fNoTranslate(Matrix* mtx, Vec3f* src, Vec3f* dest) {
    dest->x = (mtx->m[0][0] * src->x) + (mtx->m[1][0] * src->y) + (mtx->m[2][0] * src->z);
    dest->y = (mtx->m[0][1] * src->x) + (mtx->m[1][1] * src->y) + (mtx->m[2][1] * src->z);
    dest->z = (mtx->m[0][2] * src->x) + (mtx->m[1][2] * src->y) + (mtx->m[2][2] * src->z);
}

// Expresses the rotational part of the transform mtx as Tait-Bryan angles, in the yaw-pitch-roll (intrinsic YXZ)
// convention used in worldspace calculations
void Matrix_GetYRPAngles(Matrix* mtx, Vec3f* rot) {
    Matrix invYP;
    Vec3f origin = { 0.0f, 0.0f, 0.0f };
    Vec3f originP;
    Vec3f zHat = { 0.0f, 0.0f, 1.0f };
    Vec3f zHatP;
    Vec3f xHat = { 1.0f, 0.0f, 0.0f };
    Vec3f xHatP;

    Matrix_MultVec3fNoTranslate(mtx, &origin, &originP);
    Matrix_MultVec3fNoTranslate(mtx, &zHat, &zHatP);
    Matrix_MultVec3fNoTranslate(mtx, &xHat, &xHatP);
    zHatP.x -= originP.x;
    zHatP.y -= originP.y;
    zHatP.z -= originP.z;
    xHatP.x -= originP.x;
    xHatP.y -= originP.y;
    xHatP.z -= originP.z;
    rot->y = Math_Atan2F(zHatP.x, zHatP.z);
    rot->x = -Math_Atan2F(zHatP.y, sqrtf(SQ(zHatP.x) + SQ(zHatP.z)));
    Matrix_RotateX(&invYP, -rot->x, MTXF_NEW);
    Matrix_RotateY(&invYP, -rot->y, MTXF_APPLY);
    Matrix_MultVec3fNoTranslate(&invYP, &xHatP, &xHat);
    rot->x *= M_RTOD;
    rot->y *= M_RTOD;
    rot->z = Math_Atan2F(xHat.y, xHat.x) * M_RTOD;
}

// Expresses the rotational part of the transform mtx as Tait-Bryan angles, in the extrinsic XYZ convention used in
// modelspace calculations
void Matrix_GetXYZAngles(Matrix* mtx, Vec3f* rot) {
    Matrix invYZ;
    Vec3f origin = { 0.0f, 0.0f, 0.0f };
    Vec3f originP;
    Vec3f xHat = { 1.0f, 0.0f, 0.0f };
    Vec3f xHatP;
    Vec3f yHat = { 0.0f, 1.0f, 0.0f };
    Vec3f yHatP;

    Matrix_MultVec3fNoTranslate(mtx, &origin, &originP);
    Matrix_MultVec3fNoTranslate(mtx, &xHat, &xHatP);
    Matrix_MultVec3fNoTranslate(mtx, &yHat, &yHatP);
    xHatP.x -= originP.x;
    xHatP.y -= originP.y;
    xHatP.z -= originP.z;
    yHatP.x -= originP.x;
    yHatP.y -= originP.y;
    yHatP.z -= originP.z;
    rot->z = Math_Atan2F(xHatP.y, xHatP.x);
    rot->y = -Math_Atan2F(xHatP.z, sqrtf(SQ(xHatP.x) + SQ(xHatP.y)));
    Matrix_RotateY(&invYZ, -rot->y, MTXF_NEW);
    Matrix_RotateZ(&invYZ, -rot->z, MTXF_APPLY);
    Matrix_MultVec3fNoTranslate(&invYZ, &yHatP, &yHat);
    rot->x = Math_Atan2F(yHat.z, yHat.y) * M_RTOD;
    rot->y *= M_RTOD;
    rot->z *= M_RTOD;
}

// Creates a look-at matrix from Eye, At, and Up in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY).
// A look-at matrix is a rotation-translation matrix that maps y to Up, z to (At - Eye), and translates to Eye
void Matrix_LookAt(Matrix* mtx, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp,
                   u8 mode) {
    Matrix lookAt;

    guLookAtF(lookAt.m, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
    Matrix_Mult(mtx, &lookAt, mode);
}

// Converts the current Gfx matrix to a Mtx and sets it to the display list
void Matrix_SetGfxMtx(Gfx** gfx) {
    Matrix_ToMtx(gGfxMtx);
    gSPMatrix((*gfx)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}
