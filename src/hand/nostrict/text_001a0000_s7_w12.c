#include "common.h"
typedef f32 PppMtx[4][4] __attribute__((aligned(16)));
typedef f32 PppVec4[4] __attribute__((aligned(16)));
typedef struct {
    u8 pad[0x10];
    PppMtx m;
    PppMtx m2;
    s32 unk90;
    s32 unk94;
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
extern PppMtx D_00615EB0; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern PppMtx D_00615FC0;
extern PppMtx D_00616000;
extern PppMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
void func_002672f8(f32 *, PppMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002678b8(PppMtx, PppMtx, f32 *);
void sceVu0CopyMatrix(PppMtx, PppMtx);
void sceVu0UnitMatrix(PppMtx);
void sceVu0MulMatrix(PppMtx, PppMtx, PppMtx);
typedef struct {
    u8 pad0[0x26];
    u8 kind;
    u8 pad27[0x105 - 0x27];
    u8 b105;
} O09d0;
typedef struct {
    PppMtx m;
    u8 pad40[8];
    u64 rot;
    s32 rz;
    u8 pad54[0x6C - 0x54];
    f32 scale[3];
} K09d0;
/* rodata */
void func_001a09d0(PppMtx base, PppMtx m, O09d0 *o, K09d0 *k, PppMtx parent, PppMtx out, u8 flag) {
    PppVec4 tmp;
    PppMtx t;
    PppMtx rm;
    PppVec4 r;
    s32 i;
    f32 *sc;
    if (o->b105) {
        sceVu0CopyMatrix(m, k->m);
    } else {
        sceVu0UnitMatrix(m);
        func_002675a8(m[3], k->m[3]);
    }
    if (k->rot != 0 || k->rz != 0) {
        for (i = 0; i < 3; i++) r[i] = (f32)((s32 *)&k->rot)[i] * 3.1415927f * (1.0f / 32768.0f);
        sceVu0UnitMatrix(rm);
        func_002678b8(rm, rm, r);
        sceVu0MulMatrix(m, m, rm);
    }
    sc = k->scale;
    for (i = 0; i < 3; i++) func_00267560(m[i], m[i], *sc++);
    switch (o->kind) {
    case 0: case 2: case 4: case 6: case 8:
    default:
        if (parent == 0) {
            func_002675a8(tmp, m[3]);
            sceVu0MulMatrix(m, D_00615FC0, m);
            func_002672f8(m[3], base, tmp);
            if (flag) sceVu0CopyMatrix(out, m);
            sceVu0MulMatrix(m, D_00616040, m);
        } else {
            sceVu0MulMatrix(t, parent, D_00615E68->m);
            sceVu0MulMatrix(t, D_00615EB0, t);
            func_002675a8(tmp, m[3]);
            sceVu0MulMatrix(m, D_00615FC0, m);
            func_002672f8(m[3], t, tmp);
            if (flag) sceVu0CopyMatrix(out, m);
            sceVu0MulMatrix(m, D_00616040, m);
        }
        break;
    case 1: case 3: case 5: case 7: case 9:
        func_002672f8(tmp, base, m[3]);
        sceVu0MulMatrix(m, D_00616000, m);
        func_002675a8(m[3], tmp);
        if (flag) sceVu0CopyMatrix(out, m);
        sceVu0MulMatrix(m, D_00616040, m);
        break;
    }
}

