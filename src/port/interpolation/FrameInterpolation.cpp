#include <libultraship/bridge.h>

#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include "port/Engine.h"

#include "FrameInterpolation.h"

/*
Frame interpolation.

The idea of this code is to interpolate all matrices.

The code contains two approaches. The first is to interpolate
all inputs in transformations, such as angles, scale and distances,
and then perform the same transformations with the interpolated values.
After evaluation for some reason some animations such rolling look strange.

The second approach is to simply interpolate the final matrices. This will
more or less simply interpolate the world coordinates for movements.
This will however make rotations ~180 degrees get the "paper effect".
The mitigation is to identify this case for actors and interpolate the
matrix but in model coordinates instead, by "removing" the rotation-
translation before interpolating, create a rotation matrix with the
interpolated angle which is then applied to the matrix.

Currently the code contains both methods but only the second one is currently
used.

Both approaches build a tree of instructions, containing matrices
at leaves. Every node is built from OPEN_DISPS/CLOSE_DISPS and manually
inserted FrameInterpolation_OpenChild/FrameInterpolation_Close child calls.
These nodes contain information that should suffice to identify the matrix,
so we can find it in an adjacent frame.

We can interpolate an arbitrary amount of frames between two original frames,
given a specific interpolation factor (0=old frame, 0.5=average of frames,
1.0=new frame).
*/

static bool invert_matrix(const float m[16], float invOut[16]);

using namespace std;

namespace {

enum class Op {
    Marker,
    OpenChild,
    CloseChild,

    MatrixPush,
    MatrixPop,
    MatrixPut,
    MatrixMult,
    MatrixTranslate,
    MatrixScale,
    MatrixRotate1Coord,
    MatrixMultVec3fNoTranslate,
    MatrixMultVec3f,
    MatrixMtxFToMtx,
    MatrixToMtx,
    MatrixRotateAxis,
    SkinMatrixMtxFToMtx
};

typedef pair<const void*, int> label;

union Data {
    Data() {
    }

    struct {
        Matrix** matrix;
    } matrix_ptr;

    struct {
        const char* file;
        int line;
    } marker;

    struct {
        Matrix* matrix;
        MtxF mf;
        u8 mode;
    } matrix_mult;

    struct {
        Matrix* matrix;
        f32 x, y, z;
        u8 mode;
    } matrix_translate, matrix_scale;

    struct {
        Matrix* matrix;
        u32 coord;
        f32 value;
        u8 mode;
    } matrix_rotate_1_coord;

    struct {
        Matrix* matrix;
        Vec3f src;
        Vec3f dest;
    } matrix_vec_translate;

    struct {
        Matrix* matrix;
        Vec3f src;
        Vec3f dest;
    } matrix_vec_no_translate;

    struct {
        Matrix* matrix;
        Vec3f translation;
        Vec3s rotation;
    } matrix_translate_rotate_zyx;

    struct {
        Matrix* matrix;
        f32 translateX, translateY, translateZ;
        Vec3s rot;
        // MtxF mtx;
        bool has_mtx;
    } matrix_set_translate_rotate_yxz;

    struct {
        MtxF src;
        Mtx* dest;
    } matrix_mtxf_to_mtx;

    struct {
        Mtx* dest;
        MtxF src;
        bool has_adjusted;
    } matrix_to_mtx;

    struct {
        MtxF mf;
    } matrix_replace_rotation;

    struct {
        f32 angle;
        Vec3f axis;
        u8 mode;
    } matrix_rotate_axis;

    struct {
        label key;
        size_t idx;
    } open_child;
};

struct Path {
    map<label, vector<Path>> children;
    map<Op, vector<Data>> ops;
    vector<pair<Op, size_t>> items;
};

struct Recording {
    Path root_path;
};

bool is_recording;
vector<Path*> current_path;
uint32_t camera_epoch;
uint32_t previous_camera_epoch;
Recording current_recording;
Recording previous_recording;

bool next_is_actor_pos_rot_matrix;
bool has_inv_actor_mtx;
MtxF inv_actor_mtx;
size_t inv_actor_mtx_path_index;

Data& append(Op op) {
    auto& m = current_path.back()->ops[op];
    current_path.back()->items.emplace_back(op, m.size());
    return m.emplace_back();
}

MtxF* Matrix_GetCurrent(){
    return (MtxF*) gInterpolationMatrix;
}

struct InterpolateCtx {
    float step;
    float w;
    unordered_map<Mtx*, MtxF> mtx_replacements;
    MtxF tmp_mtxf, tmp_mtxf2;
    Vec3f tmp_vec3f, tmp_vec3f2;
    Vec3s tmp_vec3s;
    MtxF actor_mtx;

    MtxF* new_replacement(Mtx* addr) {
        return &mtx_replacements[addr];
    }

    void interpolate_mtxf(MtxF* res, MtxF* o, MtxF* n) {
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                res->mf[i][j] = w * o->mf[i][j] + step * n->mf[i][j];
            }
        }
    }

    float lerp(f32 o, f32 n) {
        return w * o + step * n;
    }

    void lerp_vec3f(Vec3f* res, Vec3f* o, Vec3f* n) {
        res->x = lerp(o->x, n->x);
        res->y = lerp(o->y, n->y);
        res->z = lerp(o->z, n->z);
    }

    float interpolate_angle(f32 o, f32 n) {
        if (o == n)
            return n;
        o = fmodf(o, 2 * M_PI);
        if (o < 0.0f) {
            o += 2 * M_PI;
        }
        n = fmodf(n, 2 * M_PI);
        if (n < 0.0f) {
            n += 2 * M_PI;
        }
        if (fabsf(o - n) > M_PI) {
            if (o < n) {
                o += 2 * M_PI;
            } else {
                n += 2 * M_PI;
            }
        }
        if (fabsf(o - n) > M_PI / 2) {
            // return n;
        }
        return lerp(o, n);
    }

    s16 interpolate_angle(s16 os, s16 ns) {
        if (os == ns)
            return ns;
        int o = (u16)os;
        int n = (u16)ns;
        u16 res;
        int diff = o - n;
        if (-0x8000 <= diff && diff <= 0x8000) {
            if (diff < -0x4000 || diff > 0x4000) {
                return ns;
            }
            res = (u16)(w * o + step * n);
        } else {
            if (o < n) {
                o += 0x10000;
            } else {
                n += 0x10000;
            }
            diff = o - n;
            if (diff < -0x4000 || diff > 0x4000) {
                return ns;
            }
            res = (u16)(w * o + step * n);
        }
        if (os / 327 == ns / 327 && (s16)res / 327 != os / 327) {
            int bp = 0;
        }
        return res;
    }

    void interpolate_vecs(Vec3f* res, Vec3f* o, Vec3f* n) {
        res->x = interpolate_angle(o->x, n->x);
        res->y = interpolate_angle(o->y, n->y);
        res->z = interpolate_angle(o->z, n->z);
    }

    void interpolate_angles(Vec3s* res, Vec3s* o, Vec3s* n) {
        res->x = interpolate_angle(o->x, n->x);
        res->y = interpolate_angle(o->y, n->y);
        res->z = interpolate_angle(o->z, n->z);
    }

    void interpolate_branch(Path* old_path, Path* new_path) {
        for (auto& item : new_path->items) {
            Data& new_op = new_path->ops[item.first][item.second];

            if (item.first == Op::OpenChild) {
                if (auto it = old_path->children.find(new_op.open_child.key);
                    it != old_path->children.end() && new_op.open_child.idx < it->second.size()) {
                    interpolate_branch(&it->second[new_op.open_child.idx],
                                       &new_path->children.find(new_op.open_child.key)->second[new_op.open_child.idx]);
                } else {
                    interpolate_branch(&new_path->children.find(new_op.open_child.key)->second[new_op.open_child.idx],
                                       &new_path->children.find(new_op.open_child.key)->second[new_op.open_child.idx]);
                }
                continue;
            }

            if (auto it = old_path->ops.find(item.first); it != old_path->ops.end()) {
                if (item.second < it->second.size()) {
                    Data& old_op = it->second[item.second];
                    switch (item.first) {
                        case Op::OpenChild:
                        case Op::CloseChild:
                        case Op::Marker:
                            break;

                        case Op::MatrixPush:
                            Matrix_Push(&gInterpolationMatrix);
                            break;

                        case Op::MatrixPop:
                            Matrix_Pop(&gInterpolationMatrix);
                            break;

                     // Unused on SF64
                     // case Op::MatrixPut:
                     //     interpolate_mtxf(&tmp_mtxf, &old_op.matrix_put.src, &new_op.matrix_put.src);
                     //     Matrix_Put(&tmp_mtxf);
                     //     break;

                        case Op::MatrixMult:
                            interpolate_mtxf(&tmp_mtxf, &old_op.matrix_mult.mf, &new_op.matrix_mult.mf);
                            Matrix_Mult(gInterpolationMatrix, (Matrix*) &tmp_mtxf, new_op.matrix_mult.mode);
                            break;

                        case Op::MatrixTranslate:
                            Matrix_Translate(gInterpolationMatrix, lerp(old_op.matrix_translate.x, new_op.matrix_translate.x),
                                             lerp(old_op.matrix_translate.y, new_op.matrix_translate.y),
                                             lerp(old_op.matrix_translate.z, new_op.matrix_translate.z),
                                             new_op.matrix_translate.mode);
                            break;

                        case Op::MatrixScale:
                            Matrix_Scale(gInterpolationMatrix, lerp(old_op.matrix_scale.x, new_op.matrix_scale.x),
                                         lerp(old_op.matrix_scale.y, new_op.matrix_scale.y),
                                         lerp(old_op.matrix_scale.z, new_op.matrix_scale.z), new_op.matrix_scale.mode);
                            break;

                        case Op::MatrixRotate1Coord: {
                            float v = interpolate_angle(old_op.matrix_rotate_1_coord.value,
                                                        new_op.matrix_rotate_1_coord.value);
                            u8 mode = new_op.matrix_rotate_1_coord.mode;
                            switch (new_op.matrix_rotate_1_coord.coord) {
                                case 0:
                                    Matrix_RotateX(gInterpolationMatrix, v, mode);
                                    break;

                                case 1:
                                    Matrix_RotateY(gInterpolationMatrix, v, mode);
                                    break;

                                case 2:
                                    Matrix_RotateZ(gInterpolationMatrix, v, mode);
                                    break;
                            }
                            break;
                        }
                        case Op::MatrixMultVec3fNoTranslate: {
                            interpolate_vecs(&tmp_vec3f, &old_op.matrix_vec_no_translate.src, &new_op.matrix_vec_no_translate.src);
                            interpolate_vecs(&tmp_vec3f2, &old_op.matrix_vec_no_translate.dest, &new_op.matrix_vec_no_translate.dest);
                            Matrix_MultVec3fNoTranslate(gInterpolationMatrix, &tmp_vec3f, &tmp_vec3f2);
                            break;
                        }
                        case Op::MatrixMultVec3f: {
                            interpolate_vecs(&tmp_vec3f, &old_op.matrix_vec_translate.src, &new_op.matrix_vec_translate.src);
                            interpolate_vecs(&tmp_vec3f2, &old_op.matrix_vec_translate.dest, &new_op.matrix_vec_translate.dest);
                            Matrix_MultVec3f(gInterpolationMatrix, &tmp_vec3f, &tmp_vec3f2);
                            break;
                        }

                        case Op::MatrixMtxFToMtx:
                            interpolate_mtxf(new_replacement(new_op.matrix_mtxf_to_mtx.dest),
                                             &old_op.matrix_mtxf_to_mtx.src, &new_op.matrix_mtxf_to_mtx.src);
                            break;

                        case Op::MatrixToMtx: {
                            //*new_replacement(new_op.matrix_to_mtx.dest) = *Matrix_GetCurrent();
                            if (old_op.matrix_to_mtx.has_adjusted && new_op.matrix_to_mtx.has_adjusted) {
                                interpolate_mtxf(&tmp_mtxf, &old_op.matrix_to_mtx.src, &new_op.matrix_to_mtx.src);
                                Matrix_MtxFMtxFMult(&actor_mtx, &tmp_mtxf,
                                                        new_replacement(new_op.matrix_to_mtx.dest));
                            } else {
                                interpolate_mtxf(new_replacement(new_op.matrix_to_mtx.dest), &old_op.matrix_to_mtx.src,
                                                 &new_op.matrix_to_mtx.src);
                            }
                            break;
                        }

                        case Op::MatrixRotateAxis: {
                            lerp_vec3f(&tmp_vec3f, &old_op.matrix_rotate_axis.axis, &new_op.matrix_rotate_axis.axis);
                            auto tmp = interpolate_angle(old_op.matrix_rotate_axis.angle, new_op.matrix_rotate_axis.angle);
                            Matrix_RotateAxis((Matrix*) &tmp_vec3f, tmp, 1.0f, 1.0f, 1.0f, new_op.matrix_rotate_axis.mode);
                            break;
                        }
                    }
                }
            }
        }
    }
};

} // anonymous namespace

unordered_map<Mtx*, MtxF> FrameInterpolation_Interpolate(float step) {
    InterpolateCtx ctx;
    ctx.step = step;
    ctx.w = 1.0f - step;
    ctx.interpolate_branch(&previous_recording.root_path, &current_recording.root_path);
    return ctx.mtx_replacements;
}

bool camera_interpolation = true;

void FrameInterpolation_ShouldInterpolateFrame(bool shouldInterpolate) {
    // camera_interpolation = shouldInterpolate;
    is_recording = shouldInterpolate;
}

void FrameInterpolation_StartRecord(void) {
    previous_recording = move(current_recording);
    current_recording = {};
    current_path.clear();
    current_path.push_back(&current_recording.root_path);
    if (!camera_interpolation) {
        // default to interpolating
        camera_interpolation = true;
        is_recording = false;
        return;
    }
    if (GameEngine::GetInterpolationFPS() != 20) {
        is_recording = true;
    }
}

void FrameInterpolation_StopRecord(void) {
    previous_camera_epoch = camera_epoch;
    is_recording = false;
}

void FrameInterpolation_RecordOpenChild(const void* a, int b) {
    if (!is_recording)
        return;
    label key = { a, b };
    auto& m = current_path.back()->children[key];
    append(Op::OpenChild).open_child = { key, m.size() };
    current_path.push_back(&m.emplace_back());
}

void FrameInterpolation_RecordCloseChild(void) {
    if (!is_recording)
        return;
    // append(Op::CloseChild);
    if (has_inv_actor_mtx && current_path.size() == inv_actor_mtx_path_index) {
        has_inv_actor_mtx = false;
    }
    current_path.pop_back();
}

void FrameInterpolation_DontInterpolateCamera(void) {
    camera_epoch = previous_camera_epoch + 1;
}

int FrameInterpolation_GetCameraEpoch(void) {
    return (int)camera_epoch;
}

void FrameInterpolation_RecordActorPosRotMatrix(void) {
    if (!is_recording)
        return;
    next_is_actor_pos_rot_matrix = true;
}

void FrameInterpolation_RecordMatrixPush(Matrix** matrix) {
    if (!is_recording)
        return;

    append(Op::MatrixPush).matrix_ptr = { matrix };
}

void FrameInterpolation_RecordMarker(const char* file, int line) {
    if (!is_recording)
        return;

    // append(Op::Marker).marker = { file, line };
}

void FrameInterpolation_RecordMatrixPop(Matrix** matrix) {
    if (!is_recording)
        return;
    append(Op::MatrixPop).matrix_ptr = { matrix };
}

void FrameInterpolation_RecordMatrixPut(MtxF* src) {
    if (!is_recording)
        return;
//    append(Op::MatrixPut).matrix_put = { matrix, *src };
}

void FrameInterpolation_RecordMatrixMult(Matrix* matrix, MtxF* mf, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MatrixMult).matrix_mult = { matrix, *mf, mode };
}

void FrameInterpolation_RecordMatrixTranslate(Matrix* matrix, f32 x, f32 y, f32 z, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MatrixTranslate).matrix_translate = { matrix, x, y, z, mode };
}

void FrameInterpolation_RecordMatrixScale(Matrix* matrix, f32 x, f32 y, f32 z, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MatrixScale).matrix_scale = { matrix, x, y, z, mode };
}

void FrameInterpolation_RecordMatrixMultVec3fNoTranslate(Matrix* matrix, Vec3f src, Vec3f dest){
    if (!is_recording)
        return;
    append(Op::MatrixMultVec3fNoTranslate).matrix_vec_no_translate = { matrix, src, dest };
}

void FrameInterpolation_RecordMatrixMultVec3f(Matrix* matrix, Vec3f src, Vec3f dest){
    if (!is_recording)
        return;
    append(Op::MatrixMultVec3f).matrix_vec_translate = { matrix, src, dest };
}

void FrameInterpolation_RecordMatrixRotate1Coord(Matrix* matrix, u32 coord, f32 value, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MatrixRotate1Coord).matrix_rotate_1_coord = { matrix, coord, value, mode };
}

void FrameInterpolation_RecordMatrixMtxFToMtx(MtxF* src, Mtx* dest) {
    if (!is_recording)
        return;
    append(Op::MatrixMtxFToMtx).matrix_mtxf_to_mtx = { *src, dest };
}

void FrameInterpolation_RecordMatrixToMtx(Mtx* dest, char* file, s32 line) {
    if (!is_recording)
        return;
    auto& d = append(Op::MatrixToMtx).matrix_to_mtx = { dest };
    if (has_inv_actor_mtx) {
        d.has_adjusted = true;
        Matrix_MtxFMtxFMult(&inv_actor_mtx, Matrix_GetCurrent(), &d.src);
    } else {
        d.src = *Matrix_GetCurrent();
    }
}

void FrameInterpolation_RecordMatrixRotateAxis(f32 angle, Vec3f* axis, u8 mode) {
    if (!is_recording)
        return;
    append(Op::MatrixRotateAxis).matrix_rotate_axis = { angle, *axis, mode };
}

void FrameInterpolation_RecordSkinMatrixMtxFToMtx(MtxF* src, Mtx* dest) {
    if (!is_recording)
        return;
    FrameInterpolation_RecordMatrixMtxFToMtx(src, dest);
}

// https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
static bool invert_matrix(const float m[16], float invOut[16]) {
    float inv[16], det;
    int i;

    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] +
             m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] -
             m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] +
             m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] -
              m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] -
             m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] +
             m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] -
             m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] +
              m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] +
             m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] -
             m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] +
              m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] -
              m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] -
             m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -
              m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0) {
        return false;
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++) {
        invOut[i] = inv[i] * det;
    }

    return true;
}