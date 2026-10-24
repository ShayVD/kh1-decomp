#include "common.h"
#include "data/bss_0066.h"
s32 func_0025dd48(s32 a0, s32 a1, s32 a2, s32 a3, void *a4, s32 a5);

extern s32 D_0046A618;
extern s32 D_0046A614;

void func_0024d5d0(s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        s32 *p = &D_0046A618;
        (*p)++;
    }
}

s32 func_0024dad0(s32 a0, s32 n) {
    u32 v;
    func_0025dd48(a0, 0x4802, 0, 0, 0, 0);
    D_0046A614 = 60;
    v = 0;
    if (func_0025dd48(a0, 0x480A, 0, 0, &v, 4) != 0) return 0;
    D_0046A614 = 70;
    if ((s32)(v >> 18) < n) return 0;
    return 1;
}
#include "data/bss_0066_mixed.h"
#include "data/data_0046.h"
