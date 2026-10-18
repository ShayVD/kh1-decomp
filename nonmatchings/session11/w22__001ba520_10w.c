/* func_001ba520: 10 LCS words off (was 15), mode hand (strict), no context. s10 w9 draft (plain aligned(8) Lt) with the flag block re-ordered by a 768-variant sweep (load order x expression operand order x store order x v[] placement): `l->s.wC = ~nw & old; l->s.w8 = ~old & nw; l->s.w4 = nw; l->s.w10 = ~old & nw;` after the v[] statements. Left: orig loads old (a1) before nw (a0) and computes ~old, t=nw&~old (v0), ~nw, old&~nw (a1); stores w10,w4,wC,w8. Ours loads nw first. Natural order (old; nw; t = nw & ~old; w10 = t; w4 = nw; wC = old & ~nw; w8 = t) is 17: sched1 already issues old before nw there, but the store weights (t dies at w8, wC/nw die at their stores) put w10 last; in the original w10 is first, as if t did not die at w8. Nw in a struct with D_00621220 (alias with the copy loop) changes size (cse shares the base). */
#include "common.h"
#include "platform/math.h"
typedef struct {
    struct {
        s32 w0, w4, w8, wC, w10;
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
    nw = D_00621300;
    old = l->s.w4;
    v[0] = (f32)D_00621308[0] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308[1] * (1.0f / 256.0f);
    v[2] = 0.0f;
    l->s.wC = ~nw & old;
    l->s.w8 = ~old & nw;
    l->s.w4 = nw;
    l->s.w10 = ~old & nw;
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

