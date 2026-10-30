/* gb.x func_00f32838: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[0x94]; s32 f94; } GbWorld;
extern GbWorld *D_00F56DC0;
extern s32 D_00F56D98;
extern s32 D_00F61620;
extern s32 D_00F80710[];
extern u64 D_00F80790;
s32 func_00f3d4f0(s32);
s32 func_00f3d4f8(s32, s32);
void func_00f3d518(s32 *, s32, s32);
u64 *func_00f3d5c8(u64 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, u64, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);
void func_00f3ffd0(u64 *);

void func_00f32838(u64 **pp, s32 id) {
    s32 v[4];
    u64 *p;
    s32 i;
    s32 k;
    s32 tag;
    s32 n = func_00f3d4f0(id);
    for (i = 0; i < n; i++) {
        k = func_00f3d4f8(i, id);
        func_00f3d518(v, i, id);
        if (D_00F80710[k] == 0)
            continue;
        if (D_00F56DC0->f94 == 0 && k == 7)
            continue;
        if (k != 0)
            continue;
        p = func_00f3d5c8(*pp, v[0], v[1], 0, i, 0x3200, 0x200, 0x200, 19, 0x3600, D_00F80790, id);
        if (p == NULL)
            continue;
        tag = i + 10800;
        if (D_00F56D98 != 0 || D_00F61620 != 0) {
            func_00f3ffd0(*pp);
            *pp = p;
        } else {
            func_00f3fe80(tag, *pp);
            *pp = p;
        }
    }
    if (D_00F56D98 != 0 || D_00F61620 != 0) {
        p = func_00f3fa80(func_00f3f9d0(*pp));
        p[0] = 0x740000007000;
        p[1] = 0x18;
        p += 2;
        p[0] = 0x30000;
        p[1] = 0x47;
        p += 2;
        func_00f3fa98(p);
        func_00f3ffd0(func_00f3f9e8(p));
        *pp = p;
    }
    D_00F61620 = D_00F56D98;
}
