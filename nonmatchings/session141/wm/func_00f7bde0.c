/* 45 words left (score 66): frame and temporaries right (V4 aligned(16) struct copies through ld/sd); FP register numbering and the load order of D_00FB5EBx / D_00FB5C3x differ. */
#include "ovl.h"

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;

extern f32 D_00FB5C44;
extern f32 D_00FB5EB0, D_00FB5EB4, D_00FB5EB8, D_00FB5EBC;
extern f32 D_00FB5C30, D_00FB5C34, D_00FB5C3C, D_00FB5C40;
extern OvlVec D_00FB5BF0, D_00FB5C00, D_00FB5C10, D_00FB5C20;
extern OvlMtx D_0108F6F0;
f32 tanf(f32);
void func_00f7bd10(OvlMtx, OvlVec, OvlVec, OvlVec, OvlVec);

static inline V4 mk(f32 x, f32 y, f32 z, f32 w) {
    V4 v;
    v.x = x;
    v.y = y;
    v.w = w;
    v.z = z;
    return v;
}

void func_00f7bde0(void) {
    OvlMtx vs;
    OvlMtx m80;
    OvlMtx world;
    OvlMtx view;
    V4 rot;
    V4 tr;
    V4 r;
    OvlMtx m;
    f32 ang;
    f32 scrz;
    f32 one;

    ang = D_00FB5C44 * 3.1415f / 180.0f;
    tr.x = D_00FB5EB0;
    tr.y = D_00FB5EB4;
    tr.w = D_00FB5EBC;
    tr.z = D_00FB5EB8;
    rot = tr;
    r.x = D_00FB5C30;
    r.y = D_00FB5C34;
    r.z = D_00FB5C3C;
    r.w = D_00FB5C40;
    tr = r;
    scrz = 256.0f / tanf(ang * 0.5f);
    one = 1.0f;
    PlatVu0UnitMatrix(m);
    PlatVu0RotMatrix(m, m, &rot);
    PlatVu0TransMatrix(world, m, &tr);
    func_00f7bd10(view, D_00FB5C20, D_00FB5BF0, D_00FB5C00, D_00FB5C10);
    PlatVu0ViewScreenMatrix(m80, scrz, one, one, 2048.0f, 2048.0f, one, 16777215.0f, one, 65536.0f);
    PlatVu0MulMatrix(vs, m80, view);
    PlatVu0MulMatrix(D_0108F6F0, vs, world);
}
