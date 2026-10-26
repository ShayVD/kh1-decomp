/* wm.x func_00f21128: matched by hand. */
#include "ovl.h"

typedef struct { s32 a0; s32 a4; s32 a8; u8 r, g, b, a; u8 c10, c11, c12, c13; u8 pad[0x24]; s64 t1; s64 t2; } St;
void func_001621e0(s32, OvlMtx, St *, s32);
void func_001655e0(OvlMtx, s32, s32, f32);
void *memset(void *, s32, u32);
extern OvlMtx D_00F85180;
extern OvlMtx D_00FBA990;

void func_00f21128(s32 arg0, OvlMtx arg1, OvlMtx arg2, s32 arg3, s32 *arg4, s32 arg5, f32 f) {
    St s;
    OvlMtx m;
    OvlMtx m2;
    memset(&s, 0, sizeof(St));
    PlatVu0UnitMatrix(m);
    PlatVu0MulMatrix(D_00FBA990, arg2, m);
    PlatVu0MulMatrix(arg1, arg1, m);
    PlatVu0CopyMatrix(m2, D_00F85180);
    func_001655e0(arg1, arg3, arg4[arg5], f);
    s.a8 = arg0 + 1;
    s.r = 0x80;
    s.g = 0x80;
    s.b = 0x80;
    s.a = 0x80;
    s.c13 = 0xFF;
    s.a4 = 0;
    s.t1 = 0x31000070;
    s.t2 = 0x800D0;
    func_001621e0(arg3, m2, &s, 0);
}
