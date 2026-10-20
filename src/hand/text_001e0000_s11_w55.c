/* s11w55: func_001e0ab0, func_001e0d98, func_001e10f8 (hand). FLAGGED dead test: each has
   `if (t == (s32)&TIMER) { REST } else { REST }` with identical arms right after the
   `t <= 0` early return. The test is never true and generates no code: jump2 cross-jumps the
   arms and deletes the branch, but flow2's live_at_start of the bgtz target block already
   includes t's register (v0), so reorg's steal_delay_list_from_fallthrough may not move
   `li v0,4` from the `b` slot into the bgtz slot (bgtz keeps its nop, as in the original). */
#include "common.h"
#include "data/bss_0062.h"
extern s32 D_003DB060;
extern s32 D_0062F6D0;
s32 D_0062F640 ALIGNED(16);
s32 D_0062F644 ALIGNED(4);
s32 D_0062F648 ALIGNED(8);
extern f32 D_003DACB0;
extern f32 D_003DACB4;
extern s32 D_003DACB8;
extern s32 D_003DACBC;
extern u64 D_003DAE40[];
extern u8 D_003DAF60[];
void func_001e0608(void);
void func_001e05a8(void *);
extern s32 D_003DB064;
s32 D_0062F64C ALIGNED(4);
s32 D_0062F650 ALIGNED(16);
s32 D_0062F654 ALIGNED(4);
void func_001e07a8(s32);
extern s32 D_003DB06C;
s32 D_0062F664 ALIGNED(4);
s32 D_0062F668 ALIGNED(8);
s32 D_0062F66C ALIGNED(4);

s32 func_001e0ab0(void) {
    f32 f;
    switch (D_003DB060) {
    case 0:

        D_0062F640 = D_0062F6D0;
        D_0062F644 = 0;
        D_0062F648 = 128;
        D_003DB060 = 1;

    case 1:
        break;
    default:
        goto ret0;
    }
    /* t == (s32)&D_0062F640 is never true: a dead test with identical arms. jump2
       cross-jumps the arms and deletes the test, but flow2 already counted the read of
       t (v0) at the bgtz target, so reorg cannot steal `li v0,4` into the bgtz slot. */
    {
        s32 t = D_0062F640;
        if (t <= 0) {
            D_003DB060 = 0;
            return 4;
        }
        if (t == (s32)&D_0062F640) {
        func_001e0608();
        D_003DAE40[15] = (u64)D_0062F644 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F648 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_0062F640--;
        f = (f32)D_0062F640 / (f32)D_0062F6D0 * 128.0f;
        D_0062F648 = f;
        D_0062F644 = 128.0f - f;
            } else {
        func_001e0608();
        D_003DAE40[15] = (u64)D_0062F644 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F648 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_0062F640--;
        f = (f32)D_0062F640 / (f32)D_0062F6D0 * 128.0f;
        D_0062F648 = f;
        D_0062F644 = 128.0f - f;
            }
    }
ret0:
    return 0;
}

s32 func_001e0d98(void) {
    f32 f;
    switch (D_003DB064) {
    case 0:
        D_0062F64C = D_0062F6D0;
        D_0062F650 = 0;
        D_0062F654 = 128;
        D_003DB064 = 1;
    case 1:
        break;
    default:
        goto ret0;
    }
    /* t == (s32)&D_0062F64C is never true: a dead test with identical arms. jump2
       cross-jumps the arms and deletes the test, but flow2 already counted the read of
       t (v0) at the bgtz target, so reorg cannot steal `li v0,4` into the bgtz slot. */
    {
        s32 t = D_0062F64C;
        if (t <= 0) {
            D_003DB064 = 0;
            return 4;
        }
        if (t == (s32)&D_0062F64C) {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F650 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F654 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F64C--;
        f = (f32)D_0062F64C / (f32)D_0062F6D0 * 128.0f;
        D_0062F654 = f;
        D_0062F650 = 128.0f - f;
            } else {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F650 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F654 << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F64C--;
        f = (f32)D_0062F64C / (f32)D_0062F6D0 * 128.0f;
        D_0062F654 = f;
        D_0062F650 = 128.0f - f;
            }
    }
ret0:
    return 0;
}

s32 func_001e10f8(void) {
    f32 f;
    switch (D_003DB06C) {
    case 0:
/*P*/
        D_0062F664 = D_0062F6D0;
        D_0062F668 = 128;
        D_0062F66C = 0;
        D_003DB06C = 1;
/*Q*/
    case 1:
        break;
    default:
        goto ret0;
    }
    /* t == (s32)&D_0062F664 is never true: a dead test with identical arms. jump2
       cross-jumps the arms and deletes the test, but flow2 already counted the read of
       t (v0) at the bgtz target, so reorg cannot steal `li v0,4` into the bgtz slot. */
    {
        s32 t = D_0062F664;
        if (t <= 0) {
            D_003DB06C = 0;
            return 4;
        }
        if (t == (s32)&D_0062F664) {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F668 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F66C << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F664--;
        f = (f32)D_0062F664 / (f32)D_0062F6D0 * 128.0f;
        D_0062F668 = f;
        D_0062F66C = 128.0f - f;
            } else {
        func_001e07a8(0);
        D_003DAE40[22] = 0x8000000664020E00ULL;
        D_003DAE40[15] = (u64)D_0062F668 << 24 | 0x100808080ULL;
        D_003DAE40[33] = (u64)((f32)(D_003DACB8 + 0x7000) + (4096.0f - D_003DACB0 * 4096.0f))
            | (u64)((f32)(D_003DACBC + 29688) + (3072.0f - D_003DACB4 * 3072.0f)) << 16
            | 0xFFFFFFFE00000000ULL;
        D_003DAE40[31] = (u64)D_0062F66C << 24 | 0x100808080ULL;
        D_003DAE40[35] = (u64)(D_003DACB0 * 8192.0f * 0.5f - 4096.0f + 36864.0f + (f32)D_003DACB8)
            | (u64)(D_003DACB4 * 6144.0f * 0.5f - 3072.0f + 35840.0f - 8.0f + (f32)D_003DACBC) << 16
            | 0xFFFFFFFE00000000ULL;
        func_001e05a8(D_003DAF60);
        D_003DAE40[22] = 0x8008000264120E00ULL;
        D_0062F664--;
        f = (f32)D_0062F664 / (f32)D_0062F6D0 * 128.0f;
        D_0062F668 = f;
        D_0062F66C = 128.0f - f;
            }
    }
ret0:
    return 0;
}
#include "data/data_003D.h"
