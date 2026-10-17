/* func_0010a5d0: ~88w off but structurally 16 insns off; mode hand/nostrict (needs func_0010a550 above: CONTEXT_ONLY copy included). Remaining: original loads switch constants 1 and 2 into t2/v1 in the entry block and shares them (inner sub==1 test is beql with a filled slot); here each compare reloads li 2, giving beqzl/beq + extra nops. Header store order also differs slightly. */
#include "common.h"
typedef int u128 __attribute__((mode(TI)));
extern u64 D_002B70B0[];
extern s32 D_00495250;
void func_0010a4d8(u64 *, s32, s32, s32, s32, s32, s32);
CONTEXT_ONLY s32 func_0010a550(u64 *p, s32 a1, s32 a2, s32 a3, s32 a4, s32 idx, s32 a6) {
    p[0] = D_002B70B0[idx];
    p[1] = 0;
    p += 2;
    func_0010a4d8(p, a2, a6, a4, 4, a3, D_00495250);
    ((s32 *)p)[7] = 0x8000;
    ((s32 *)p)[19] = 0x8000;
    return a1 + 13;
}
extern u8 D_002B71D0[], D_002B7210[], D_002B7250[], D_002B7290[], D_002B72D0[], D_002B7310[], D_002B7350[];
void func_0010a5d0(s32 a0, u8 *p, s32 n, s32 mode, s32 sub) {
    s32 loc[2];
    u64 *q;
    *(u128 *)p = 0;
    *(s32 *)p = 0x7000000e;
    q = (u64 *)(p + 16);
    q[0] = ((u64)n << 47) | 0xd000400000008001ULL;
    q[1] = 0x4124124124128ULL;
    loc[0] = 0;
    loc[1] = 0;
    switch (mode) {
    case 0:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7210, 23, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B72D0, 26, (s32)D_002B71D0); break;
        }
        break;
    case 1:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7250, 22, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7310, 25, (s32)D_002B71D0); break;
        }
        break;
    case 2:
        switch (sub) {
        case 1: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7290, 24, (s32)D_002B71D0); break;
        case 2: func_0010a550((u64 *)(p + 32), 2, a0, (s32)loc, (s32)D_002B7350, 27, (s32)D_002B71D0); break;
        }
        break;
    }
}

