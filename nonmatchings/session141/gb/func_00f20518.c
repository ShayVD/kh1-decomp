/* 72 words / score 13 (492 vs 496 bytes). An inline alloc(&global, size, align) helper gives the original's precomputed global addresses in s-registers; the loop fields stay plain assignments. Left: loop address givs. The original forms buf[i].d as s2+base+28 and buf[i].e as base+(s2+24)+8, then does move s2,a0. Tried do-while, buf[i++].e, x[] array fields, a 2D array, and pointer arithmetic. Round 16 (wwm1): looked at, not changed. The target forms .d as s2 + 28 (not s0 + 12) and .e through the incremented biv (s2 + 24, then move s2,a0), so d and e are reached through different expressions from a, b and c. */
#include "ovl.h"

typedef struct { void *a, *b, *c, *d, *e, *f; } GbBuf;
typedef struct { u8 pad[16]; GbBuf buf[2]; } GbMem;
void *func_001bb500(s32, s32);
extern GbMem *D_00F56DC0;
extern void *D_00F56DC4;
extern void *D_00F56DE0;
extern void *D_00F56DE4;
extern void *D_00F56DE8;
extern void *D_00F74204;
extern void *D_00F74210;
extern void *D_00F74214;
extern void *D_00F74218;
extern void *D_00F7421C;
extern void *D_00F74220;
extern void *D_00F74224;

static inline void alloc(void **p, s32 size, s32 align) {
    *p = func_001bb500(size, align);
}

void func_00f20518(void) {
    s32 i;
    alloc((void **)&D_00F56DC0, 0x2400, 0x10);
    alloc((void **)&D_00F56DC4, 0x13008, 0x10);
    for (i = 0; i < 2; i++) {
        D_00F56DC0->buf[i].a = func_001bb500(0xC0000, 0x80);
        D_00F56DC0->buf[i].b = func_001bb500(0x4E000, 0x10);
        D_00F56DC0->buf[i].c = func_001bb500(0xA000, 0x10);
        D_00F56DC0->buf[i].d = func_001bb500(0xA000, 0x10);
        D_00F56DC0->buf[i].e = func_001bb500(0xA000, 0x10);
    }
    alloc((void **)&D_00F56DE8, 0xC8000, 0x80);
    alloc((void **)&D_00F74204, 0xC0000, 0x80);
    alloc((void **)&D_00F74214, 0x90000, 0x80);
    alloc((void **)&D_00F74210, 0x440000, 0x80);
    alloc((void **)&D_00F74218, 0x10000, 0x80);
    alloc((void **)&D_00F74220, 0x40000, 0x80);
    alloc((void **)&D_00F74224, 0x100000, 0x80);
    alloc((void **)&D_00F7421C, 0x40000, 0x80);
    D_00F56DE0 = func_001bb500(0x4000, 0x10);
    D_00F56DE4 = func_001bb500(0x1000, 0x80);
}
