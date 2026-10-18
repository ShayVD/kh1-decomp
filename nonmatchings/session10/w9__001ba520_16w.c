/* func_001ba520: 16 words off (was 20), mode hand (strict). New: Lt is a plain struct with __attribute__((aligned(8))) instead of union { u64 d[14]; struct s; }: member access through a union has alias set 0, which made every l->s store conflict with the stack v[] stores. Left: the flag block (old/nw/~old/t/~nw/old&~nw) issue order and registers (orig old a1, nw a0, ~old a3, t v0, D_00621308 base a2) and the store order w10,w4,wC,w8; source order of the block has no effect (sched1: ~nw prio 26 vs t 25; sched2 then rotates registers). */
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
    t = nw & ~old;
/*P*/
    l->s.w10 = t;
    l->s.w8 = t;
    l->s.w4 = nw;
    v[2] = 0.0f;
    v[0] = (f32)D_00621308[0] * (1.0f / 256.0f);
    v[1] = (f32)D_00621308[1] * (1.0f / 256.0f);
    l->s.wC = old & ~nw;
/*Q*/
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

