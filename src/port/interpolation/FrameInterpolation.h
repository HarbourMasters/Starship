#pragma once

#include "sf64math.h"
#include <libultraship.h>

#ifdef __cplusplus

#include <unordered_map>

std::unordered_map<Mtx*, MtxF> FrameInterpolation_Interpolate(float step);

extern "C" {

#endif

void FrameInterpolation_ShouldInterpolateFrame(bool shouldInterpolate);

void FrameInterpolation_StartRecord(void);

void FrameInterpolation_StopRecord(void);

void FrameInterpolation_RecordMarker(const char* file, int line);

void FrameInterpolation_RecordOpenChild(const void* a, int b);

void FrameInterpolation_RecordCloseChild(void);

void FrameInterpolation_DontInterpolateCamera(void);

int FrameInterpolation_GetCameraEpoch(void);

void FrameInterpolation_RecordActorPosRotMatrix(void);

void FrameInterpolation_RecordMatrixPush(Matrix** mtx);

void FrameInterpolation_RecordMatrixPop(Matrix** mtx);

void FrameInterpolation_RecordMatrixMult(Matrix* matrix, MtxF* mf, u8 mode);

void FrameInterpolation_RecordMatrixTranslate(Matrix* matrix, f32 x, f32 y, f32 z, u8 mode);

void FrameInterpolation_RecordMatrixScale(Matrix* matrix, f32 x, f32 y, f32 z, u8 mode);

void FrameInterpolation_RecordMatrixRotate1Coord(Matrix* matrix, u32 coord, f32 value, u8 mode);

void FrameInterpolation_RecordMatrixMtxFToMtx(MtxF* src, Mtx* dest);

void FrameInterpolation_RecordMatrixReplaceRotation(MtxF* mf);

void FrameInterpolation_RecordMatrixRotateAxis(f32 angle, Vec3f* axis, u8 mode);

void FrameInterpolation_RecordSkinMatrixMtxFToMtx(MtxF* src, Mtx* dest);

void FrameInterpolation_RecordMatrixMultVec3f(Matrix* matrix, Vec3f src, Vec3f dest);

void FrameInterpolation_RecordMatrixMultVec3fNoTranslate(Matrix* matrix, Vec3f src, Vec3f dest);

#ifdef __cplusplus
}
#endif