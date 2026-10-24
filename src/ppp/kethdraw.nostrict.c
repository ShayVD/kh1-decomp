/* The KeTh strip draw, -fno-strict-aliasing (docs/modules.md "Session 49"):
 * func_001a7718 builds a node's GS packet (pppKeThDraw through keth.nostrict.c's
 * func_001a8c40), with its GNU C nested functions func_001a67f0,
 * func_001a6c90, func_001a72c8, func_001a7600 and func_001a7668.  Alone in
 * its file for its file-scope #defines.  Read from the code, not proved by
 * a boot. */
#include "common.h"
#include "platform/vu.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 Mtx[4][4] __attribute__((aligned(16)));
typedef f32 Vec[4] __attribute__((aligned(16)));

/* func_001a7718 with its GNU C nested functions func_001a67f0, func_001a6c90,
 * func_001a72c8, func_001a7600, func_001a7668 (static chain in $v0).
 * Uses rodata: three 0.0f literals (one per nested function, 0x48fd98..0x48fda0). */

typedef union {
    u128 q;
    u64 d[2];
    u32 w[4];
    f32 f[4];
} Qw;

typedef struct {
    f32 pos[4];
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
} Vtx;

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    u16 n34;
    u16 pad36;
    u16 n38;
    u16 pad3a;
    u16 n3c;
    u16 f3e;
    Vtx v[1];
} Obj;

typedef struct {
    u8 b[8];
    u8 pad8[4];
    f32 f0c;
    s8 s[8];
    u8 pad18[4];
    f32 f1c;
    u8 pad20[0x10];
    f32 f30;
    u8 pad34[4];
    f32 f38;
} Cfg;

typedef struct {
    Mtx *m;
    Obj *o;
    Qw *pk;
    Cfg *c;
    f32 *uv;
    Qw *last;
    u64 d18;
    u64 d20;
} Arg7718;

f32 func_001a9058(f32, f32);
void func_001a9080(f32 *, f32 *);
void func_001a9098(f32 *, f32 *);
void func_001a90e0(f32 *, f32 *, f32 *);
void func_001a9128(f32 *, f32 *, f32 *);
u32 func_001a9140(f32 *, f32 *, f32 *);
u32 func_001a91b0(f32 *, f32 *);
void func_001a9218(f32 *, f32 *);
s32 func_001a9248(f32 *, Mtx, f32 *);

#define pkt s.pkt_
#define vp s.vp_
#define stride s.stride_
#define base s.base_
#define cnt s.cnt_
#define tagp s.tagp_
#define flag s.flag_
#define n0 s.n0_
#define n1 s.n1_
#define p0 s.p0_
#define p1 s.p1_
s32 func_001a7718(Arg7718 *a) {
    Mtx m;
    Vec c0;
    Vec c1;
    Vec uv;
    Vec d0;
    Vec d1;
    Vec k144;
    Vec v160;
    Vec v176;
    Vec v192;
    Vec v208;
    Vec v224;
    Vec v240;
    Qw tag0;
    Qw tag1;
    Vec pad288[2];
    Vec v320;
    Qw tag2;
    Vec pad352;
    Vec v368;
    Vec v384;
    Vec v400;
    Vec v416;
    Vec v432;
    Vec v448;
    Vec v464;
    Vec tmp;
    struct {
        Qw *pkt_;
        u8 *vp_;
        s32 x504[3];
        s32 stride_;
        Qw *base_;
        s32 cnt_;
        Qw *tagp_;
        u32 flag_;
        s32 n0_;
        s32 n1_;
        Vtx *p0_;
        Vtx *p1_;
        s32 x552[2];
    } s;

    auto void func_001a67f0(void) asm("func_001a67f0");
    auto void func_001a6c90(void) asm("func_001a6c90");
    auto void func_001a72c8(void) asm("func_001a72c8");
    auto void func_001a7600(void) asm("func_001a7600");
    auto void func_001a7668(void) asm("func_001a7668");

    void func_001a67f0(void) {
        tagp = pkt;
        pkt->q = tag2.q;
        pkt++;
        v320[3] = 1.0f - ((Vtx *)vp)->f1c * k144[2];
        PlatVu0FTOI0Vector(tmp, c0);
        func_001a9098(v400, tmp);
        PlatVu0CopyVector(pkt->f, v400);
        pkt++;
        flag = func_001a91b0(pkt->f, v160);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0FTOI0Vector(v384, c1);
        PlatVu0AddVector(tmp, c1, d1);
        PlatVu0ClampVector(c1, tmp, 0.0f, uv[2]);
        PlatVu0FTOI0Vector(v368, c1);
        PlatVu0CopyVector(tmp, (f32 *)vp);
        func_001a9248(v192, m, tmp);
        v320[2] = 1.0f / v192[3];
        vp += stride;
        func_001a9128(tmp, v192, v176);
        func_001a9218(v448, tmp);
        func_001a90e0(tmp, v208, v448);
        func_001a9218(tmp, tmp);
        v320[0] += v240[3];
        v320[0] = func_001a9058(v320[0], 0.0f);
        v464[0] = tmp[1];
        v464[1] = -tmp[0];
        v464[0] = v464[0] * v320[0] * v320[1] * (v320[3] * uv[0]);
        v464[1] = v464[1] * v320[0] * v320[1] * (v320[3] * uv[1]);
        func_001a9080(v208, v448);
        v320[1] = v320[2];
        func_001a9098(v400, v368);
        PlatVu0CopyVector(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v464);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0CopyVector(v224, v464);
        PlatVu0ScaleVector(v416, v464, uv[3]);
        PlatVu0CopyVector(pkt->f, v368);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v416);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0AddVector(tmp, c0, d0);
        PlatVu0ClampVector(c0, tmp, 0.0f, 255.0f);
        PlatVu0FTOI0Vector(v448, c0);
        PlatVu0CopyVector(pkt->f, v448);
        pkt++;
        flag |= func_001a91b0(pkt->f, v176);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0ScaleVector(v416, v464, v240[1]);
        PlatVu0ScaleVector(v448, v416, uv[3]);
        PlatVu0CopyVector(pkt->f, v368);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v448);
        pkt->w[3] |= flag;
        pkt++;
        func_001a9098(v400, v368);
        PlatVu0CopyVector(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v176, v416);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0CopyVector(v160, v176);
        PlatVu0CopyVector(v176, v192);
        cnt--;
    }

    void func_001a6c90(void) {
        while (cnt > 0) {
            v320[3] = 1.0f - ((Vtx *)vp)->f1c * k144[2];
            tagp = pkt;
            pkt->q = tag1.q;
            pkt++;
            PlatVu0FTOI0Vector(v384, c1);
            PlatVu0AddVector(tmp, c1, d1);
            PlatVu0ClampVector(c1, tmp, 0.0f, uv[2]);
            PlatVu0FTOI0Vector(v368, c1);
            PlatVu0CopyVector(tmp, (f32 *)vp);
            func_001a9248(v192, m, tmp);
            v320[2] = 1.0f / v192[3];
            vp += stride;
            func_001a9128(tmp, v192, v176);
            func_001a9218(v448, tmp);
            func_001a90e0(tmp, v208, v448);
            func_001a9218(tmp, tmp);
            v320[0] += v240[3];
            v320[0] = func_001a9058(v320[0], 0.0f);
            v464[0] = tmp[1];
            v464[1] = -tmp[0];
            v464[0] = v464[0] * v320[0] * v320[1] * (v320[3] * uv[0]);
            v464[1] = v464[1] * v320[0] * v320[1] * (v320[3] * uv[1]);
            func_001a9080(v208, v448);
            v320[1] = v320[2];
            func_001a9098(v400, v384);
            PlatVu0CopyVector(pkt->f, v400);
            pkt++;
            flag = func_001a9140(pkt->f, v160, v224);
            pkt->w[3] |= flag;
            pkt++;
            func_001a9098(v400, v368);
            PlatVu0CopyVector(pkt->f, v400);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v464);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0ScaleVector(v448, v224, uv[3]);
            PlatVu0ScaleVector(v432, v224, v240[1]);
            PlatVu0CopyVector(v224, v464);
            PlatVu0ScaleVector(v416, v464, uv[3]);
            PlatVu0CopyVector(pkt->f, v384);
            pkt++;
            flag |= func_001a9140(pkt->f, v160, v448);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0CopyVector(pkt->f, v368);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v416);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0FTOI0Vector(v416, c0);
            PlatVu0AddVector(tmp, c0, d0);
            PlatVu0ClampVector(c0, tmp, 0.0f, 255.0f);
            PlatVu0FTOI0Vector(v448, c0);
            PlatVu0CopyVector(pkt->f, v416);
            pkt++;
            flag |= func_001a91b0(pkt->f, v160);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0CopyVector(pkt->f, v448);
            pkt++;
            flag |= func_001a91b0(pkt->f, v176);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0ScaleVector(v416, v464, v240[1]);
            PlatVu0ScaleVector(v464, v432, uv[3]);
            PlatVu0ScaleVector(v448, v416, uv[3]);
            PlatVu0CopyVector(pkt->f, v384);
            pkt++;
            flag |= func_001a9140(pkt->f, v160, v464);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0CopyVector(pkt->f, v368);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v448);
            pkt->w[3] |= flag;
            pkt++;
            func_001a9098(v400, v384);
            PlatVu0CopyVector(pkt->f, v400);
            pkt++;
            flag |= func_001a9140(pkt->f, v160, v432);
            pkt->w[3] |= flag;
            pkt++;
            func_001a9098(v400, v368);
            PlatVu0CopyVector(pkt->f, v400);
            pkt++;
            flag |= func_001a9140(pkt->f, v176, v416);
            pkt->w[3] |= flag;
            pkt++;
            PlatVu0CopyVector(v160, v176);
            PlatVu0CopyVector(v176, v192);
            cnt--;
        }
    }

    void func_001a72c8(void) {
        tagp = pkt;
        pkt->q = tag2.q;
        pkt++;
        PlatVu0FTOI0Vector(v416, c0);
        PlatVu0AddVector(tmp, c0, d0);
        PlatVu0ClampVector(c0, tmp, 0.0f, 255.0f);
        PlatVu0FTOI0Vector(v448, c0);
        func_001a9098(tmp, v448);
        PlatVu0CopyVector(pkt->f, tmp);
        pkt++;
        flag = func_001a91b0(pkt->f, v176);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0FTOI0Vector(v384, c1);
        func_001a9098(v400, v384);
        PlatVu0CopyVector(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v224);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0ScaleVector(v448, v224, uv[3]);
        PlatVu0ScaleVector(v432, v224, v240[1]);
        PlatVu0CopyVector(pkt->f, v384);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v448);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0CopyVector(pkt->f, v416);
        pkt++;
        flag |= func_001a91b0(pkt->f, v160);
        pkt->w[3] |= flag;
        pkt++;
        PlatVu0ScaleVector(v464, v432, uv[3]);
        PlatVu0FTOI0Vector(v384, c1);
        PlatVu0CopyVector(pkt->f, v384);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v464);
        pkt->w[3] |= flag;
        pkt++;
        func_001a9098(v400, v384);
        PlatVu0CopyVector(pkt->f, v400);
        pkt++;
        flag |= func_001a9140(pkt->f, v160, v432);
        pkt->w[3] |= flag;
        pkt++;
        a->last = tagp;
        a->pk = pkt;
    }

    void func_001a7600(void) {
        PlatVu0CopyVector(tmp, (f32 *)vp);
        func_001a9248(v160, m, tmp);
        vp += stride;
        cnt--;
    }

    void func_001a7668(void) {
        PlatVu0CopyVector(tmp, (f32 *)vp);
        func_001a9248(v176, m, tmp);
        v320[1] = 1.0f / v176[3];
        PlatVu0SubVector(tmp, v176, v160);
        func_001a9218(v208, tmp);
        vp += stride;
        cnt--;
    }

    if (a->o->n38 + a->o->n3c < 3) return 0;
    pkt = base = a->pk;
    stride = 48;
    PlatVu0CopyMatrix(m, *a->m);
    c0[0] = a->c->b[0];
    c0[1] = a->c->b[1];
    c0[2] = a->c->b[2];
    c0[3] = a->c->b[3];
    c1[0] = a->c->b[4];
    c1[1] = a->c->b[5];
    c1[2] = a->c->b[6];
    c1[3] = a->c->b[7];
    d0[0] = a->c->s[0];
    d0[1] = a->c->s[1];
    d0[2] = a->c->s[2];
    d0[3] = a->c->s[3];
    d1[0] = a->c->s[4];
    d1[1] = a->c->s[5];
    d1[2] = a->c->s[6];
    d1[3] = a->c->s[7];
    v240[1] = -1.0f;
    v320[0] = a->c->f0c;
    k144[2] = a->c->f38;
    uv[3] = a->c->f30;
    v240[3] = a->c->f1c;
    uv[2] = 255.0f;
    ((s32 *)v400)[3] = 0;
    k144[0] = 4096.0f;
    k144[1] = 4096.0f;
    ((s32 *)k144)[3] = 0x8000;
    uv[0] = a->uv[0];
    uv[1] = a->uv[1];
    tag0.d[0] = 0x2000000000000001;
    tag0.d[1] = 238;
    tag1.d[0] = 0x202640000000000a;
    tag2.d[0] = 0x2026c00000000006;
    tag1.d[1] = 81;
    tag2.d[1] = 81;
    if (!(a->o->f3e & 0x1000)) {
        v464[0] = a->o->f30;
        PlatVu0ScaleVector(tmp, d0, v464[0]);
        PlatVu0AddVector(tmp, c0, tmp);
        PlatVu0ClampVector(c0, tmp, 0.0f, uv[2]);
        PlatVu0ScaleVector(tmp, d1, v464[0]);
        PlatVu0AddVector(tmp, c1, tmp);
        PlatVu0ClampVector(c1, tmp, 0.0f, uv[2]);
        tmp[0] = v320[0] + v240[3] * v464[0];
        if (tmp[0] < 0.0f) {
            v320[0] = 0.0f;
        } else {
            v320[0] = tmp[0];
        }
        n0 = a->o->n38;
        n1 = a->o->n3c;
        p0 = a->o->v + a->o->n34;
        p1 = a->o->v;
    } else {
        n0 = a->o->n3c;
        n1 = a->o->n38;
        p0 = a->o->v + a->o->n3c - 1;
        p1 = a->o->v + a->o->n34 + a->o->n38 - 1;
        stride = -stride;
    }
    tagp = pkt;
    pkt->q = tag0.q;
    pkt++;
    pkt->d[0] = a->d20;
    pkt->d[1] = 71;
    pkt++;
    pkt->d[0] = a->d18;
    pkt->d[1] = 66;
    pkt++;
    if (n0 != 0) {
        vp = (u8 *)p0;
        cnt = n0;
        func_001a7600();
        if (cnt == 0) {
            vp = (u8 *)p1;
            cnt = n1;
            goto l7668;
        }
        func_001a7668();
        if (cnt == 0) {
            vp = (u8 *)p1;
            cnt = n1;
            goto l67f0;
        }
        func_001a67f0();
        n0--;
        func_001a6c90();
        if (n1 == 0) goto end;
        cnt = n1;
        vp = (u8 *)p1;
        goto l6c90;
    }
    vp = (u8 *)p1;
    cnt = n1;
    func_001a7600();
l7668:
    func_001a7668();
l67f0:
    func_001a67f0();
l6c90:
    func_001a6c90();
end:
    func_001a72c8();
    return 1;
}
