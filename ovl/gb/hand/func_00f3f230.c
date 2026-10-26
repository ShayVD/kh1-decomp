/* gb.x func_00f3f230: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[16]; s32 a, b, c, d; u64 e[8]; } P66;
void func_00f3f938(s32, P66 *, s32);

void func_00f3f230(s32 arg0) {
    P66 p;
    p.a = 0x8004;
    p.b = 0x10000000;
    p.c = 14;
    p.d = 0;
    p.e[0] = 0x44;
    p.e[1] = 0x42;
    p.e[2] = 0x70000;
    p.e[3] = 0x47;
    p.e[4] = 0;
    p.e[5] = 8;
    p.e[6] = 0x61;
    p.e[7] = 0x14;
    func_00f3f938(5, &p, arg0);
}
