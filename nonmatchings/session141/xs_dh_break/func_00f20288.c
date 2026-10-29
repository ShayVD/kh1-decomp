/* score 95 (1036 vs 1048; was 173). Round 29 wwm2: the literals 3.2f / 0.975f (gcc 2.96 truncates), the scalars declared n, start, spr, jx, jy first (their stack slots 80-96 now match), the second header written through q and q += 16 before start = q (the original keeps it in s1 and spills it), the strip stores in order [0], [1], [2], and the end test as `if (!D_00425BC4 || D_00F311C4 > 1200) { ...; return 4; }`. Left: register choice and schedule in the shard loop, buf + 2 header writes through s1, and three unfilled delay slots (12 bytes). To score it with hand.py, paste shard.h's struct in place of the #include. Round 21 (wwm1): score 95 -> 57 (206 words) with the dependency-checked reorderer (wwm2 r35 hill3, as /tmp/claude-0/s141/wwm1/w3.py). */
/* xs_dh_break.x func_00f20288: draft (session 136), not byte-identical; the port runs it
 * (ovl/xs_dh_break/drafts.tsv). The per-frame task func_00f20b38 installs: the texture and its
 * CLUT (D_00F31340, D_00F31290) and the draw settings (D_00F313F0) are sent, then each of the
 * 2,500 shards as a 4-vertex textured strip (a shard facing away, func_00236e80, is not kicked),
 * shaken by D_00FA2400; a shard whose time has come spins and falls. Ends (4) after 1,200 time
 * units, or at once when D_00425BC4 is 0, setting D_002BC0A8 bit 0 again. */
#include "shard.h"
#include "platform/dma.h"
#include "platform/gs.h"

f32 func_00f20020(void);
void *func_0011fb38(s32, u64, void *);
void *func_00122048(u32, u32);
void func_001220b8(void *);
f32 func_00120ef0(f32 *, OvlVec *, f32 *);
s32 func_00236e80(u32 *, u32 *, u32 *, u32 *);
f32 func_001edcd8(f32);
extern f32 D_002BBDFC;
extern s32 D_002BC0A8;
extern OvlMtx D_002E26C0;
extern OvlMtx D_002C58D0;
extern s32 D_00425BC4;
extern f32 D_00F311C4;
extern u64 D_00F31290[], D_00F31340[], D_00F313F0[];
extern f32 D_00FA2400;

s32 func_00f20288(void) {
    OvlMtx m;
    OvlVec t;
    s32 n;
    u64 *start;
    u32 spr;
    s32 jx;
    s32 jy;
    u64 *buf;
    u8 *q;
    s32 k;
    DhShard *s;
    D_00F311C4 += D_002BBDFC;
    PlatDmaSend(PlatDmaGetChan(2), D_00F31340);
    PlatDmaSend(PlatDmaGetChan(2), D_00F31290);
    PlatDmaSend(PlatDmaGetChan(2), D_00F313F0);
    buf = func_00122048(0x400, 0x80);
    buf[2] = 0x100E400000000001ULL;
    buf[3] = 0xE;
    spr = PLAT_DMA_SPR_ADDR(buf);
    q = (u8 *)func_0011fb38(0x42, 0x44, buf + 4);
    D_00FA2400 = (D_00FA2400 + 3.2f) * 0.975f;
    ((u64 *)q)[0] = 0x3000000000008004ULL;
    ((u64 *)q)[1] = 0x412;
    q += 16;
    start = (u64 *)q;
    jx = (s32)((func_00f20020() - 0.5f) * D_00FA2400);
    jy = (s32)((func_00f20020() - 0.5f) * D_00FA2400);
    s = D_00F317F0;
    for (n = 2499; n >= 0; n--, s++) {
        sceVu0RotMatrix(m, D_002C58D0, s->rot);
        sceVu0CopyVector(m[3], s->c);
        sceVu0MulMatrix(m, D_002E26C0, m);
        q = (u8 *)start;
        for (k = 0; k < 4; k++) {
            f32 w = func_00120ef0(t, m, s->pt[k]);
            ((f32 *)q)[0] = s->tu[k] * w;
            ((f32 *)q)[1] = s->tv[k] * w;
            ((f32 *)q)[2] = w;
            q += 16;
            ((u32 *)q)[0] = 0x80; ((u32 *)q)[1] = 0x80; ((u32 *)q)[2] = 0x80; ((u32 *)q)[3] = 0x80;
            q += 16;
            sceVu0FTOI4Vector((s32 *)q, t);
            ((u32 *)q)[3] = k < 2 ? 0x8000 : 0;
            ((s32 *)q)[0] += jx;
            ((s32 *)q)[1] += jy;
            q += 16;
        }
        if (func_00236e80((u32 *)(q - 0xA0), (u32 *)(q - 0x70), (u32 *)(q - 0x40), (u32 *)(q - 0x10))) {
            *(u32 *)(q - 0x34) = 0x8000;
            *(u32 *)(q - 0x4) = 0x8000;
        }
        buf[0] = (((q - (u8 *)buf) >> 4) - 1) | 0x70000000;
        PlatDmaSend(PlatDmaGetChan(2), (void *)spr);
        if (s->start < D_00F311C4) {
            for (k = 0; k < 3; k++)
                s->rot[k] = func_001edcd8(s->rot[k] + s->drot[k]);
            sceVu0ScaleVector(t, s->vel, D_002BBDFC);
            sceVu0AddVector(s->c, s->c, t);
            s->vel[1] = (s->vel[1] + D_002BBDFC * 0.12249999f) * 0.95f;
        }
        PlatGsSyncPath(0, 0);
    }
    func_001220b8(buf);
    if (D_00425BC4 == 0 || D_00F311C4 > 1200.0f) {
        D_002BC0A8 |= 1;
        return 4;
    }
    return 0;
}
