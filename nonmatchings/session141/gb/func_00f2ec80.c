/* 13 words / score 27: sibling of the matched func_00f2f440 (same recipe: scalar ids, precomputed locals, i declared last). Left: two s-reg pairs swapped (x1/x0 in s4/s3, y3/x2 in s7/s6). Tried hill-climbing the statement order, separate temporaries, decl orders, and a 10-minute permuter run (best was unnatural). */
#include "ovl.h"

typedef struct { u8 pad[0x4C]; u16 kind; u8 pad4e[0x84 - 0x4E]; s16 id; } GbState;
extern GbState *D_00F56DC0;
extern u8 D_00F56DC8[];
void func_001bfac8(void);
s32 func_00f23928(s32);
s32 func_00f23a00(s32);
void func_00f2e578(void *);
void func_00f2e660(void *, s32, s32, s32, s32);
void func_00f2e788(void *, s32);
void func_00f2e808(void *);

void func_00f2ec80(s32 n) {
    s32 prev, cur, next, next2;
    s32 t;
    s32 y0, y1, y2, y3, x0, x1, x2, x3, h0, h1, h2, h3;
    s32 i;
    cur = D_00F56DC0->id;
    next = func_00f23928(cur);
    prev = func_00f23a00(cur);
    next2 = func_00f23928(next);
    for (i = 0; i < n; i++) {
        func_00f2e578(D_00F56DC8);
        h0 = (5 * (n - i) << 4) / n;
        t = 0x30 * i / n;
        h1 = 0x80 - t;
        h2 = t + 0x50;
        h3 = (5 * i << 4) / n;
        t = 0x110 * (n - i) / n;
        x0 = t - 0x2C0;
        x3 = t + 0x1B0;
        x1 = -0x1B0 * i / n;
        t = (5 * (n - i) << 5) / n;
        y0 = t + 0xC0;
        y1 = t + 0x160;
        t = (5 * i << 5) / n;
        y2 = t + 0x160;
        y3 = t + 0xC0;
        x2 = 0x1B0 * (n - i) / n;
        func_00f2e660(D_00F56DC8, prev, x0, y0, h0);
        func_00f2e660(D_00F56DC8, cur, x1, y1, h1);
        func_00f2e660(D_00F56DC8, next, x2, y2, h2);
        func_00f2e660(D_00F56DC8, next2, x3, y3, h3);
        func_00f2e788(D_00F56DC8, D_00F56DC0->kind - 1);
        func_00f2e808(D_00F56DC8);
        func_001bfac8();
    }
}
