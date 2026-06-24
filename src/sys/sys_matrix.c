#include "sys.h"

#include "port/interpolation/FrameInterpolation.h"
#define qs1616(e) ((s32) ((e) *0x00010000))

#define IPART(x) ((qs1616(x) >> 16) & 0xFFFF)
#define FPART(x) (qs1616(x) & 0xFFFF)

#define gdSPDefMtxF(xx, yx, zx, wx, xy, yy, zy, wy, xz, yz, zz, wz, xw, yw, zw, ww) \
    {                                                                               \
        { xx, yx, zx, wx, xy, yy, zy, wy, xz, yz, zz, wz, xw, yw, zw, ww, }         \
    }

Mtx gIdentityMtx =
    gdSPDefMtxF(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

Matrix gIdentityMatrix = { {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
} };

Matrix* gGfxMatrix;
Matrix sGfxMatrixStack[0x1000];
Matrix* gCalcMatrix;
Matrix sCalcMatrixStack[0x1000];
Matrix sInterpolationMatrixStack[0x1000];
Matrix* gInterpolationMatrix = &sInterpolationMatrixStack[0];

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
    FrameInterpolation_RecordMatrixPush(mtxStack);

    if (mtxStack == NULL || *mtxStack == NULL) {
        int bp = 0;
    }

    Matrix_Copy(*mtxStack + 1, *mtxStack);
    (*mtxStack)++;
}

// Removes the top matrix of the stack
void Matrix_Pop(Matrix** mtxStack) {
    FrameInterpolation_RecordMatrixPop(mtxStack);
    (*mtxStack)--;
}

/**
 * Matrix multiplication, dest = mfA * mfB.
 * mfA and dest should not be the same matrix.
 */
void Matrix_MtxFMtxFMult(MtxF* mfB, MtxF* mfA, MtxF* dest) {
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

// Copies tf into mtx (MTXF_NEW) or applies it to mtx (MTXF_APPLY)
void Matrix_Mult(Matrix* mtx, Matrix* tf, u8 mode) {
    FrameInterpolation_RecordMatrixMult(mtx, tf, mode);
    f32 rx;
    f32 ry;
    f32 rz;
    f32 rw;
    s32 i0;
    s32 i1;
    s32 i2;
    s32 i3;

    if (mode == 1) {
        rx = mtx->m[0][0];
        ry = mtx->m[1][0];
        rz = mtx->m[2][0];
        rw = mtx->m[3][0];

        for (i0 = 0; i0 < 4; i0++) {
            mtx->m[i0][0] = (rx * tf->m[i0][0]) + (ry * tf->m[i0][1]) + (rz * tf->m[i0][2]) + (rw * tf->m[i0][3]);
        }

        rx = mtx->m[0][1];
        ry = mtx->m[1][1];
        rz = mtx->m[2][1];
        rw = mtx->m[3][1];

        for (i1 = 0; i1 < 4; i1++) {
            mtx->m[i1][1] = (rx * tf->m[i1][0]) + (ry * tf->m[i1][1]) + (rz * tf->m[i1][2]) + (rw * tf->m[i1][3]);
        }

        rx = mtx->m[0][2];
        ry = mtx->m[1][2];
        rz = mtx->m[2][2];
        rw = mtx->m[3][2];

        for (i2 = 0; i2 < 4; i2++) {
            mtx->m[i2][2] = (rx * tf->m[i2][0]) + (ry * tf->m[i2][1]) + (rz * tf->m[i2][2]) + (rw * tf->m[i2][3]);
        }

        rx = mtx->m[0][3];
        ry = mtx->m[1][3];
        rz = mtx->m[2][3];
        rw = mtx->m[3][3];

        for (i3 = 0; i3 < 4; i3++) {
            mtx->m[i3][3] = (rx * tf->m[i3][0]) + (ry * tf->m[i3][1]) + (rz * tf->m[i3][2]) + (rw * tf->m[i3][3]);
        }
    } else {
        Matrix_Copy(mtx, tf);
    }
}

// Creates a translation matrix in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_Translate(Matrix* mtx, f32 x, f32 y, f32 z, u8 mode) {
    FrameInterpolation_RecordMatrixTranslate(mtx, x, y, z, mode);
    f32 rx;
    f32 ry;
    s32 i;

    if (mode == 1) {
        for (i = 0; i < 4; i++) {
            rx = mtx->m[0][i];
            ry = mtx->m[1][i];

            mtx->m[3][i] += (rx * x) + (ry * y) + (mtx->m[2][i] * z);
        }
    } else {
        mtx->m[3][0] = x;
        mtx->m[3][1] = y;
        mtx->m[3][2] = z;
        mtx->m[0][1] = mtx->m[0][2] = mtx->m[0][3] = mtx->m[1][0] = mtx->m[1][2] = mtx->m[1][3] = mtx->m[2][0] =
            mtx->m[2][1] = mtx->m[2][3] = 0.0f;
        mtx->m[0][0] = mtx->m[1][1] = mtx->m[2][2] = mtx->m[3][3] = 1.0f;
    }
}

// Creates a scale matrix in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_Scale(Matrix* mtx, f32 xScale, f32 yScale, f32 zScale, u8 mode) {
    FrameInterpolation_RecordMatrixScale(mtx, xScale, yScale, zScale, mode);
    f32 rx;
    f32 ry;
    s32 i;

    if (mode == 1) {
        for (i = 0; i < 4; i++) {
            rx = mtx->m[0][i];
            ry = mtx->m[1][i];

            mtx->m[0][i] = rx * xScale;
            mtx->m[1][i] = ry * yScale;
            mtx->m[2][i] *= zScale;
        }
    } else {
        mtx->m[0][0] = xScale;
        mtx->m[1][1] = yScale;
        mtx->m[2][2] = zScale;
        mtx->m[0][1] = mtx->m[0][2] = mtx->m[0][3] = mtx->m[1][0] = mtx->m[1][2] = mtx->m[1][3] = mtx->m[2][0] =
            mtx->m[2][1] = mtx->m[2][3] = mtx->m[3][0] = mtx->m[3][1] = mtx->m[3][2] = 0.0f;
        mtx->m[3][3] = 1.0f;
    }
}

// Creates rotation matrix about the X axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateX(Matrix* mtx, f32 angle, u8 mode) {
    FrameInterpolation_RecordMatrixRotate1Coord(mtx, 0, angle, mode);
    f32 cs;
    f32 sn;
    f32 ry;
    f32 rz;
    s32 i;

    sn = __sinf(angle);
    cs = __cosf(angle);
    if (mode == 1) {
        for (i = 0; i < 4; i++) {
            ry = mtx->m[1][i];
            rz = mtx->m[2][i];

            mtx->m[1][i] = (ry * cs) + (rz * sn);
            mtx->m[2][i] = (rz * cs) - (ry * sn);
        }
    } else {
        mtx->m[1][1] = mtx->m[2][2] = cs;
        mtx->m[1][2] = sn;
        mtx->m[2][1] = -sn;
        mtx->m[0][0] = mtx->m[3][3] = 1.0f;
        mtx->m[0][1] = mtx->m[0][2] = mtx->m[0][3] = mtx->m[1][0] = mtx->m[1][3] = mtx->m[2][0] = mtx->m[2][3] =
            mtx->m[3][0] = mtx->m[3][1] = mtx->m[3][2] = 0.0f;
    }
}

// Creates rotation matrix about the Y axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateY(Matrix* mtx, f32 angle, u8 mode) {
    FrameInterpolation_RecordMatrixRotate1Coord(mtx, 1, angle, mode);
    f32 cs;
    f32 sn;
    f32 rx;
    f32 rz;
    s32 i;

    sn = __sinf(angle);
    cs = __cosf(angle);
    if (mode == 1) {
        for (i = 0; i < 4; i++) {
            rx = mtx->m[0][i];
            rz = mtx->m[2][i];

            mtx->m[0][i] = (rx * cs) - (rz * sn);
            mtx->m[2][i] = (rx * sn) + (rz * cs);
        }
    } else {
        mtx->m[0][0] = mtx->m[2][2] = cs;
        mtx->m[0][2] = -sn;
        mtx->m[2][0] = sn;
        mtx->m[1][1] = mtx->m[3][3] = 1.0f;
        mtx->m[0][1] = mtx->m[0][3] = mtx->m[1][0] = mtx->m[1][2] = mtx->m[1][3] = mtx->m[2][1] = mtx->m[2][3] =
            mtx->m[3][0] = mtx->m[3][1] = mtx->m[3][2] = 0.0f;
    }
}

// Creates rotation matrix about the Z axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateZ(Matrix* mtx, f32 angle, u8 mode) {
    FrameInterpolation_RecordMatrixRotate1Coord(mtx, 2, angle, mode);
    f32 cs;
    f32 sn;
    f32 rx;
    f32 ry;
    s32 i;

    sn = __sinf(angle);
    cs = __cosf(angle);
    if (mode == 1) {
        for (i = 0; i < 4; i++) {
            rx = mtx->m[0][i];
            ry = mtx->m[1][i];

            mtx->m[0][i] = (rx * cs) + (ry * sn);
            mtx->m[1][i] = (ry * cs) - (rx * sn);
        }
    } else {
        mtx->m[0][0] = mtx->m[1][1] = cs;
        mtx->m[0][1] = sn;
        mtx->m[1][0] = -sn;
        mtx->m[2][2] = mtx->m[3][3] = 1.0f;
        mtx->m[0][2] = mtx->m[0][3] = mtx->m[1][2] = mtx->m[1][3] = mtx->m[2][0] = mtx->m[2][1] = mtx->m[2][3] =
            mtx->m[3][0] = mtx->m[3][1] = mtx->m[3][2] = 0.0f;
    }
}

// Creates rotation matrix about a given vector axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY).
// The vector specifying the axis does not need to be a unit vector.
void Matrix_RotateAxis(Matrix* mtx, f32 angle, f32 axisX, f32 axisY, f32 axisZ, u8 mode) {
    //    FrameInterpolation_RecordMatrixRotateAxis()
    f32 rx;
    f32 ry;
    f32 rz;
    f32 norm;
    f32 cxx;
    f32 cyx;
    f32 czx;
    f32 cxy;
    f32 cyy;
    f32 czy;
    f32 cxz;
    f32 cyz;
    f32 czz;
    f32 xx;
    f32 yy;
    f32 zz;
    f32 xy;
    f32 yz;
    f32 xz;
    f32 sinA;
    f32 cosA;

    norm = sqrtf((axisX * axisX) + (axisY * axisY) + (axisZ * axisZ));
    if (norm != 0.0) {
        axisX /= norm;
        axisY /= norm;
        axisZ /= norm;
        sinA = __sinf(angle);
        cosA = __cosf(angle);
        xx = axisX * axisX;
        yy = axisY * axisY;
        zz = axisZ * axisZ;
        xy = axisX * axisY;
        yz = axisY * axisZ;
        xz = axisX * axisZ;

        if (mode == 1) {
            cxx = (1.0f - xx) * cosA + xx;
            cyx = (1.0f - cosA) * xy + axisZ * sinA;
            czx = (1.0f - cosA) * xz - axisY * sinA;

            cxy = (1.0f - cosA) * xy - axisZ * sinA;
            cyy = (1.0f - yy) * cosA + yy;
            czy = (1.0f - cosA) * yz + axisX * sinA;

            cxz = (1.0f - cosA) * xz + axisY * sinA;
            cyz = (1.0f - cosA) * yz - axisX * sinA;
            czz = (1.0f - zz) * cosA + zz;

            // loop doesn't seem to work here.
            rx = mtx->m[0][0];
            ry = mtx->m[0][1];
            rz = mtx->m[0][2];
            mtx->m[0][0] = (rx * cxx) + (ry * cxy) + (rz * cxz);
            mtx->m[0][1] = (rx * cyx) + (ry * cyy) + (rz * cyz);
            mtx->m[0][2] = (rx * czx) + (ry * czy) + (rz * czz);

            rx = mtx->m[1][0];
            ry = mtx->m[1][1];
            rz = mtx->m[1][2];
            mtx->m[1][0] = (rx * cxx) + (ry * cxy) + (rz * cxz);
            mtx->m[1][1] = (rx * cyx) + (ry * cyy) + (rz * cyz);
            mtx->m[1][2] = (rx * czx) + (ry * czy) + (rz * czz);

            rx = mtx->m[2][0];
            ry = mtx->m[2][1];
            rz = mtx->m[2][2];
            mtx->m[2][0] = (rx * cxx) + (ry * cxy) + (rz * cxz);
            mtx->m[2][1] = (rx * cyx) + (ry * cyy) + (rz * cyz);
            mtx->m[2][2] = (rx * czx) + (ry * czy) + (rz * czz);
        } else {
            mtx->m[0][0] = (1.0f - xx) * cosA + xx;
            mtx->m[0][1] = (1.0f - cosA) * xy + axisZ * sinA;
            mtx->m[0][2] = (1.0f - cosA) * xz - axisY * sinA;
            mtx->m[0][3] = 0.0f;

            mtx->m[1][0] = (1.0f - cosA) * xy - axisZ * sinA;
            mtx->m[1][1] = (1.0f - yy) * cosA + yy;
            mtx->m[1][2] = (1.0f - cosA) * yz + axisX * sinA;
            mtx->m[1][3] = 0.0f;

            mtx->m[2][0] = (1.0f - cosA) * xz + axisY * sinA;
            mtx->m[2][1] = (1.0f - cosA) * yz - axisX * sinA;
            mtx->m[2][2] = (1.0f - zz) * cosA + zz;
            mtx->m[2][3] = 0.0f;

            mtx->m[3][0] = mtx->m[3][1] = mtx->m[3][2] = 0.0f;
            mtx->m[3][3] = 1.0f;
        }
    }
}

// Converts the current Gfx matrix to a Mtx
void Matrix_ToMtx(Mtx* dest) {
    FrameInterpolation_RecordMatrixMtxFToMtx(gGfxMatrix->m, dest);
    // LTODO: We need to validate this
    guMtxF2L(gGfxMatrix->m, dest);
}

// Converts the Mtx src to a Matrix, putting the result in dest
void Matrix_FromMtx(Mtx* src, Matrix* dest) {
    FrameInterpolation_RecordMatrixMtxFToMtx(src, dest);
    guMtxF2L(src->mf, dest->m);
}

// Applies the transform matrix mtx to the vector src, putting the result in dest
void Matrix_MultVec3f(Matrix* mtx, Vec3f* src, Vec3f* dest) {
    FrameInterpolation_RecordMatrixMultVec3f(mtx, *src, *dest);
    dest->x = (mtx->m[0][0] * src->x) + (mtx->m[1][0] * src->y) + (mtx->m[2][0] * src->z) + mtx->m[3][0];
    dest->y = (mtx->m[0][1] * src->x) + (mtx->m[1][1] * src->y) + (mtx->m[2][1] * src->z) + mtx->m[3][1];
    dest->z = (mtx->m[0][2] * src->x) + (mtx->m[1][2] * src->y) + (mtx->m[2][2] * src->z) + mtx->m[3][2];
}

// Applies the linear part of the transformation matrix mtx to the vector src, ignoring any translation that mtx might
// have. Puts the result in dest.
void Matrix_MultVec3fNoTranslate(Matrix* mtx, Vec3f* src, Vec3f* dest) {
    FrameInterpolation_RecordMatrixMultVec3fNoTranslate(mtx, *src, *dest);
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
