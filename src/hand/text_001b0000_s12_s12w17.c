#include "common.h"
#include "platform/math.h"
#include "data/bss_0062.h"
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
/* func_001ba520: one mask variable n for ~old then ~nw (set twice, so not local-alloc'd: t = nw & n is not tied to it). */
void func_001ba520(void) {
    f32 v[4];
    Lt *l;
    s32 old, nw, t, n;
    if (D_003772D0 == 0) {
        D_00621220 = D_002BCA00;
        return;
    }
    (&D_00621220.l[0])[1] = D_002BCA70;
    l = &D_00621220.l[0];
    old = l->s.w4;
    nw = D_00621300;
    l->s.w4 = nw;
    n = ~old;
    t = nw & n;
    l->s.w8 = t;
    n = ~nw;
    l->s.w10 = t;
    l->s.wC = old & n;
    v[0] = (f32)D_00621308[0] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308[1] * (1.0f / 256.0f);
    v[2] = 0.0f;
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

