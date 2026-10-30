/* wm.x func_00f59930: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[0x94]; s32 f94; } GbWorld;
extern GbWorld *D_00F9B540;
extern s32 D_00F9B518;
extern s32 D_00FA5DA0;
extern s32 D_0108CED0[];
extern u64 D_0108CF50;
s32 func_00f645e8(s32);
s32 func_00f645f0(s32, s32);
void func_00f64610(s32 *, s32, s32);
u64 *func_00f646c0(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, u64, s32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
u64 *func_00f66b78(u64 *);
void func_00f66b90(u64 *);
void func_00f66f78(s32, u64 *);
void func_00f670c8(u64 *);

void func_00f59930(u64 **pp, s32 id) {
    s32 v[4];
    u64 *p;
    s32 i;
    s32 k;
    s32 tag;
    s32 n = func_00f645e8(id);
    for (i = 0; i < n; i++) {
        k = func_00f645f0(i, id);
        func_00f64610(v, i, id);
        if (D_0108CED0[k] == 0)
            continue;
        if (D_00F9B540->f94 == 0 && k == 7)
            continue;
        if (k != 0)
            continue;
        p = func_00f646c0(*pp, v[0], v[1], 0, i, 0x3200, 0x200, 0x200, 19, 0x3600, D_0108CF50, id);
        if (p == NULL)
            continue;
        tag = i + 10800;
        if (D_00F9B518 != 0 || D_00FA5DA0 != 0) {
            func_00f670c8(*pp);
            *pp = p;
        } else {
            func_00f66f78(tag, *pp);
            *pp = p;
        }
    }
    if (D_00F9B518 != 0 || D_00FA5DA0 != 0) {
        p = func_00f66b78(func_00f66ac8(*pp));
        p[0] = 0x740000007000;
        p[1] = 0x18;
        p += 2;
        p[0] = 0x30000;
        p[1] = 0x47;
        p += 2;
        func_00f66b90(p);
        func_00f670c8(func_00f66ae0(p));
        *pp = p;
    }
    D_00FA5DA0 = D_00F9B518;
}
