/* func_00166570: MATCHED (session 16, s16m1), hand/nostrict. From s7 w7's 21w draft: the three
 * work matrices are one local array mm[3] (same frame offsets 0/64/128), the bone-chain loop uses
 * mm[1]/mm[2] directly (s11w37's preheader), and a pointer mp = mm, set after `bones = ...`, is used
 * for the two post-loop mm[2][0]/mm[1][0] arguments. mp is a REG copy of the soft frame pointer:
 * gcse neither hashes it as an expression nor copy-propagates a hard register, so (plus mp 128) /
 * (plus mp 64) are not PRE-redundant with the pre-loop (plus $fp N); mp gets REG_EQUIV $fp, no hard
 * register, and reload rematerialises it as sp: the original's fresh `addiu a1,sp,128 / addiu
 * a2,sp,64` after the loop and the `move s6,s2; move s2,s0` preheader copies. */
#include "common.h"
#include "platform/math.h"

typedef f32 G2Mtx[4][4];
void func_00162c5c(G2Mtx, G2Mtx, G2Mtx);
void func_002675a8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);

static inline f32 inl_wrap(f32 v) {
    for (;;) {
        if (v > 3.14159251f) { v -= 6.28318501f; continue; }
        if (v < -3.14159251f) { v += 6.28318501f; continue; }
        break;
    }
    return v;
}

static inline void inl_scl(G2Mtx d, G2Mtx s, f32 *v) {
    func_00267e90(d[0], s[0], v[0]);
    func_00267e90(d[1], s[1], v[1]);
    func_00267e90(d[2], s[2], v[2]);
    func_002675a8(d[3], s[3]);
}

#define INL2(a, b, o, p) do { func_00162c5c(a, (o)->p15C[p], a); func_00162c5c(b, (o)->p160[p], b); } while (0)
