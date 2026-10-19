/* 001ba520: LCS 15 words, mode hand (strict), no context. FINDING (not better than w22's 10w): natural flag block (old; nw; t = nw & ~old; w10 = t; w4 = nw; wC = old & ~nw; w8 = t;) plus volatile on w4/w8/wC/w10 gives the original's exact store order w10, w4, wC and the original instruction order except two things: sched1 ranks ~nw (insn 107, priority via 109->wC store) above t = nw & ~old (99) at t=7, so ~old and ~nw do not share a3 (original: nor a3=~old; and v0=t; nor a3=~nw) and nw lands in a2, ptr D_00621308 in a3; and the w8 store issues after mul.s f1 + swc1 f4 instead of right after mul.s f0. Register-blind opcode diff floor over 6144 variants (16 volatile subsets x 24 store orders x t/no-t x operand orders x load order) is 7, reached only with all four volatile and order w10,w4,wC,w8. */
#include "common.h"
#include "platform/math.h"
typedef struct {
    struct {
        s32 w0;
        volatile s32 w4, w8, wC, w10;
        u8 pad14[0x1C];
        f32 a[4];
        f32 b[4];
        f32 an[2];
        u8 pad58[8];
        f32 bn[2];
        u8 pad68[8];
    } s;
} __attribute__((aligned(8))) Lt;
typedef struct { Lt l[2]; } Lt2;
extern Lt2 D_00621220;
extern Lt2 D_002BCA00;
extern s32 D_003772D0;
extern s32 D_00621300;
extern Lt D_00621290;
extern Lt D_002BCA70;
extern s32 D_00621308[4];
void func_001ba520(void) {
    f32 v[4];
    Lt *l;
    s32 old, nw, t;
    if (D_003772D0 == 0) {
        D_00621220 = D_002BCA00;
        return;
    }
    (&D_00621220.l[0])[1] = D_002BCA70;
    l = &D_00621220.l[0];
    old = l->s.w4;
    nw = D_00621300;
    v[0] = (f32)D_00621308[0] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308[1] * (1.0f / 256.0f);
    v[2] = 0.0f;
    t = nw & ~old;
    l->s.w10 = t;
    l->s.w4 = nw;
    l->s.wC = old & ~nw;
    l->s.w8 = t;
    v[3] = PlatSqrtf(v[0] * v[0] + v[1] * v[1]);
    l->s.a[0] = v[0];
    l->s.a[1] = v[1];
    l->s.a[2] = v[2];
    l->s.a[3] = v[3];
    l->s.an[0] = v[0] / v[3];
    l->s.an[1] = v[1] / v[3];
    v[0] = (f32)D_00621308[2] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308[3] * (1.0f / 256.0f);
    v[2] = 0.0f;
    v[3] = PlatSqrtf(v[0] * v[0] + v[1] * v[1]);
    l->s.b[0] = v[0];
    l->s.b[1] = v[1];
    l->s.b[2] = v[2];
    l->s.b[3] = v[3];
    l->s.bn[0] = v[0] / v[3];
    l->s.bn[1] = v[1] / v[3];
}

