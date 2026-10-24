/* Hand-matched functions near 0x145000-0x14C600 (worker 8). */
#include "common.h"
#include "data/bss_0053.h"
#include "data/bss_0054.h"
#include "vm/script_vm.h"

#include "data/types/text_00140000_h8.h"
extern u8 D_00533BA0[];
typedef struct { u8 pad[0xc]; f32 xc; } W8Fc;
typedef struct { u8 pad[0x8]; f32 *x8; W8Fc *xc; u8 pad10[0x14 - 0x10]; u32 x14; u8 pad18[0x30 - 0x18]; s32 x30; u8 pad34[0x38 - 0x34]; s32 x38; } W8O60;
void func_00176310(W8O60 *);
extern s32 D_00350D10;
typedef struct { u8 pad[0x28]; s32 x28; } W8Z5c;
typedef struct { u8 pad[8]; s32 x8; u8 padc[0x5c - 0xc]; W8Z5c *x5c; } W8Z;
s32 func_00176578(s32, s32, s32, s32);
s32 func_00147ed8(s32, s32, s32, s32);
typedef struct { u8 pad[0x100]; union { f32 f; u64 x; struct { u64 lo:32; u64 b32:1; u64 r:31; } b; } x100; } W8A148;
typedef struct { u8 pad[0x148]; W8A148 *x148; u8 pad14c[0x1cc - 0x14c]; u32 x1cc; u8 pad1d0[0x3c0 - 0x1d0]; u8 x3c0[0x14]; f32 x3d4; } W8Act;
void func_00267560(void *, void *, f32);
void func_0014cce0(W8Act *, f32);
void func_00130398(W8Act *, s32, f32);
void func_0014f658(W8Act *, s32);
s32 func_0014c4a8(W8Act *a);

/* 0x14bba8 (needs func_0014b958 defined above) */

void func_0014c400(W8Act *a) {
    a->x148->x100.f = 46.0f;
    a->x1cc &= ~1;
}

void func_0014c428(W8Act *a) {
    a->x148->x100.f = 24.0f;
    a->x1cc |= 1;
}

void func_0014c448(W8Act *a) {
    func_00267560(a->x3c0, a->x3c0, 0.7f);
    func_0014cce0(a, 8.0f);
    func_00130398(a, 6, 8.0f);
}

s32 func_0014c4a8(W8Act *a) {
    if (a->x148->x100.f <= 0.0f && 50.0f < a->x3d4) {
        func_00130398(a, 113, 16.0f);
        func_00267560(a->x3c0, a->x3c0, 0.5f);
        func_0014f658(a, 21);
        return 1;
    }
    return 0;
}

void func_0014c530(W8Act *a) {
    if (func_0014c4a8(a)) a->x148->x100.b.b32 = 0;
}

/* needs make: uses rodata */

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048E408[];
s32 D_00350D10 ALIGNED(16) = (s32)D_0048E408;
#include "data/bss_0052_mixed.h"
#include "data/bss_0054_mixed.h"
#include "data/data_0048.h"
#include "data/data_0030.h"
#include "data/data_0035.h"
