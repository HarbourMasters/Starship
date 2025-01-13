#include "global.h"
#include "assets/ast_text.h"

char D_801619A0[100];

char* Graphics_ClearPrintBuffer(char* buf, s32 fill, s32 len) {
    s32 i;
    char* ptr = buf;

    for (i = len; i > 0; i--) {
        *ptr++ = fill;
    }

    return buf;
}

s32 Graphics_Printf(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    Graphics_ClearPrintBuffer(D_801619A0, 0, 100);
    Lib_vsPrintf(D_801619A0, fmt, args);
    va_end(args);

    return 0;
}

void Lib_Texture_Scroll(u16* texture, s32 width, s32 height, u8 mode) {
    // LTodo: [HD-Textures] This is broken
    u16* pixel = SEGMENTED_TO_VIRTUAL(texture);
    u16 tempPxl;
    s32 u;
    s32 v;

    switch (mode) {
        case 0:
            for (u = 0; u < width; u++) {
                tempPxl = pixel[u];
                for (v = 1; v < height; v++) {
                    pixel[(v - 1) * width + u] = pixel[(v) *width + u];
                }
                pixel[(height - 1) * width + u] = tempPxl;
            }
            break;
        case 1:
            for (u = 0; u < width; u++) {
                tempPxl = pixel[(height - 1) * width + u];
                for (v = height - 2; v >= 0; v--) {
                    pixel[(v + 1) * width + u] = pixel[(v) *width + u];
                }
                pixel[u] = tempPxl;
            }
            break;
        case 2:
            for (v = 0; v < height; v++) {
                tempPxl = pixel[v * width + width - 1];
                for (u = width - 2; u >= 0; u--) {
                    pixel[v * width + u + 1] = pixel[v * width + u];
                }
                pixel[v * width] = tempPxl;
            }
            break;
        case 3:
            for (v = 0; v < height; v++) {
                tempPxl = pixel[v * width];
                for (u = 1; u < width; u++) {
                    pixel[v * width + u - 1] = pixel[v * width + u];
                }
                pixel[v * width + width - 1] = tempPxl;
            }
            break;
    }

    // LTodo: we should only invalidate one texture
    gSPInvalidateTexCache(gMasterDisp++, NULL);
}

void Lib_Texture_Mottle(u16* dst, u16* src, u8 mode) {
    // LTodo: [HD-Textures] This is broken
    s32 u;
    s32 v;
    u8* dst8;
    u8* src8;
    s32 offset;

    dst = LOAD_ASSET(dst);
    src = LOAD_ASSET(src);

    switch (mode) {
        case 2:
            for (v = 0; v < 32 * 32; v += 32) {
                offset = 3.0f * __sinf((s32) (((v / 32) + (gGameFrameCount / 4)) % 32U) * (2 * M_PI / 32));
                for (u = 0; u < 32; u++) {
                    dst[v + (offset + u) % 32U] = src[v + u];
                }
            }
            break;

        case 3:
            for (v = 0; v < 32 * 64; v += 64) { // should be 32 * 64?
                offset = __sinf((s32) (((v / 64) + (gGameFrameCount / 4)) % 32U) * (2 * M_PI / 8));
                for (u = 0; u < 64; u++) {
                    dst[v + (offset + u) % 64U] = src[v + u];
                }
            }
            break;

        case 1:
            for (v = 0; v < 16 * 16; v += 16) {
                offset = 2.0f * __sinf((s32) (((v / 16) + (gGameFrameCount / 2)) % 16U) * (2 * M_PI / 16));
                for (u = 0; u < 16; u++) {
                    dst[v + (offset + u) % 16U] = src[v + u];
                }
            }
            break;

        case 0:
            for (v = 0; v < 32 * 32; v += 32) {
                offset = 2.0f * __sinf((s32) (((v / 32) + (gGameFrameCount / 2)) % 32U) * (2 * M_PI / 32));
                for (u = 0; u < 32; u++) {
                    dst[v + (offset + u) % 32U] = src[v + u];
                }
            }
            break;

        case 5:
            dst8 = (u8*) dst;
            src8 = (u8*) src;
            for (v = 0; v < 64 * 64; v += 64) {
                offset = 4.0f * __sinf((s32) (((v / 64) + (gGameFrameCount / 4)) % 32U) * (2 * M_PI / 32));
                for (u = 0; u < 64; u++) {
                    dst8[v + (offset + u) % 64U] = src8[v + u];
                }
            }
            break;
    }

    // LTodo: we should only invalidate one texture
    gSPInvalidateTexCache(gMasterDisp++, NULL);
}

s32 Animation_GetLimbIndex(Limb* limb, Limb** skeleton) {
    s32 i = 1;

    for (i = 1; *skeleton != NULL; i++, skeleton++) {
        if (*skeleton == limb) {
            return i;
        }
    }
    return 0;
}

#define TAG_LIMB_ADDRESS(ptr, data) ((((u32) (ptr) << 16) & 0xFFFF0000) | ((u32) (data) & 0x0000FFFF))
#define TAG_LIMB(limb, data) ((u32) (0x80000000 | (TAG_LIMB_ADDRESS(limb, data))))

void Animation_DrawLimb(s32 mode, Limb* limb, Limb** skeleton, Vec3f* jointTable, OverrideLimbDraw overrideLimbDraw,
                        PostLimbDraw postLimbDraw, void* data) {
    bool override;
    s32 limbIndex;
    Gfx* dList;
    Vec3f trans;
    Vec3f rot;
    Vec3f pos;
    Vec3f origin = { 0.0f, 0.0f, 0.0f };

    Matrix_Push(&gCalcMatrix);

    skeleton = LOAD_ASSET(skeleton);
    limbIndex = Animation_GetLimbIndex(limb, skeleton);
    limb = SEGMENTED_TO_VIRTUAL(limb);
    rot = jointTable[limbIndex];
    trans.x = limb->trans.x;
    trans.y = limb->trans.y;
    trans.z = limb->trans.z;
    dList = limb->dList;
    Matrix_Push(&gGfxMatrix);

    // @port Tag the transform.
    FrameInterpolation_RecordOpenChild(TAG_LIMB(limb, data), limbIndex);

    if (overrideLimbDraw == NULL) {
        override = false;
    } else {
        override = overrideLimbDraw(limbIndex - 1, &dList, &trans, &rot, data);
    }
    if (!override) {
        Matrix_Translate(gCalcMatrix, trans.x, trans.y, trans.z, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot.x * M_DTOR, MTXF_APPLY);
        if (dList != NULL) {
            if (mode >= 2) {
                Matrix_MultVec3f(gCalcMatrix, &origin, &pos);
                if (mode != 5) {
                    Display_SetSecondLight(&pos);
                }
            }
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, dList);
        }
    }

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    if (postLimbDraw != NULL) {
        postLimbDraw(limbIndex - 1, &rot, data);
    }
    Matrix_Pop(&gGfxMatrix);
    if (limb->child != NULL) {
        Animation_DrawLimb(mode, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, data);
    }
    Matrix_Pop(&gCalcMatrix);
    if (limb->sibling != NULL) {
        Animation_DrawLimb(mode, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw, data);
    }
}

void Animation_DrawSkeleton(s32 mode, Limb** skeletonSegment, Vec3f* jointTable, OverrideLimbDraw overrideLimbDraw,
                            PostLimbDraw postLimbDraw, void* data, Matrix* transform) {
    bool override;
    Limb** skeleton;
    Limb* rootLimb;
    s32 rootIndex;
    Gfx* dList;
    Vec3f baseTrans;
    Vec3f baseRot;

    Matrix_Push(&gCalcMatrix);
    Matrix_Copy(gCalcMatrix, transform);

    skeleton = SEGMENTED_TO_VIRTUAL(skeletonSegment);
    rootLimb = SEGMENTED_TO_VIRTUAL(skeleton[0]);
    rootIndex = Animation_GetLimbIndex(skeleton[0], skeleton);
    baseRot = jointTable[rootIndex];

    if (mode & 1) {
        baseTrans.x = rootLimb->trans.x;
        baseTrans.y = rootLimb->trans.y;
        baseTrans.z = rootLimb->trans.z;
    } else {
        baseTrans.x = jointTable[0].x;
        baseTrans.y = jointTable[0].y;
        baseTrans.z = jointTable[0].z;
    }

    dList = rootLimb->dList;
    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild(TAG_LIMB(rootLimb, data), rootIndex);

    if (overrideLimbDraw == NULL) {
        override = false;
    } else {
        override = overrideLimbDraw(rootIndex - 1, &dList, &baseTrans, &baseRot, data);
    }
    if (!override) {
        Matrix_Translate(gCalcMatrix, baseTrans.x, baseTrans.y, baseTrans.z, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, baseRot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, baseRot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, baseRot.x * M_DTOR, MTXF_APPLY);
        if (dList != NULL) {
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, dList);
        }
    }
    if (postLimbDraw != NULL) {
        postLimbDraw(rootIndex - 1, &baseRot, data);
    }

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    Matrix_Pop(&gGfxMatrix);

    if (rootLimb->child != NULL) {
        Animation_DrawLimb(mode, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, data);
    }
    Matrix_Pop(&gCalcMatrix);

    if (mode >= 2) {
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
    }
}

s16 Animation_GetFrameData(Animation* animationSegmemt, s32 frame, Vec3f* frameTable) {
    Animation* animation = SEGMENTED_TO_VIRTUAL(animationSegmemt);
    u16 limbCount = animation->limbCount;
    JointKey* key = SEGMENTED_TO_VIRTUAL(animation->jointKey);
    u16* frameData = SEGMENTED_TO_VIRTUAL(animation->frameData);
    s32 i;
    s32 temp;

    temp = (frame < key->xLen) ? frameData[key->x + frame] : frameData[key->x];
    frameTable->x = (s16) temp;
    temp = (frame < key->yLen) ? frameData[key->y + frame] : frameData[key->y];
    frameTable->y = (s16) temp;
    temp = (frame < key->zLen) ? frameData[key->z + frame] : frameData[key->z];
    frameTable->z = (s16) temp;

    frameTable++, key++;
    for (i = 1; i <= limbCount; i++, key++, frameTable++) {
        temp = (frame < key->xLen) ? frameData[key->x + frame] : frameData[key->x];
        frameTable->x = temp * 360.0f / 65536.0f;
        temp = (frame < key->yLen) ? frameData[key->y + frame] : frameData[key->y];
        frameTable->y = temp * 360.0f / 65536.0f;
        temp = (frame < key->zLen) ? frameData[key->z + frame] : frameData[key->z];
        frameTable->z = temp * 360.0f / 65536.0f;
    }
    return limbCount + 1;
}

s32 Animation_GetFrameCount(Animation* anim) {
    Animation* animation = LOAD_ASSET(anim);

    return animation->frameCount;
}

void Animation_FindBoundingBox(Gfx* dList, s32 len, Vec3f* min, Vec3f* max, s32* vtxFound, s32* vtxCount,
                               Vtx** vtxList) {
    s64* sp44 = SEGMENTED_TO_VIRTUAL(dList);
    s64* var_s0;

    for (var_s0 = sp44; (s32) (*var_s0 >> 0x38) != G_ENDDL && var_s0 - sp44 < len; var_s0++) {
        switch ((s32) (*var_s0 >> 0x38)) {
            case G_DL:
                Animation_FindBoundingBox(*var_s0 & 0xFFFFFFFF, (*var_s0 >> 0x20) & 0xFFFF, min, max, vtxFound,
                                          vtxCount, vtxList);
                break;
            case G_VTX:
                // *vtxList = SEGMENTED_TO_VIRTUAL(*var_s0 & 0xFFFFFFFF);
                *vtxCount = (*var_s0 >> 0x30) & 0xF;
                break;
            case G_TRI1:
                if (!*vtxFound) {
                    *vtxFound = 1;
                    max->x = min->x = (*vtxList)[*var_s0 & 0xFF].v.ob[0];
                    max->y = min->y = (*vtxList)[*var_s0 & 0xFF].v.ob[1];
                    max->z = min->z = (*vtxList)[*var_s0 & 0xFF].v.ob[2];
                } else {
                    min->x = MIN(min->x, (*vtxList)[*var_s0 & 0xFF].v.ob[0]);
                    min->y = MIN(min->y, (*vtxList)[*var_s0 & 0xFF].v.ob[1]);
                    min->z = MIN(min->z, (*vtxList)[*var_s0 & 0xFF].v.ob[2]);
                    max->x = MAX(max->x, (*vtxList)[*var_s0 & 0xFF].v.ob[0]);
                    max->y = MAX(max->y, (*vtxList)[*var_s0 & 0xFF].v.ob[1]);
                    max->z = MAX(max->z, (*vtxList)[*var_s0 & 0xFF].v.ob[2]);
                }
                min->x = MIN(min->x, (*vtxList)[(*var_s0 >> 8) & 0xFF].v.ob[0]);
                min->y = MIN(min->y, (*vtxList)[(*var_s0 >> 8) & 0xFF].v.ob[1]);
                min->z = MIN(min->z, (*vtxList)[(*var_s0 >> 8) & 0xFF].v.ob[2]);
                max->x = MAX(max->x, (*vtxList)[(*var_s0 >> 8) & 0xFF].v.ob[0]);
                max->y = MAX(max->y, (*vtxList)[(*var_s0 >> 8) & 0xFF].v.ob[1]);
                max->z = MAX(max->z, (*vtxList)[(*var_s0 >> 8) & 0xFF].v.ob[2]);
                min->x = MIN(min->x, (*vtxList)[(*var_s0 >> 0x10) & 0xFF].v.ob[0]);
                min->y = MIN(min->y, (*vtxList)[(*var_s0 >> 0x10) & 0xFF].v.ob[1]);
                min->z = MIN(min->z, (*vtxList)[(*var_s0 >> 0x10) & 0xFF].v.ob[2]);
                max->x = MAX(max->x, (*vtxList)[(*var_s0 >> 0x10) & 0xFF].v.ob[0]);
                max->y = MAX(max->y, (*vtxList)[(*var_s0 >> 0x10) & 0xFF].v.ob[1]);
                max->z = MAX(max->z, (*vtxList)[(*var_s0 >> 0x10) & 0xFF].v.ob[2]);
                break;
        }
    }
}

void Animation_GetDListBoundingBox(Gfx* dList, s32 len, Vec3f* min, Vec3f* max) {
    s32 vtxFound = false;
    s32 vtxCount;
    Vtx* vtxList;

    Animation_FindBoundingBox(dList, len, min, max, &vtxFound, &vtxCount, &vtxList);
}

void Animation_GetSkeletonBoundingBox(Limb** skeletonSegment, Animation* animationSegment, s32 frame, Vec3f* min,
                                      Vec3f* max) {
    JointKey* key;
    u16* frameData;
    Animation* animation;
    Limb* limb;
    u16 var_t6;
    s32 vtxFound;
    s32 vtxCount;
    Vtx* vtxList;
    Vec3f boundBox[8];
    Vec3f boundBoxRot[8];
    s32 i;
    Limb** skeleton = LOAD_ASSET(skeletonSegment);

    limb = SEGMENTED_TO_VIRTUAL(skeleton[0]);
    animation = LOAD_ASSET(animationSegment);
    key = SEGMENTED_TO_VIRTUAL(animation->jointKey);
    frameData = SEGMENTED_TO_VIRTUAL(animation->frameData);

    if (frame < (s16) key[1].zLen) {
        var_t6 = frameData[(s16) key[1].z + frame];
    } else {
        var_t6 = frameData[(s16) key[1].z];
    }
    Matrix_RotateZ(gGfxMatrix, (((s32) var_t6 * 360.0f) / 65536.0f) * M_DTOR, MTXF_NEW);
    if (frame < (s16) key[1].yLen) {
        var_t6 = frameData[(s16) key[1].y + frame];
    } else {
        var_t6 = frameData[(s16) key[1].y];
    }
    Matrix_RotateY(gGfxMatrix, (((s32) var_t6 * 360.0f) / 65536.0f) * M_DTOR, MTXF_APPLY);
    if (frame < (s16) key[1].xLen) {
        var_t6 = frameData[(s16) key[1].x + frame];
    } else {
        var_t6 = frameData[(s16) key[1].x];
    }
    Matrix_RotateX(gGfxMatrix, (((s32) var_t6 * 360.0f) / 65536.0f) * M_DTOR, MTXF_APPLY);
    vtxFound = false;
    if (limb->dList != NULL) {
        Animation_FindBoundingBox(limb->dList, 8192, min, max, &vtxFound, &vtxCount, &vtxList);
        if (vtxFound) {
            boundBox[0].x = boundBox[3].x = boundBox[4].x = boundBox[7].x = min->x;
            boundBox[0].y = boundBox[1].y = boundBox[4].y = boundBox[5].y = max->y;
            boundBox[0].z = boundBox[1].z = boundBox[2].z = boundBox[3].z = max->z;
            boundBox[1].x = boundBox[2].x = boundBox[5].x = boundBox[6].x = max->x;
            boundBox[2].y = boundBox[3].y = boundBox[6].y = boundBox[7].y = min->y;
            boundBox[4].z = boundBox[5].z = boundBox[6].z = boundBox[7].z = min->z;
            for (i = 0; i < 8; i++) {
                // Matrix_MultVec3f(gGfxMatrix, boundBox[i], boundBoxRot[i]); should logically go here
            }
            *min = *max = boundBoxRot[0];
            for (i = 1; i < 8; i++) {
                min->x = MIN(min->x, boundBoxRot[i].x);
                max->x = MAX(max->x, boundBoxRot[i].x);
                min->y = MIN(min->y, boundBoxRot[i].y);
                max->y = MAX(max->y, boundBoxRot[i].y);
                min->z = MIN(min->z, boundBoxRot[i].z);
                max->z = MAX(max->z, boundBoxRot[i].z);
            }
        }
    }
}

f32 Math_SmoothStepToF(f32* value, f32 target, f32 scale, f32 maxStep, f32 minStep) {
    f32 step = target - *value;

    if (step != 0.0f) {
        step *= scale;
        if ((step >= minStep) || (-minStep >= step)) {
            if (step > maxStep) {
                step = maxStep;
            } else if (step < -maxStep) {
                step = -maxStep;
            }
            *value += step;
        } else if (step < minStep) { // bug? should check sign, not size.
            step = minStep;
            *value += step;
            if (*value > target) {
                *value = target;
            }
        } else if (step > -minStep) {
            step = -minStep;
            *value += step;
            if (*value < target) {
                *value = target;
            }
        }
    }
    return step;
}

f32 Math_SmoothStepToAngle(f32* angle, f32 target, f32 scale, f32 maxStep, f32 minStep) {
    f32 var_fv1 = target - *angle;

    if (var_fv1 != 0.0f) {
        if (var_fv1 > 180.0f) {
            var_fv1 -= 360.0f;
        } else if (var_fv1 < -180.0f) {
            var_fv1 += 360.0f;
        }
        var_fv1 *= scale;
        if ((var_fv1 >= minStep) || (-minStep >= var_fv1)) {
            if (var_fv1 > maxStep) {
                var_fv1 = maxStep;
            } else if (var_fv1 < -maxStep) {
                var_fv1 = -maxStep;
            }
            *angle += var_fv1;
        } else if (var_fv1 < minStep) { // bug? should check sign, not size.
            var_fv1 = minStep;
            *angle += minStep;
            if (*angle > target) {
                *angle = target;
            }
        } else if (var_fv1 > -minStep) {
            var_fv1 = -minStep;
            *angle += var_fv1;
            if (*angle < target) {
                *angle = target;
            }
        }
    }
    if (*angle >= 360.0f) {
        *angle -= 360.0f;
    } else if (*angle < 0.0f) {
        *angle += 360.0f;
    }
    return var_fv1;
}

void Math_SmoothStepToVec3fArray(Vec3f* src, Vec3f* dst, s32 mode, s32 count, f32 scale, f32 maxStep, f32 minStep) {
    Vec3f* srcTemp;
    Vec3f* dstTemp;
    s32 i;

    switch (mode) {
        case 0:
            for (i = 0; i < count; i++) {
                dst[i].x = src[i].x;
                dst[i].y = src[i].y;
                dst[i].z = src[i].z;
            }
            break;
        case 1:
            dstTemp = dst;
            srcTemp = src;
            Math_SmoothStepToF(&dstTemp->x, srcTemp->x, scale, maxStep, minStep);
            Math_SmoothStepToF(&dstTemp->y, srcTemp->y, scale, maxStep, minStep);
            Math_SmoothStepToF(&dstTemp->z, srcTemp->z, scale, maxStep, minStep);
            dstTemp++;
            srcTemp++;

            for (i = 1; i < count; i++, dstTemp++, srcTemp++) {
                Math_SmoothStepToAngle(&dstTemp->x, srcTemp->x, scale, maxStep, minStep);
                Math_SmoothStepToAngle(&dstTemp->y, srcTemp->y, scale, maxStep, minStep);
                Math_SmoothStepToAngle(&dstTemp->z, srcTemp->z, scale, maxStep, minStep);
            }
            break;
        default:
            break;
    }
}

s32 Math_PursueVec3f(Vec3f* pos, Vec3f* target, Vec3f* rot, f32 stepSize, f32 scaleTurn, f32 maxTurn, f32 dist) {
    Vec3f diff;
    f32 targetRotX;
    f32 targetRotY;
    Vec3f localStep = { 0.0f, 0.0f, 0.0f };
    Vec3f worldStep;
    Matrix worldTransform;

    diff.x = target->x - pos->x;
    diff.y = target->y - pos->y;
    diff.z = target->z - pos->z;

    targetRotY = Math_RadToDeg(Math_Atan2F(diff.x, diff.z));
    targetRotX = Math_RadToDeg(-Math_Atan2F(diff.y, sqrtf(SQ(diff.x) + SQ(diff.z))));
    Math_SmoothStepToAngle(&rot->y, targetRotY, scaleTurn, maxTurn, 0.0f);
    Math_SmoothStepToAngle(&rot->x, targetRotX, scaleTurn, maxTurn, 0.0f);
    Matrix_RotateY(&worldTransform, rot->y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(&worldTransform, rot->x * M_DTOR, MTXF_APPLY);
    localStep.z = stepSize;
    Matrix_MultVec3fNoTranslate(&worldTransform, &localStep, &worldStep);

    pos->x += worldStep.x;
    pos->y += worldStep.y;
    pos->z += worldStep.z;

    diff.x = target->x - pos->x;
    diff.y = target->y - pos->y;
    diff.z = target->z - pos->z;

    return (VEC3F_MAG(&diff)) < dist;
}

void Lib_TextureRect_CI4(Gfx** gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                         f32 yScale) {
    gDPLoadTLUT_pal16((*gfxPtr)++, 0, palette);
    gDPLoadTextureBlock_4b((*gfxPtr)++, texture, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_CI4_Flip(Gfx** gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos,
                              f32 xScale, f32 yScale) {
    gDPLoadTLUT_pal16((*gfxPtr)++, 0, palette);
    gDPLoadTextureBlock_4b((*gfxPtr)++, texture, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangleFlip((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_CI4_MirX(Gfx** gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos,
                              f32 xScale, f32 yScale) {
    gDPLoadTLUT_pal16((*gfxPtr)++, 0, palette);
    gDPLoadTextureBlock_4b((*gfxPtr)++, texture, G_IM_FMT_CI, width, height, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, (width - 1) * 32, 0, (u16) (s32) (-1.0f / xScale * 1024.0f),
                            (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_CI4_MirY(Gfx** gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos,
                              f32 xScale, f32 yScale) {
    gDPLoadTLUT_pal16((*gfxPtr)++, 0, palette);
    gDPLoadTextureBlock_4b((*gfxPtr)++, texture, G_IM_FMT_CI, width, height, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, (height - 1) * 32, (s32) (1.0f / xScale * 1024.0f),
                            (u16) (s32) (-1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_CI8(Gfx** gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                         f32 yScale) {
    gDPLoadTLUT_pal256((*gfxPtr)++, palette);
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_RGBA16(Gfx** gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                            f32 yScale) {
    gDPSetTileCustom((*gfxPtr)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTextureImage((*gfxPtr)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, texture);
    gDPLoadSync((*gfxPtr)++);
    gDPLoadTile((*gfxPtr)++, G_TX_LOADTILE, 0, 0, width - 1 << 2, height - 1 << 2);

    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_RGBA16_MirX(Gfx** gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                                 f32 yScale) {
    gDPSetTileCustom((*gfxPtr)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTextureImage((*gfxPtr)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, texture);
    gDPLoadSync((*gfxPtr)++);
    gDPLoadTile((*gfxPtr)++, G_TX_LOADTILE, 0, 0, width - 1 << 2, height - 1 << 2);

    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, (width /* - 1*/) * 32, 0, (u16) (s32) (-1.0f / xScale * 1024.0f),
                            (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA8(Gfx** gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale) {
    gDPSetTileCustom((*gfxPtr)++, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTextureImage((*gfxPtr)++, G_IM_FMT_IA, G_IM_SIZ_8b, width, texture);
    gDPLoadSync((*gfxPtr)++);
    gDPLoadTile((*gfxPtr)++, G_TX_LOADTILE, 0, 0, width - 1 << 2, height - 1 << 2);

    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA8_FlipMirX(Gfx** gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                                  f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangleFlip((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + height * xScale) * 4.0f), (s32) ((yPos + width * yScale) * 4.0f),
                            G_TX_RENDERTILE, (width - 1) * 32, 0, (u16) (s32) (-1.0f / yScale * 1024.0f),
                            (s32) (1.0f / xScale * 1024.0f));
}

void Lib_TextureRect_IA8_FlipMirY(Gfx** gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                                  f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangleFlip((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + height * xScale) * 4.0f), (s32) ((yPos + width * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, (height - 1) * 32, (s32) (1.0f / yScale * 1024.0f),
                            (u16) (s32) (-1.0f / xScale * 1024.0f));
}

void Lib_TextureRect_IA8_MirX(Gfx** gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                              f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, (width - 1) * 32, 0, (u16) (s32) (-1.0f / xScale * 1024.0f),
                            (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA8_MirY(Gfx** gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                              f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, (height - 1) * 32, (s32) (1.0f / xScale * 1024.0f),
                            (u16) (s32) (-1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA16(Gfx** gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                          f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA16_MirX(Gfx** gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                               f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, (width - 1) * 32, 0, (u16) (s32) (-1.0f / xScale * 1024.0f),
                            (s32) (1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA16_MirY(Gfx** gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                               f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, (height - 1) * 32, (s32) (1.0f / xScale * 1024.0f),
                            (u16) (s32) (-1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_IA16_MirXY(Gfx** gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                                f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_IA, G_IM_SIZ_16b, width, height, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, (width - 1) * 32, (height - 1) * 32,
                            (u16) (s32) (-1.0f / xScale * 1024.0f), (u16) (s32) (-1.0f / yScale * 1024.0f));
}

void Lib_TextureRect_RGBA32(Gfx** gfxPtr, u32* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale,
                            f32 yScale) {
    gDPLoadTextureBlock((*gfxPtr)++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPWideTextureRectangle((*gfxPtr)++, (s32) (xPos * 4.0f), (s32) (yPos * 4.0f),
                            (s32) ((xPos + width * xScale) * 4.0f), (s32) ((yPos + height * yScale) * 4.0f),
                            G_TX_RENDERTILE, 0, 0, (s32) (1.0f / xScale * 1024.0f), (s32) (1.0f / yScale * 1024.0f));
}

void Graphics_FillRectangle(Gfx** gfxPtr, s32 ulx, s32 uly, s32 lrx, s32 lry, u8 r, u8 g, u8 b, u8 a) {
    if (a != 0) {
        gDPPipeSync((*gfxPtr)++);
        gDPSetPrimColor((*gfxPtr)++, 0x00, 0x00, r, g, b, a);
        gDPSetColorDither((*gfxPtr)++, G_CD_NOISE);
        gDPSetAlphaDither((*gfxPtr)++, G_AD_NOISE);
        gDPSetCycleType((*gfxPtr)++, G_CYC_1CYCLE);
        gDPSetCombineMode((*gfxPtr)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetRenderMode((*gfxPtr)++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPFillWideRectangle((*gfxPtr)++, ulx, uly, lrx, lry);
    }
}

void Math_Vec3fFromAngles(Vec3f* step, f32 xRot, f32 yRot, f32 stepsize) {
    Vec3f sp1C;

    Matrix_RotateY(gCalcMatrix, yRot * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, xRot * M_DTOR, MTXF_APPLY);
    sp1C.x = sp1C.y = 0.0f;
    sp1C.z = stepsize;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp1C, step);
}

f32 Math_RadToDeg(f32 rAngle) {
    rAngle *= M_RTOD;

    while (rAngle < 0.0f) {
        rAngle += 360.0f;
    }
    return rAngle;
}

u16* Graphics_SetupTextureRender(Gfx** gfxPtr, u8 width, u8 height) {
    u16* texture;
    u16 norm;

    width += 0xF;
    width &= 0x70;
    texture = gTextureRender;
    gTextureRender = gTextureRender + width * height;
    gDPPipeSync((*gfxPtr)++);
    gDPSetCycleType((*gfxPtr)++, G_CYC_FILL);
    gDPSetRenderMode((*gfxPtr)++, G_RM_NOOP, G_RM_NOOP2);
    gViewport->vp.vscale[0] = width * 2;
    gViewport->vp.vscale[1] = height * 2;
    gViewport->vp.vscale[2] = G_MAXZ / 2;
    gViewport->vp.vscale[3] = 0;
    gViewport->vp.vtrans[0] = width * 2;
    gViewport->vp.vtrans[1] = height * 2;
    gViewport->vp.vtrans[2] = G_MAXZ / 2;
    gViewport->vp.vtrans[3] = 0;
    gSPViewport((*gfxPtr)++, gViewport++);
    gDPSetScissor((*gfxPtr)++, G_SC_NON_INTERLACE, 0, 0, width, height);
    gDPSetDepthImage((*gfxPtr)++, &gZBuffer);
    gDPSetColorImage((*gfxPtr)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, &gZBuffer);
    gDPSetFillColor((*gfxPtr)++, FILL_COLOR(GPACK_ZDZ(G_MAXFBZ, 0)));
    gDPFillRectangle((*gfxPtr)++, 0, 0, width - 1, height - 1);
    gDPPipeSync((*gfxPtr)++);
    gDPSetDepthSource((*gfxPtr)++, G_ZS_PIXEL);
    gDPSetColorImage((*gfxPtr)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, texture);
    gDPSetColorDither((*gfxPtr)++, G_CD_DISABLE);
    gDPSetFillColor((*gfxPtr)++, 0);
    gDPSetFillColor((*gfxPtr)++, FILL_COLOR(gBgColor | 1));
    gDPFillRectangle((*gfxPtr)++, 0, 0, width - 1, height - 1);
    gDPPipeSync((*gfxPtr)++);
    guPerspective(gGfxMtx, &norm, gFovY, (f32) width / height, 10.0f, 12800.0f, 1.0f);
    gSPPerspNormalize((*gfxPtr)++, norm);
    gSPMatrix((*gfxPtr)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(gGfxMtx, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -12800.0f, 0.0f, 1.0f, 0.0f);
    gSPMatrix((*gfxPtr)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    Matrix_Copy(gGfxMatrix, &gIdentityMatrix);

    return texture;
}

void Graphics_DisplayHUDNumber(s32 xPos, s32 yPos, s32 number) {
    u8* hudNumberTex[] = { D_1010660, D_10106B0, D_1010700, D_1010750, D_10107A0,
                           D_10107F0, D_1010840, D_1010890, D_10108E0, D_1010930 };
    u16* hudNumberPal[] = { D_10106A0, D_10106F0, D_1010740, D_1010790, D_10107E0,
                            D_1010830, D_1010880, D_10108D0, D_1010920, D_1010970 };
    s32 place;
    s32 startNumber = false;

    number %= 10000000;
    place = 1000000;
    for (place = 1000000; place != 1; place /= 10) {
        if ((number / place != 0) || (startNumber == true)) {
            Lib_TextureRect_CI4(&gMasterDisp, hudNumberTex[number / place], hudNumberPal[number / place], 16, 8, xPos,
                                yPos, 1.0f, 1.0f);
            startNumber = true;
            xPos += 9;
            number %= place;
        }
    }
    Lib_TextureRect_CI4(&gMasterDisp, hudNumberTex[number / place], hudNumberPal[number / place], 16, 8, xPos, yPos,
                        1.0f, 1.0f);
}

u8* sSmallNumberTex[] = { aSmallText_0, aSmallText_1, aSmallText_2, aSmallText_3, aSmallText_4,
                          aSmallText_5, aSmallText_6, aSmallText_7, aSmallText_8, aSmallText_9 };

void Graphics_DisplaySmallNumber(s32 xPos, s32 yPos, s32 number) {
    s32 place;
    s32 startNumber = false;

    number %= 10000000;
    place = 1000000;
    for (place = 1000000; place != 1; place /= 10) {
        if ((number / place != 0) || (startNumber == true)) {
            Lib_TextureRect_IA8(&gMasterDisp, sSmallNumberTex[number / place], 16, 8, xPos, yPos, 1.0f, 1.0f);
            startNumber = true;
            xPos += 9;
            number %= place;
        }
    }
    Lib_TextureRect_IA8(&gMasterDisp, sSmallNumberTex[number / place], 16, 8, xPos, yPos, 1.0f, 1.0f);
}

char sSmallChars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ!:-.0123456789";
char sLargeChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ. 0123456789st-";
u8 sLargeCharWidths[] = { 15, 14, 14, 13, 13, 13, 14, 14, 5,  12, 14, 12, 16, 14, 15, 13, 16, 14, 13, 13, 13,
                          16, 17, 17, 16, 13, 5,  16, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 10, 9,  14, 0 };
u8* sLargeCharTex[] = {
    aLargeText_A, aLargeText_B, aLargeText_C, aLargeText_D,  aLargeText_E,  aLargeText_F,      aLargeText_G,
    aLargeText_H, aLargeText_I, aLargeText_J, aLargeText_K,  aLargeText_L,  aLargeText_M,      aLargeText_N,
    aSmallText_O, aLargeText_P, aLargeText_Q, aLargeText_R,  aLargeText_S,  aLargeText_T,      aLargeText_U,
    aLargeText_V, aLargeText_W, aLargeText_X, aLargeText_Y,  aLargeText_Z,  aLargeText_DOT,    NULL,
    aLargeText_0, aLargeText_1, aLargeText_2, aLargeText_3,  aLargeText_4,  aLargeText_5,      aLargeText_6,
    aLargeText_7, aLargeText_8, aLargeText_9, aLargeText_s_, aLargeText_t_, aLargeText_HYPHEN,
};
u8* sLargeNumberTex[] = {
    aLargeText_0, aLargeText_1, aLargeText_2, aLargeText_3, aLargeText_4,
    aLargeText_5, aLargeText_6, aLargeText_7, aLargeText_8, aLargeText_9,
};
u8* sSmallCharTex[] = { NULL,           aSmallText_A, aSmallText_B,         aSmallText_C,     aSmallText_D,
                        aSmallText_E,   aSmallText_F, aSmallText_G,         aSmallText_H,     aSmallText_I,
                        aSmallText_J,   aSmallText_K, aSmallText_L,         aSmallText_M,     aSmallText_N,
                        aSmallText_o_,  aSmallText_p, aSmallText_q,         aSmallText_r,     aSmallText_s,
                        aSmallText_T,   aSmallText_U, aSmallText_V,         aSmallText_W,     aSmallText_X,
                        aSmallText_Y,   aSmallText_Z, aSmallTextExclamMark, aSmallText_COLON, aSmallText_HYPHEN,
                        aSmallText_DOT, aSmallText_0, aSmallText_1,         aSmallText_2,     aSmallText_3,
                        aSmallText_4,   aSmallText_5, aSmallText_6,         aSmallText_7,     aSmallText_8,
                        aSmallText_9 };

void Graphics_DisplayLargeText(s32 xPos, s32 yPos, f32 xScale, f32 yScale, char* text) {
    u32 charIndex;
    f32 xPosCurrent = xPos;
    s32 pad4C;
    s32 width;
    s32 startPrint = false;

    while (text[0] != 0) {
        charIndex = 0;
        while ((charIndex < ARRAY_COUNT(sLargeChars)) && sLargeChars[charIndex] != text[0]) {
            charIndex++;
        }
        if (sLargeChars[charIndex] == text[0]) {
            if ((startPrint == true) && (text[-1] == 'Y') && (text[0] == 'A')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'A')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'O')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'T') && (text[0] == 'A')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'Y')) {
                xPosCurrent -= 4.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'I')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'O')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'J')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'W') && (text[0] == 'A')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'Y') && (text[0] == 'O')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'T')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'W')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'O') && (text[0] == 'T')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'G')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'O') && (text[0] == 'Y')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'J')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'T') && (text[0] == 'O')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'U')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'S')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'R') && (text[0] == 'O')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'Y')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'N') && (text[0] == 'J')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'E')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'S') && (text[0] == 't')) {
                xPosCurrent -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'X') && (text[0] == 'X')) {
                xPosCurrent -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'O') && (text[0] == 'X')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'W') && (text[0] == 'W')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'X') && (text[0] == 'W')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'W') && (text[0] == 'X')) {
                xPosCurrent -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'H') && (text[0] == 'O')) {
                xPosCurrent += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'J') && (text[0] == 'I')) {
                xPosCurrent += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'I') && (text[0] == 'N')) {
                xPosCurrent += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'I') && (text[0] == 'M')) {
                xPosCurrent += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'I') && (text[0] == 'D')) {
                xPosCurrent += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'U') && (text[0] == 'K')) {
                xPosCurrent += 1.0f;
            }
            if (sLargeCharTex[charIndex] != NULL) {
                width = 16;
                if ((text[0] == 'W') || (text[0] == 'X')) {
                    width = 32;
                }
                Lib_TextureRect_IA8(&gMasterDisp, sLargeCharTex[charIndex], width, 15, xPosCurrent, yPos, xScale,
                                    yScale);
            }
            startPrint = true;
            xPosCurrent += (sLargeCharWidths[charIndex] * xScale) + 2.0f;
        }
        text++;
    }
}

s32 Graphics_GetLargeTextWidth(char* text) {
    s32 startPrint = false;
    s32 xPos = 0;
    u32 charIndex;

    while (text[0] != 0) {
        charIndex = 0;
        while ((charIndex < ARRAY_COUNT(sLargeChars)) && sLargeChars[charIndex] != text[0]) {
            charIndex++;
        }
        if (sLargeChars[charIndex] == text[0]) {
            if ((startPrint == true) && (text[-1] == 'Y') && (text[0] == 'A')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'A')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'O')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'T') && (text[0] == 'A')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'Y')) {
                xPos -= 4.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'I')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'O')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'J')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'W') && (text[0] == 'A')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'Y') && (text[0] == 'O')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'T')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'W')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'O') && (text[0] == 'T')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'G')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'O') && (text[0] == 'Y')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'J')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'T') && (text[0] == 'O')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'U')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'A') && (text[0] == 'S')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'R') && (text[0] == 'O')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'Y')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'N') && (text[0] == 'J')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'K') && (text[0] == 'E')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'S') && (text[0] == 't')) {
                xPos -= 2.0f;
            }
            if ((startPrint == true) && (text[-1] == 'X') && (text[0] == 'X')) {
                xPos -= 3.0f;
            }
            if ((startPrint == true) && (text[-1] == 'O') && (text[0] == 'X')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'W') && (text[0] == 'W')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'X') && (text[0] == 'W')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'W') && (text[0] == 'X')) {
                xPos -= 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'H') && (text[0] == 'O')) {
                xPos += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'J') && (text[0] == 'I')) {
                xPos += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'I') && (text[0] == 'N')) {
                xPos += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'I') && (text[0] == 'M')) {
                xPos += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'I') && (text[0] == 'D')) {
                xPos += 1.0f;
            }
            if ((startPrint == true) && (text[-1] == 'U') && (text[0] == 'K')) {
                xPos += 1.0f;
            }
            startPrint = true;
            xPos += sLargeCharWidths[charIndex] + 2.0f;
        }
        text++;
    }
    return xPos;
}

void Graphics_DisplayLargeNumber(s32 xPos, s32 yPos, s32 number) {
    s32 place;
    s32 startNumber = false;

    number %= 10000000;
    place = 1000000;
    for (place = 1000000; place != 1; place /= 10) {
        if ((number / place != 0) || (startNumber == true)) {
            Lib_TextureRect_IA8(&gMasterDisp, sLargeNumberTex[number / place], 16, 15, xPos, yPos, 1.0f, 1.0f);
            startNumber = true;
            xPos += 13;
            number %= place;
        }
    }
    Lib_TextureRect_IA8(&gMasterDisp, sLargeNumberTex[number / place], 16, 15, xPos, yPos, 1.0f, 1.0f);
}

void Graphics_DisplaySmallText(s32 xPos, s32 yPos, f32 xScale, f32 yScale, char* text) {
    u32 var_t0;
    f32 xPosCurrent = xPos;
    s32 width;

    while (text[0] != 0) {
        var_t0 = 0;
        while ((var_t0 < ARRAY_COUNT(sSmallChars)) && sSmallChars[var_t0] != text[0]) {
            var_t0++;
        }
        if (sSmallChars[var_t0] == text[0]) {
            if (sSmallCharTex[var_t0] != NULL) {
                width = 8;
                if (var_t0 > 30) {
                    width = 16;
                }
                Lib_TextureRect_IA8(&gMasterDisp, sSmallCharTex[var_t0], width, 8, xPosCurrent, yPos, xScale, yScale);
                if (1) {}
            }
            switch (text[0]) {
                case '!':
                case ':':
                case 'I':
                    xPosCurrent += 4.0f * xScale;
                    break;
                case '-':
                    xPosCurrent += 6.0f * xScale;
                    break;
                default:
                    if (var_t0 >= 30) {
                        xPosCurrent += 9.0f * xScale;
                    } else {
                        xPosCurrent += 8.0f * xScale;
                    }
            }
        }
        text++;
    }
}

s32 Graphics_GetSmallTextWidth(char* text) {
    u32 charIndex;
    s32 xPos = 0;

    while (text[0] != 0) {
        charIndex = 0;
        while ((charIndex < ARRAY_COUNT(sSmallChars)) && sSmallChars[charIndex] != text[0]) {
            charIndex++;
        }
        if (sSmallChars[charIndex] == text[0]) {
            switch (text[0]) {
                case '!':
                case ':':
                case 'I':
                    xPos += 4.0f;
                    break;
                case '-':
                    xPos += 6.0f;
                    break;
                default:
                    if (charIndex >= 30) {
                        xPos += 9.0f;
                    } else {
                        xPos += 8.0f;
                    }
            }
        }
        text++;
    }
    return xPos;
}

void func_stdlib_800A1540(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}

// 20 kinds of fake. Try to improve it here: https://decomp.me/scratch/NMQZB
void Texture_BlendRGBA16(f32 weight, u16 size, u16* src1, u16* src2, u16* dst) {
    s32 i;
    u16* var_a1 = LOAD_ASSET(src1);
    u16* var_a2 = LOAD_ASSET(src2);
    u16* var_a3 = LOAD_ASSET(dst);
    u16 temp1;
    u16 temp2;
    u16 temp3;
    f32 r1;
    f32 g1;
    f32 b1;
    s32 a1;
    f32 r2;
    f32 g2;
    f32 b2;
    s32 a2;
    f32 red;
    f32 grn;
    f32 blu;
    g2 = RGBA16_GRN(temp2); // mega fake

    for (i = 0; i < size; i++) {
        temp1 = var_a1[i];
        r1 = RGBA16_RED(temp1);
        g1 = RGBA16_GRN(temp1);
        b1 = RGBA16_BLU(temp1);
        temp1 = temp1 & 1; // fake?
        if (1) {}          // fake?
        temp2 = var_a2[i];
        r2 = RGBA16_RED(temp2);
        g2 = RGBA16_GRN(temp2);
        b2 = RGBA16_BLU(temp2);
        a2 = temp2 & 1;

        red = (r2 - r1) * weight / 100.0f + r1;
        grn = (g2 - g1) * weight / 100.0f + g1;
        blu = (b2 - b1) * weight / 100.0f + b1;

        var_a3[i] = ((u16) (red * 2048.0f) & 0xF800) | ((u16) (grn * 64.0f) & 0x7C0) | ((u16) (blu * 2.0f) & 0x3E) |
                    (temp1 | a2 & 1);
    }
}
