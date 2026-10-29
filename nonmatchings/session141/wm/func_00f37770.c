/* score 24 (1176 bytes, same size). Camera/object orient keyframe: rot from degrees (constant needs 0.017453291f; gcc 2.96 rounds 0.01745329f to ...fa33), type switch 2/3/9/4, acos(dot/PlatSqrtf(|d|^2*|u|^2)) axis-angle, slerp loop. `default: case 0:` in both mode switches gives the orig slti tree (96 -> 24). Left: s5/s6 swap between n and &rot. Tried statement/decl orders, r = rot pointer, loop forms. Round 26 wwm2. */
#include "platform/math.h"
typedef struct { u8 pad[20]; s32 type; s32 dur; s32 rx; s32 ry; s32 rz; } Key;
typedef struct { f32 m[4][4]; f32 v40[4]; f32 v50[4]; f32 m60[8][4]; s32 xE0; s32 padE4[6]; s32 xFC; } Obj;
extern f32 D_002BBDEC;
void func_001be9f0(f32 *);
void func_001becb8(f32 (*)[4], f32 *, s32);
void func_001bf098(f32 (*)[4], f32 (*)[4]);
void func_001bf2b0(f32 *, f32 *, f32 *);
void func_001bf3e8(f32 (*)[4], f32 *);
void func_001bf698(f32 *, f32 *, f32);
void func_001bf710(f32 *, f32 *, f32 *, f32);
void func_001bf888(f32 *, f32 (*)[4]);
void func_001bfac8(void);
void func_00f2c818(f32 (*)[4]);
f32 acosf(f32);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0RotMatrix(f32 (*)[4], f32 (*)[4], f32 *);
void sceVu0Normalize(f32 *, f32 *);
void sceVu0OuterProduct(f32 *, f32 *, f32 *);
f32 sceVu0InnerProduct(f32 *, f32 *);
void sceVu0CopyVector(f32 *, f32 *);

void func_00f37770(s32 mode, Obj *o, Key *k, s32 anim)
{
    f32 dir[4];
    f32 axis[4];
    f32 up[4];
    f32 rot[4];
    f32 m[4][4];
    f32 q[4];
    f32 q0[4];
    f32 q1[4];
    s32 type;
    s32 n;
    s32 i;

    type = k->type;
    n = k->dur / D_002BBDEC;
    rot[0] = k->rx * 0.017453291f;
    rot[1] = k->ry * 0.017453291f;
    rot[2] = k->rz * 0.017453291f;
    rot[3] = 1.0f;
    func_001be9f0(rot);
    func_001bf888(q0, o->m);
    switch (type) {
    case 2:
        sceVu0CopyMatrix(m, o->m);
        break;
    case 3:
        func_00f2c818(m);
        dir[3] = 1.0f;
        dir[0] = m[3][0] - o->m[3][0];
        dir[1] = m[3][1] - o->m[3][1];
        dir[2] = m[3][2] - o->m[3][2];
        sceVu0Normalize(dir, dir);
        up[0] = o->m[2][0];
        up[1] = o->m[2][1];
        up[2] = o->m[2][2];
        up[3] = 1.0f;
        sceVu0OuterProduct(axis, up, dir);
        sceVu0Normalize(axis, axis);
        func_001bf698(q, axis, acosf(sceVu0InnerProduct(up, dir) /
                                     PlatSqrtf((dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]) *
                                               (up[0] * up[0] + up[1] * up[1] + up[2] * up[2]))));
        func_001bf2b0(q, q, q0);
        func_001bf3e8(m, q);
        break;
    case 9:
        func_00f2c818(m);
        dir[3] = 1.0f;
        dir[0] = m[3][0] - o->m[3][0];
        dir[1] = m[3][1] - o->m[3][1];
        dir[2] = m[3][2] - o->m[3][2];
        sceVu0Normalize(dir, dir);
        func_001becb8(m, dir, 0);
        break;
    case 4:
        sceVu0UnitMatrix(m);
        break;
    }
    sceVu0RotMatrix(m, m, rot);
    if (anim != 0 && n > 0) {
        i = 0;
        func_001bf888(q1, m);
        while (i < n && o->xFC != 0) {
            if (o->xE0 == 0) {
                return;
            }
            func_001bf710(q, q0, q1, (f32)i++ / (f32)n);
            func_001bf3e8(m, q);
            switch (mode) {
            default:
            case 0:
                func_001bf098(o->m60, m);
                sceVu0CopyVector(o->v40, m[2]);
                break;
            case 1:
                func_001bf098(o->m60, m);
                break;
            case 2:
                sceVu0CopyVector(o->v40, m[2]);
                break;
            }
            func_001bfac8();
        }
        func_001bf3e8(m, q1);
    }
    switch (mode) {
    default:
    case 0:
        func_001bf098(o->m60, m);
        sceVu0CopyVector(o->v40, m[2]);
        break;
    case 1:
        func_001bf098(o->m60, m);
        break;
    case 2:
        sceVu0CopyVector(o->v40, m[2]);
        break;
    }
}
