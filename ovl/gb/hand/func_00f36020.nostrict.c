/* gb.x func_00f36020: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[6]; u16 w; u8 pad8[2]; u16 h; } GbDims;
typedef struct {
    u8 pad0[0x58];
    u64 lo : 32;
    u16 px : 4;
    u16 py : 4;
    u16 pz : 4;
    u16 pr : 4;
    u16 pad5e;
    u8 pad60[0xA0 - 0x60];
    GbDims dims;
} GbWorld;
typedef struct { u8 pad0[0x3C]; f32 f3c; } GbObj;
extern GbWorld *D_00F56DC0;
extern f32 D_00F61640;
extern s32 D_00F616BC;
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, u64 *);
void func_00f3fef0(s32, u64 *);
void func_00f3feb8(s32, u64 *);
s32 func_00f23088(void);
s32 func_00f23230(s32, u64 **, GbObj *, s32, s32, GbDims *);

s32 func_00f36020(s32 flag, s32 id, u64 **pp, s32 x, s32 y, GbObj *obj, GbDims *d) {
    u64 *p;
    u64 *q;
    u64 *b;
    if (d == NULL)
        d = &D_00F56DC0->dims;
    b = func_00f3f9d0(*pp);
    *pp = b;
    b[0] = 0x100000000000800B;
    b[1] = 14;
    q = b + 2;
    q[0] = 0xFFFFFF000800D0;
    q[1] = 76;
    q = b + 4;
    q[0] = 0;
    q[1] = 24;
    q = b + 6;
    q[0] = 0x017F000001FF0000;
    q[1] = 64;
    q = b + 8;
    q[0] = 0x30003;
    q[1] = 71;
    q = b + 10;
    q[0] = 6;
    q[1] = 0;
    q = b + 12;
    q[0] = 0x3F80000000000000;
    q[1] = 1;
    q = b + 14;
    q[0] = 0;
    q[1] = 5;
    q = b + 16;
    q[0] = 0x18002000;
    q[1] = 5;
    q = b + 18;
    q[0] = 0x800D0;
    q[1] = 76;
    q = b + 20;
    q[0] = 0x70000;
    q[1] = 71;
    q = b + 22;
    q[1] = 24;
    q[0] = ((u64)(y << 4) << 32) | (x << 4);
    q = b + 24;
    *pp = q;
    if (func_00f23088() == 0)
        func_00f3fe80(id, func_00f3f9e8(*pp));
    else
        func_00f3fef0(0, func_00f3f9e8(*pp));
    obj->f3c = D_00F61640;
    id = func_00f23230(id + 1, pp, obj, 128, D_00F56DC0->py, d) + 1;
    p = func_00f3fa80(func_00f3f9d0(*pp));
    p[0] = 0x740000007000;
    p[1] = 24;
    p += 2;
    p[0] = 0x5000D;
    p[1] = 71;
    p += 2;
    p[0] = 96;
    p[1] = 20;
    p += 2;
    func_00f3fa98(p);
    if (func_00f23088() == 0)
        func_00f3fe80(id, func_00f3f9e8(p));
    else
        func_00f3fef0(10, func_00f3f9e8(p));
    *pp = p;
    id++;
    if (flag && D_00F616BC == 0) {
        p = func_00f3fa80(func_00f3f9d0(p));
        p[0] = 68;
        p[1] = 66;
        p += 2;
        p[0] = 0x740000007000;
        p[1] = 24;
        p += 2;
        p[0] = 0x5000D;
        p[1] = 71;
        p += 2;
        p[0] = 96;
        p[1] = 20;
        p += 2;
        func_00f3fa98(p);
        func_00f3feb8(0, func_00f3f9e8(p));
        *pp = p;
    }
    return id;
}
