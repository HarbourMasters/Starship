#ifndef SF64_MATH_H
#define SF64_MATH_H

#include <libultraship.h>
#include "libc/math.h"
#include <math.h>

#define MTXF_NEW 0
#define MTXF_APPLY 1

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3f; // size = 0xC

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} Vec3s; // size = 0x6;

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f rot;
} PosRot; // size = 0x18

typedef struct {
    /* 0x00 */ Vec3f eye;
    /* 0x0C */ Vec3f at;
} CameraPoint; // size = 0x18

typedef struct {
    /* 0x0 */ s16 vtx[3];
} Triangle; // size = 0x6

typedef struct {
    /* 0x0 */ Vec3f normal;
    /* 0xC */ f32 dist;
} PlaneF; // size = 0x10

typedef struct {
    /* 0x0 */ Vec3s normal;
    /* 0x8 */ s32 dist;
} PlaneI; // size = 0xC

typedef union {
    float m[4][4];
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
    // u64 force_struct_alignment;
} Matrix; // size = 0x40

extern Mtx gIdentityMtx; // 800C4620
extern Matrix gIdentityMatrix; //800C4660

extern Matrix* gGfxMatrix;
extern Matrix sGfxMatrixStack[];
extern Matrix* gCalcMatrix;
extern Matrix sCalcMatrixStack[];

f32 Math_ModF(f32 value, f32 mod);
void Rand_Init(void);
f32 Rand_ZeroOne(void);
void Rand_SetSeed(s32 seed1, s32 seed2, s32 seed3);
f32 Rand_ZeroOneSeeded(void);
f32 Math_Atan2F(f32 y, f32 x);
f32 Math_Atan2F_XY(f32 x, f32 y);
f32 Math_Atan2F_XYAlt(f32 x, f32 y);
f32 Math_PowF(f32 base, s32 exp);
void Math_MinMax(s32* min, s32* max, s32 val1, s32 val2, s32 val3);

f32 Math_SmoothStepToF(f32 *value, f32 target, f32 scale, f32 maxStep, f32 minStep);
f32 Math_SmoothStepToAngle(f32 *angle, f32 target, f32 scale, f32 maxStep, f32 minStep);
void Math_SmoothStepToVec3fArray(Vec3f *src, Vec3f *dst, s32 mode, s32 count, f32 scale, f32 maxStep, f32 minStep);
s32 Math_PursueVec3f(Vec3f *pos, Vec3f *target, Vec3f *rot, f32 stepSize, f32 scaleTurn, f32 maxTurn, f32 dist);
void Math_Vec3fFromAngles(Vec3f *step, f32 xRot, f32 yRot, f32 stepsize);
f32 Math_RadToDeg(f32 rAngle);

// Copies src Matrix into dst
void Matrix_Copy(Matrix* dst, Matrix* src);

// Makes a copy of the stack's current matrix and puts it on the top of the stack
void Matrix_Push(Matrix** mtxStack);

// Removes the top matrix of the stack
void Matrix_Pop(Matrix** mtxStack);

// Copies tf into mtx (MTXF_NEW) or applies it to mtx (MTXF_APPLY)
void Matrix_Mult(Matrix* mtx, Matrix* tf, u8 mode);

// Creates a translation matrix in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_Translate(Matrix* mtx, f32 x, f32 y, f32 z, u8 mode);

// Creates a scale matrix in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_Scale(Matrix* mtx, f32 xScale, f32 yScale, f32 zScale, u8 mode);

// Creates rotation matrix about the X axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateX(Matrix* mtx, f32 angle, u8 mode);

// Creates rotation matrix about the Y axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateY(Matrix* mtx, f32 angle, u8 mode);

// Creates rotation matrix about the Z axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY)
void Matrix_RotateZ(Matrix* mtx, f32 angle, u8 mode);

// Creates rotation matrix about a given vector axis in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY).
// The vector specifying the axis does not need to be a unit vector.
void Matrix_RotateAxis(Matrix* mtx, f32 angle, f32 axisX, f32 axisY, f32 axisZ, u8 mode);

// Converts the current Gfx matrix to a Mtx
void Matrix_ToMtx(Mtx* dest);

// Converts the Mtx src to a Matrix, putting the result in dest
void Matrix_FromMtx(Mtx* src, Matrix* dest);

// Applies the transform matrix mtx to the vector src, putting the result in dest
void Matrix_MultVec3f(Matrix* mtx, Vec3f* src, Vec3f* dest);

// Applies the linear part of the transformation matrix mtx to the vector src, ignoring any translation that mtx might
// have. Puts the result in dest.
void Matrix_MultVec3fNoTranslate(Matrix* mtx, Vec3f* src, Vec3f* dest);

// Expresses the rotational part of the transform mtx as Tait-Bryan angles, in the yaw-pitch-roll (intrinsic YXZ)
// convention used in worldspace calculations
void Matrix_GetYRPAngles(Matrix* mtx, Vec3f* rot);

// Expresses the rotational part of the transform mtx as Tait-Bryan angles, in the extrinsic XYZ convention used in
// modelspace calculations
void Matrix_GetXYZAngles(Matrix* mtx, Vec3f* rot);

// Creates a look-at matrix from Eye, At, and Up in mtx (MTXF_NEW) or applies one to mtx (MTXF_APPLY).
// A look-at matrix is a rotation-translation matrix that maps y to Up, z to (At - Eye), and translates to Eye
void Matrix_LookAt(Matrix* mtx, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp,
                  u8 mode);

// Converts the current Gfx matrix to a Mtx and sets it to the display list
void Matrix_SetGfxMtx(Gfx** gfx);


f32 Math_FAtanF(f32);
f32 Math_FAtan2F(f32, f32);
f32 Math_FAsinF(f32);
f32 Math_FAcosF(f32);

f32 Math_FloorF(f32);
f32 Math_CeilF(f32);
f64 Math_Fabs(f64);
f32 Math_FabsF(f32);
f32 Math_NearbyIntF(f32);
f32 Math_TruncF(f32);
f32 Math_RoundF(f32);

#endif
