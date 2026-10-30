/* gb.x func_00f20518: matched by hand. */
#include "ovl.h"

/* gb.x func_00f20518: matched by hand (wgb round 37). The second store in the loop is written through a union view with a 4-byte prefix (v4.e[i].w[4]), so cse forms its address as (base + 4) + (i * 24 + 16) and reuses the i * 24 + 16 register, as the original does (sw v0,4(v1) after addu v1,v1,s0). */
typedef struct { s32 w[6]; } E47610;
typedef union { struct { u8 p0[0]; E47610 e[4]; } v0; struct { u8 p4[4]; E47610 e[4]; } v4; struct { u8 p8[8]; E47610 e[4]; } v8; struct { u8 p16[16]; E47610 e[4]; } v16; } W47610;
s32 func_001bb500(s32, s32);
extern W47610 *D_00F56DC0;
extern s32 D_00F56DC4;
extern s32 D_00F56DE8;
extern s32 D_00F74204;
extern s32 D_00F74214;
extern s32 D_00F74210;
extern s32 D_00F74218;
extern s32 D_00F74220;
extern s32 D_00F74224;
extern s32 D_00F7421C;
extern s32 D_00F56DE0;
extern s32 D_00F56DE4;

static inline void alloc47610(s32 *p, s32 size, s32 align) {
    *p = func_001bb500(size, align);
}

void func_00f20518(void) {
    s32 i;

    alloc47610((s32 *)&D_00F56DC0, 9216, 16);
    alloc47610(&D_00F56DC4, 0x13008, 16);
    for (i = 0; i < 2; i++) {
        D_00F56DC0->v0.e[i].w[4] = func_001bb500(0xC0000, 128);
        D_00F56DC0->v4.e[i].w[4] = func_001bb500(0x4E000, 16);
        D_00F56DC0->v8.e[i].w[4] = func_001bb500(0xA000, 16);
        D_00F56DC0->v16.e[i].w[3] = func_001bb500(0xA000, 16);
        D_00F56DC0->v8.e[i + 1].w[0] = func_001bb500(0xA000, 16);
    }
    alloc47610(&D_00F56DE8, 0xC8000, 128);
    alloc47610(&D_00F74204, 0xC0000, 128);
    alloc47610(&D_00F74214, 0x90000, 128);
    alloc47610(&D_00F74210, 0x440000, 128);
    alloc47610(&D_00F74218, 0x10000, 128);
    alloc47610(&D_00F74220, 0x40000, 128);
    alloc47610(&D_00F74224, 0x100000, 128);
    alloc47610(&D_00F7421C, 0x40000, 128);
    D_00F56DE0 = func_001bb500(16384, 16);
    D_00F56DE4 = func_001bb500(4096, 128);
}
