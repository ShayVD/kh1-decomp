#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0064.h"
#include "data/types/text_00200000_h70.h"
extern f32 D_002BBDFC;

typedef W606Mem_304be8 T74;
typedef Save_304be8 G4BE8;
extern f32 D_002BBDFC;
extern s32 D_00641224, D_00641228, D_00641230, D_00641234;

extern s32 D_00641228, D_00641234;

typedef u32 (*KF3de0)(s32);
extern KF3de0 D_003F3DE0[];
void func_00213e50(u8 *a, s32 lo, s32 hi, s32 k) {
    s32 i, j;
    u32 p;
    u8 t;
    i = lo;
    j = hi;
    p = D_003F3DE0[k](a[(lo + hi) / 2]);
    for (;;) {
        while (D_003F3DE0[k](a[i]) < p) i++;
        while (p < D_003F3DE0[k](a[j])) j--;
        if (i >= j) break;
        t = a[i]; a[i++] = a[j]; a[j--] = t;
    }
    if (lo < i - 1) func_00213e50(a, lo, i - 1, k);
    if (j + 1 < hi) func_00213e50(a, j + 1, hi, k);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_00213d80();
void func_00213db8();
void func_00213e18();
KF3de0 D_003F3DE0[0x4] ALIGNED(16) = {
    (void *)func_00213d80, (void *)func_00213db8, (void *)func_00213e18, 0,
};
#include "data/data_003F.h"
#include "data/pieces/D_002BBDFC.h"
