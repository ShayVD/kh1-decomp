/* wm.x func_00f57e78: matched by hand. */
#include "ovl.h"

/* gb.x func_00f57e78: matched by hand (session 141). The x index is its own local, `k = q * 4 + 8`, so gcse shares it between the d == 0 / d == 1 branches unfolded. */
typedef struct {
    u8 pad0[0x48];
    u8 loc[0x16];
    u16 f5e;
    u16 f60;
    u16 f62;
    u8 pad64[0x10D8 - 0x64];
    s32 ang;
} GbWorld;
extern GbWorld *D_00F9B540;
extern s32 D_00F9B544;
extern s8 D_00F9B528[];
extern u8 D_00FA5D10[];
s32 func_001c00e8(s32, void *, kh1_u128);
void func_001c0078(s32);
void func_00f55310(void);
f32 func_001befc8(s32, void *);
void func_00f55630(f32 *);
void func_00f4b338(s32, s32);
void func_001bfac8(void);
void func_001bbf88(void *, s32, s32);
u16 func_001bbdf0(void *);

void func_00f57e78(s32 d) {
    f32 v[3];
    s32 task;
    s32 i;
    s32 q;
    s32 k;
    s32 x = 0;
    s32 z = 0;
    s32 y;
    f32 fx, fy, fz, t;
    task = func_001c00e8(-1, func_00f55310, KH1_Q(0));
    D_00F9B540->f60 = D_00F9B540->f5e;
    q = D_00F9B540->ang / 1024;
    k = q * 4 + 8;
    if (d == 0) {
        x = D_00F9B528[k];
        z = D_00F9B528[q * 4 + 10];
    }
    if (d == 1) {
        x = -D_00F9B528[k];
        z = -D_00F9B528[q * 4 + 10];
    }
    y = (d == 2) ? -1 : 0;
    if (d == 3)
        y = 1;
    if (x | y | z) {
        fy = y;
        fx = x;
        fz = z;
        for (i = 0; i < 15; i++) {
            t = func_001befc8(i, D_00FA5D10);
            v[0] = fx * t * 3.1415927f / 180.0f;
            v[1] = fy * t * 3.1415927f / 180.0f;
            v[2] = fz * t * 3.1415927f / 180.0f;
            func_00f55630(v);
            D_00F9B540->f60 = D_00F9B540->f5e;
            func_00f4b338(D_00F9B544, 0);
            func_001bfac8();
        }
        if (x != 0)
            func_001bbf88(D_00F9B540->loc, 0, -x);
        if (z != 0)
            func_001bbf88(D_00F9B540->loc, 2, -z);
        if (d == 2)
            func_001bbf88(D_00F9B540->loc, 1, 1);
        if (d == 3)
            func_001bbf88(D_00F9B540->loc, 1, -1);
        func_00f55630(0);
    }
    D_00F9B540->f62 = func_001bbdf0(D_00F9B540->loc);
    D_00F9B540->f60 = D_00F9B540->f5e;
    func_00f4b338(D_00F9B544, 0);
    func_001c0078(task);
}
