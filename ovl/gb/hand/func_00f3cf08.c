/* gb.x func_00f3cf08: matched by hand. */
#include "ovl.h"

u64 *func_001f0718(u64 *, s32, s32, s32, s32, s32, s32);
void func_001bb558(void);
void func_001efaf0(void);
u64 *func_00f3f9d0(u64 *);
s32 func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);
void func_00f3fe80(s32, s32);
extern u64 **D_00F61F58;

void func_00f3cf08(s32 a0, s32 a1, s32 a2, s32 a3) {
    u64 *p = *D_00F61F58;

    func_001bb558();
    p = func_00f3fa80(func_00f3f9d0(p));
    p[0] = (u64)(0x700 << 4) | ((u64)(0x740 << 4) << 32);
    p[1] = 0x18;
    p += 2;
    func_00f3fa98(p);
    p = func_001f0718(p, 1, 0x80808080, a0, a1, a2, a3);
    func_00f3fe80(0x9C40, func_00f3f9e8(p));
    *D_00F61F58 = p;
    func_001efaf0();
}
