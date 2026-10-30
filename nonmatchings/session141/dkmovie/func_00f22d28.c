/* Round 60 (wwm2): score 21 -> 17 with the default value grouped as (dbw << 48 | psm << 56) | (psm << 24 | dbp << 32). The other groupings tried stay at 21. Left: the target's move t4,t1 is a gcse copy of dbw << 48 for the flag branch, where ours reuses t1 through cse, and the ORs combine in a different order. Earlier header below. */
/* dkmovie.x func_00f22d28: near miss (session 141), 14 words, score 21 (was 22): (u32)dbp in the default value and a plain (s64)psm << 56 | dbw << 48 | dbp << 32 in the flag branch stop CSE, so dbp << 32 is recomputed inside the branch like the original. Left: the original copies dbp to t3 and dbw << 48 to t4 (two extra moves) and ORs the default as (psm<<24 | dbp<<32) | (dbw<<48 | psm<<56). Tried: if/else and goto forms (92-96 bytes), macro in the branch, a dbw<<48 temp, all flag modes; 10 min permuter on each of two drafts (psm++; psm--; before the if gives 19, not kept). */
#include "ovl.h"
#define GS_SET_BITBLTBUF(sbp, sbw, spsm, dbp, dbw, dpsm) \
    ((u64)(sbp) | ((u64)(sbw) << 16) | ((u64)(spsm) << 24) | \
    ((u64)(dbp) << 32) | ((u64)(dbw) << 48) | ((u64)(dpsm) << 56))
void func_00f22cf8(void *, s32, u64);
void func_00f22d28(void *p, s32 dbp, s32 dbw, s32 psm, s32 flag) {
    u64 v = ((u64)dbw << 48 | (u64)(u32)psm << 56) | ((u64)(u32)psm << 24 | (u64)(u32)dbp << 32);
    if (flag) v = (s64)psm << 56 | (u64)dbw << 48 | (u64)dbp << 32;
    func_00f22cf8(p, 0x50, v);
}
