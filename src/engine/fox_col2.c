#include "global.h"

#include "fox_colheaders.c"

bool func_col2_800A36FC(Vec3f* objPos, Vec3f* colliderPos, CollisionHeader2* colHeader, Vec3f* hitDataOut);
bool func_col2_800A3A74(Vec3f* point, Vec3f** tri, Vec3f* normOut);

bool func_col2_800A3690(Vec3f* objPos, Vec3f* colliderPos, s32 colId, Vec3f* hitDataOut) {
    return func_col2_800A36FC(objPos, colliderPos, LOAD_ASSET(&D_800D2CA0[colId]), hitDataOut);
}

bool func_col2_800A36FC(Vec3f* objPos, Vec3f* colliderPos, CollisionHeader2* colHeader, Vec3f* hitDataOut) {
    Vec3f objRelPos;
    PlaneF triPlane;
    bool above;
    s32 i;
    s32 j;
    Vec3f* tri[3];
    Vec3f norm;
    Vec3f vtx;
    s32 sp38 = false;
    s32 count;
    Triangle* polys;
    Vec3f* mesh;

    objRelPos.x = objPos->x - colliderPos->x;
    objRelPos.y = objPos->y - colliderPos->y;
    objRelPos.z = objPos->z - colliderPos->z;
    if ((objRelPos.x < colHeader->min.x) || (objRelPos.y < colHeader->min.y) || (objRelPos.z < colHeader->min.z) ||
        (colHeader->max.x < objRelPos.x) || (colHeader->max.y < objRelPos.y) || (colHeader->max.z < objRelPos.z)) {
        return false;
    }
    above = false;
    count = colHeader->polyCount;
    polys = LOAD_ASSET(colHeader->polys);
    mesh = LOAD_ASSET(colHeader->mesh);
    for (i = 0; i < count; i++, polys++) {
        for (j = 0; j < 3; j++) {
            tri[j] = &mesh[polys->vtx[j]];
        }
        above = func_col2_800A3A74(&objRelPos, tri, &norm);
        if (above) {
            break;
        }
    }
    if (above) {
        vtx.x = tri[0]->x;
        vtx.y = tri[0]->y;
        vtx.z = tri[0]->z;
        func_col1_80098860(&triPlane, &vtx, &norm);
        hitDataOut->y = func_col1_800988B4(&objRelPos, &triPlane);
        if (triPlane.normal.x != 0.0f) {
            norm.x = -triPlane.dist / triPlane.normal.x;
        } else {
            norm.x = 0.0f;
        }
        if (triPlane.normal.y != 0.0f) {
            norm.y = -triPlane.dist / triPlane.normal.y;
        } else {
            norm.y = 0.0f;
        }
        if (triPlane.normal.z != 0.0f) {
            norm.z = -triPlane.dist / triPlane.normal.z;
        } else {
            norm.z = 0.0f;
        }
        hitDataOut->x = Math_Atan2F_XY(norm.y, norm.z);
        if (norm.z != 0.0f) {
            hitDataOut->z = -Math_Atan2F_XY(__sinf(Math_Atan2F_XY(norm.y, norm.z)) * norm.z, norm.x);
        } else if (hitDataOut->x >= M_PI) {
            hitDataOut->z = Math_Atan2F_XY(norm.y, norm.x);
        } else {
            hitDataOut->z = -Math_Atan2F_XY(norm.y, norm.x);
        }
        if ((objPos->y - hitDataOut->y <= 0.0f) || (gCurrentLevel == LEVEL_MACBETH)) {
            sp38 = true;
        }
    }
    return sp38;
}

// Checks if point is above the triangle tri. If so, puts the triangle normal in normOut
bool func_col2_800A3A74(Vec3f* point, Vec3f** tri, Vec3f* normOut) {
    s32 pad;
    f32 temp1;
    bool ret = false;
    f32 temp_fv0;
    Vec3f vtx1;
    Vec3f vtx2;
    Vec3f vtx3;
    f32 ptx;
    f32 ptz;

    vtx1.x = (*tri)->x;
    vtx1.y = (*tri)->y;
    vtx1.z = (*tri)->z;
    tri++;
    vtx2.x = (*tri)->x;
    vtx2.y = (*tri)->y;
    vtx2.z = (*tri)->z;
    tri++;
    vtx3.x = (*tri)->x;
    vtx3.y = (*tri)->y;
    vtx3.z = (*tri)->z;
    tri++;

    ptx = point->x;
    ptz = point->z;
    temp1 = ((vtx2.z - vtx1.z) * (ptx - vtx2.x)) - ((vtx2.x - vtx1.x) * (ptz - vtx2.z));
    if (temp1 >= 0.0f) {
        if (((vtx3.x - vtx2.x) * (ptz - vtx3.z)) <= ((vtx3.z - vtx2.z) * (ptx - vtx3.x))) {
            if (((vtx1.x - vtx3.x) * (ptz - vtx1.z)) <= ((vtx1.z - vtx3.z) * (ptx - vtx1.x))) {
                ret = true;
                normOut->x = ((vtx2.y - vtx1.y) * (vtx3.z - vtx2.z)) - ((vtx2.z - vtx1.z) * (vtx3.y - vtx2.y));
                normOut->y = ((vtx2.z - vtx1.z) * (vtx3.x - vtx2.x)) - ((vtx2.x - vtx1.x) * (vtx3.z - vtx2.z));
                normOut->z = ((vtx2.x - vtx1.x) * (vtx3.y - vtx2.y)) - ((vtx2.y - vtx1.y) * (vtx3.x - vtx2.x));
                if ((normOut->x != 0.0f) || (normOut->y != 0.0f) || (normOut->z != 0.0f)) {
                    temp_fv0 = VEC3F_MAG(normOut);
                    if (temp_fv0 != 0) {
                        normOut->x = (normOut->x / temp_fv0) * 127.0f;
                        normOut->y = (normOut->y / temp_fv0) * 127.0f;
                        normOut->z = (normOut->z / temp_fv0) * 127.0f;
                    }
                }
            }
        }
    }
    return ret;
}
