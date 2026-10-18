#include "common.h"
/* func_001edfb8: port of sibling func_001f86e0 (src/hand/text_001f0000_s6_17.c). */
typedef struct { u64 a, b; } Q;
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
Q *func_00122048(s32, s32);
s32 sceGsSyncPath(s32, u16);
void func_001220b8(void *);
Q *func_0011fb38(s32 reg, u64 val, Q *p);

void func_001edfb8(s32 x0, s32 y0, s32 w, s32 h) {
    s32 x1, y1;
    Q *buf, *e, *p;
    void *ub;
    x1 = x0 + w - 1;
    y1 = y0 + h - 1;
    if (x0 < 512 && y0 < 384 && x1 >= 0 && y1 >= 0) {
        if (x1 >= 512) x1 = 511;
        if (x0 < 0) x0 = 0;
        if (y0 < 0) y0 = 0;
        if (y1 >= 384) y1 = 383;

        p = func_00122048(1024, 128);
        buf = p;
        p = buf + 1;
        ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
        p->a = 0x1000000000008001;
        p->b = 14;

        e = func_0011fb38(64, (u64)x0 | ((u64)x1 << 16) | ((u64)y0 << 32) | ((u64)y1 << 48), p + 1);
        buf->a = ((e - buf) - 1) | 0x70000000;
        func_00266f38(func_00266c08(2), ub);
        sceGsSyncPath(0, 0);
        func_001220b8(buf);
    }
}
