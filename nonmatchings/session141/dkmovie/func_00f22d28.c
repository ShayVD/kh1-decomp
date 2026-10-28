/* dkmovie.x func_00f22d28: near miss (session 141), score 22: GS BITBLTBUF packing; ours turns the flag test into movz, the original branches and recomputes dbp << 32 inside it. */
#include "ovl.h"
#define GS_SET_BITBLTBUF(sbp, sbw, spsm, dbp, dbw, dpsm) \
    ((u64)(sbp) | ((u64)(sbw) << 16) | ((u64)(spsm) << 24) | \
    ((u64)(dbp) << 32) | ((u64)(dbw) << 48) | ((u64)(dpsm) << 56))
void func_00f22cf8(void *, s32, u64);
void func_00f22d28(void *p, s32 dbp, s32 dbw, s32 psm, s32 flag) {
    u64 v = GS_SET_BITBLTBUF(0, 0, (u32)psm, dbp, dbw, (u32)psm);
    if (flag) {
        v = GS_SET_BITBLTBUF(0, 0, 0, dbp, dbw, psm);
    }
    func_00f22cf8(p, 0x50, v);
}
