/* wm.x func_00f5fcf0: matched by hand. */
#include "ovl.h"

u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void sceVu0RotTransPers(s32 *, OvlMtx, f32 *, s32);

#define XYZ(v) ((s64)(v)[0] | ((s64)(v)[1] << 16) | ((s64)0x8000 << 17))

u64 *func_00f5fcf0(f32 *a, f32 *b, u64 col2, u64 col1, OvlMtx m, u64 *p) {
    OvlVec pt;
    s32 v[6][4];
    s32 i;
    pt[3] = 1.0f;
    pt[0] = (b[0] - a[0]) * 0.5f + a[0];
    pt[1] = a[1];
    pt[2] = (b[2] - a[2]) * 0.5f + a[2];
    sceVu0RotTransPers(v[0], m, pt, 0);
    pt[1] = b[1];
    sceVu0RotTransPers(v[1], m, pt, 0);
    pt[1] = (b[1] - a[1]) * 0.5f + a[1];
    pt[0] = a[0];
    sceVu0RotTransPers(v[2], m, pt, 0);
    pt[0] = b[0];
    sceVu0RotTransPers(v[3], m, pt, 0);
    pt[0] = (b[0] - a[0]) * 0.5f + a[0];
    pt[2] = a[2];
    sceVu0RotTransPers(v[4], m, pt, 0);
    pt[2] = b[2];
    sceVu0RotTransPers(v[5], m, pt, 0);

    p = func_00f66b78(p);
    p[0] = 197;
    p[1] = 0;
    p += 2;
    p[0] = col1;
    p[1] = 1;
    p += 2;
    p[0] = XYZ(v[0]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[2]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[4]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[3]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[5]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[2]);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);

    p = func_00f66b78(p);
    p[0] = 197;
    p[1] = 0;
    p += 2;
    p[0] = col1;
    p[1] = 1;
    p += 2;
    p[0] = XYZ(v[1]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[2]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[4]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[3]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[5]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[2]);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);

    for (i = 0; i < 4; i++) {
        p = func_00f66b78(p);
        p[0] = 194;
        p[1] = 0;
        p += 2;
        p[0] = col2;
        p[1] = 1;
        p += 2;
        p[0] = XYZ(v[0]);
        p[1] = 5;
        p += 2;
        p[0] = XYZ(v[i + 2]);
        p[1] = 5;
        p += 2;
        p[0] = XYZ(v[1]);
        p[1] = 5;
        p += 2;
        func_00f66b90(p);
    }

    p = func_00f66b78(p);
    p[0] = 194;
    p[1] = 0;
    p += 2;
    p[0] = col2;
    p[1] = 1;
    p += 2;
    p[0] = XYZ(v[2]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[4]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[3]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[5]);
    p[1] = 5;
    p += 2;
    p[0] = XYZ(v[2]);
    p[1] = 5;
    p += 2;
    func_00f66b90(p);
    return p;
}
