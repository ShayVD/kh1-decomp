/* 001166e8 (character-vs-world collision step) near miss (hand/nostrict, rodata: jtbl_0048D090/jtbl_0048D0C0, score with wqb03_rr.py 0048D090): size correct (4136), 843 words, most of them because o and fp swap s2/s3 (orig fp=s2, o=s3). Also off: prologue loads 1e6 into $f20 before func_00116628; the per-face hit test should keep the flags word in one reg across the if (orig loads it in both arms); case 8 re-saves t2 around func_00267e90. Needed: u32 bitfields for the face flags word (b15 == 1 stays a compare with 1), kind==11 as (u64 & 0xFF) >> 4 (lbu + dsrl), switch with an empty case 9, best-height test as if (hit < cur - h) { if (d < h) ... } else ..., one ColE *ep in the tail. */
#include "common.h"

typedef struct {
    f32 pos[4];   /* +0x00 */
    f32 d[4];     /* +0x10 */
    f32 r;        /* +0x20 */
    f32 h;        /* +0x24 */
    s32 fl;       /* +0x28 */
    s32 x2C;      /* +0x2C */
    s32 st;       /* +0x30 */
    u8 pad34[4];
    s16 x38;      /* +0x38 */
    s16 x3A;      /* +0x3A */
    s16 x3C;      /* +0x3C */
    s16 x3E;      /* +0x3E */
    f32 out[4];   /* +0x40 */
    u8 pad50[0x18];
    f32 x68;      /* +0x68 */
    s16 x6C;      /* +0x6C */
    s16 x6E;      /* +0x6E */
    s16 x70;      /* +0x70 */
    u8 pad72[4];
    s16 x76;      /* +0x76 */
} ColO;

typedef struct {
    u32 b0 : 1;
    u32 sub : 2;
    u32 b3 : 1;
    u32 kind : 4;
    u32 b8 : 7;
    u32 b15 : 1;
    u32 b16 : 7;
    u32 b23 : 1;
    u32 rest : 8;
} ColF;

typedef struct {
    u8 pad0[0xA];
    u8 xA;
    u8 padB[5];
    ColF f;       /* +0x10 */
} ColE;

typedef struct {
    f32 min[3];
    f32 max[3];
    u16 n;
    u8 pad1A[6];
} ColBox;

typedef struct {
    u64 w;
} ColTri;

extern f32 D_002C1250;
extern s32 D_002C1304;
extern s32 D_002C12C0;
extern s32 D_002BC128;
extern s32 D_002BC130;
extern s32 D_002BD250[];
extern ColE *D_002A6238;

void func_00104eb0(s32, f32 *);
void func_00104f10(s32, f32 *);
s32 func_00115158(f32 *, f32 *, f32 *);
void func_00115408(s32, f32 *, f32 *, s32);
s32 func_00115600(s32, f32 *);
void func_00115758(s32, ColO *);
void func_00116368(ColBox *, s32);
void func_00116628(ColO *);
s32 func_00116690(ColF *);
s32 func_001166a0(ColF *);
s32 func_001166b0(ColF *);
s32 func_001166c0(ColF *);
s32 func_001166c8(ColF *);
s32 func_001166d8(ColF *);
s32 func_00119a20(s32, f32 *, f32 *, f32 *, f32 *);
s32 func_00119ad8(s32, s32, f32 *, f32 *, f32 *, f32 *);
void func_0011a978(s32, s32, f32 *);
void func_0011a9c8(s32, s32, f32 *);
ColTri *func_0011ab38(s32, s32);
u64 func_0011b6a0(ColO *, f32 *, s32);
s32 func_0011bdf8(ColO *, f32 *, s32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);

static inline f32 colDist(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

u64 func_001166e8(ColO *o)
{
    s32 ids[512];
    f32 pos[4] __attribute__((aligned(16)));
    f32 p1[4] __attribute__((aligned(16)));
    f32 p2[4] __attribute__((aligned(16)));
    f32 hit[4] __attribute__((aligned(16)));
    f32 cur[4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    f32 tmp2[4] __attribute__((aligned(16)));
    f32 nrm[4] __attribute__((aligned(16)));
    f32 unk[16] __attribute__((aligned(16)));
    ColBox box __attribute__((aligned(16)));
    s32 list[512];
    s32 tri;
    f32 h2;
    f32 h1;
    s32 best1;
    s32 best2;
    u64 r0;
    u64 hf;
    u64 acc0;
    u64 acc1;
    s32 lastid;
    s32 cnt;
    s32 it;
    s32 maxit;
    s32 (*fn)(ColF *);
    f32 *vel;
    s32 i, n, id, k, tf;
    ColF *fp;
    ColE *ep;
    f32 e, y, d, best;

    acc0 = 0;
    acc1 = 0;
    o->fl |= 0x80000000;
    best2 = -1;
    best1 = -1;
    lastid = -1;
    func_00116628(o);
    fn = func_001166a0;
    maxit = 3;
    it = 0;
    cnt = 0;
    h1 = h2 = 1000000.0f;
    D_002C1250 = o->r - 0.008f;
    switch (o->fl & 0x7C) {
    case 4: fn = func_00116690; break;
    case 16: break;
    case 8: fn = func_001166b0; break;
    case 32: fn = func_001166c0; break;
    case 64: fn = func_001166c8; break;
    default: fn = func_001166d8; break;
    }
    if (D_002C1304 == 1) {
        o->out[1] = o->pos[1];
        o->out[3] = 1.0f;
        o->out[0] = o->pos[0] + o->d[0];
        o->out[2] = o->pos[2] + o->d[2];
        return 0;
    }
    vel = o->d;
    func_00267518(pos, o->pos, vel);
again:
    r0 = 0;
    hf = 0;
    if (!(o->fl & 2)) r0 = func_0011b6a0(o, pos, 0);
again2:
    n = 0;
    func_002675a8(cur, pos);
    i = 0;
    func_002675a8(p1, pos);
    func_002675a8(p2, pos);
    p2[1] -= o->h;
    e = D_002C1250 + o->r * 0.5f;
    box.min[0] = pos[0] - e;
    box.max[0] = pos[0] + e;
    box.min[2] = pos[2] - e;
    box.max[2] = pos[2] + e;
    box.min[1] = (pos[1] - o->h) - e;
    box.max[1] = (pos[1] - o->h) + e;
    func_00116368(&box, 4);
    hit[3] = 1.0f;
    pos[1] -= o->h;
    for (; i < box.n; i++) {
        id = D_002BD250[i];
        func_00104f10(id, tmp);
        fp = &D_002A6238[id].f;
        if (D_002A6238[id].xA && func_00119a20(id, tmp, p2, hit, &D_002C1250)) {
            k = D_002A6238[id].xA;
            tf = fp->b15;
            o->x3A = id;
            o->x38 = k;
            if (tf == 1) o->st |= 4;
        }
        k = fp->kind;
        if (k == 0) continue;
        if (fp->sub) continue;
        switch (k) {
        case 10:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) o->st |= 0x10;
            else list[n++] = id;
            break;
        case 3:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) {
                lastid = id;
                cnt++;
            } else list[n++] = id;
            break;
        case 4:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) o->x6C = id;
            else list[n++] = id;
            break;
        case 2:
            if (func_00119a20(id, tmp, p2, hit, &D_002C1250)) o->x3E = id;
            else list[n++] = id;
            break;
        case 8:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) {
                o->st |= 8;
                hf = 1;
                func_00267e90(tmp, tmp, o->r);
                func_00267518(pos, hit, tmp);
                if (fp->b23) o->x76 = id;
            } else list[n++] = id;
            break;
        case 13:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) o->x70 = id;
            else list[n++] = id;
            break;
        case 6:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) o->x6E = id;
            else list[n++] = id;
            break;
        case 12:
            if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) o->st |= 0x20;
            else list[n++] = id;
            break;
        case 9:
            break;
        default:
            if (fn(fp) == 0) {
                if (func_00119a20(id, tmp, pos, hit, &D_002C1250)) {
                    hf = 1;
                    func_00267e90(tmp, tmp, o->r);
                    func_00267518(pos, hit, tmp);
                    if (fp->b23) o->x76 = id;
                } else list[n++] = id;
            }
            break;
        }
    }
    for (i = 0; i < n; i++) {
        id = list[i];
        func_00104f10(id, tmp);
        fp = &D_002A6238[id].f;
        if (D_002A6238[id].xA && func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) {
            k = D_002A6238[id].xA;
            tf = fp->b15;
            o->x3A = id;
            o->x38 = k;
            if (tf == 1) o->st |= 4;
        }
        k = fp->kind;
        if (k == 0) continue;
        switch (k) {
        case 10:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) o->st |= 0x10;
            break;
        case 3:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) {
                lastid = id;
                cnt++;
            }
            break;
        case 4:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) o->x6C = id;
            break;
        case 2:
            if (func_00119ad8(-1, id, tmp, p2, hit, &D_002C1250)) o->x3E = id;
            break;
        case 8:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) {
                o->st |= 8;
                hf = 1;
                func_00267530(pos, pos, hit);
                func_002673b8(pos, pos);
                func_00267e90(pos, pos, o->r);
                func_00267518(pos, hit, pos);
                if (fp->b23) o->x76 = id;
            }
            break;
        case 13:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) o->x70 = id;
            break;
        case 6:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) o->x6E = id;
            break;
        case 12:
            if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) o->st |= 0x20;
            break;
        case 9:
            break;
        default:
            if (fn(fp) == 0) {
                if (func_00119ad8(-1, id, tmp, pos, hit, &D_002C1250)) {
                    func_00267530(nrm, pos, hit);
                    hf = 1;
                    func_002673b8(nrm, nrm);
                    func_00267e90(nrm, nrm, o->r);
                    func_00267518(pos, hit, nrm);
                    if (fp->b23) o->x76 = id;
                }
            }
            break;
        }
    }
    pos[1] += o->h;
    acc1 |= hf;
    acc0 |= r0;
    if (hf | r0) {
        if (it < maxit) {
            if (!(o->r < colDist(pos, o->pos))) {
                it++;
                goto again;
            }
        } else if (it == 100) {
            goto done;
        }
        if (D_002BC128 == 10 && D_002BC130 == 7) {
            func_00267530(nrm, pos, p1);
            func_002673b8(nrm, nrm);
            func_00267e90(nrm, nrm, o->r);
            func_00267518(pos, p1, nrm);
            if (maxit != 4) {
                maxit = 4;
                it = 0;
                goto again;
            }
        } else {
            func_00267518(pos, o->pos, vel);
            r0 = 0;
            hf = 0;
            it = 100;
            goto again2;
        }
    }
done:
    func_002675a8(cur, pos);
    if (cnt) func_00115758(lastid, o);
    if (!(o->fl & 2)) best2 = func_0011bdf8(o, pos, &tri, &h2);
    box.min[0] = pos[0];
    box.min[2] = pos[2];
    box.min[1] = pos[1] - o->h;
    box.max[1] = pos[1] + 1000000.0f;
    box.max[0] = pos[0];
    box.max[2] = pos[2];
    i = 0;
    n = 0;
    func_00116368(&box, 8);
    for (; i < box.n; i++) {
        id = D_002BD250[i];
        fp = &D_002A6238[id].f;
        if (fp->sub) continue;
        if (fn(fp)) continue;
        if (func_00115600(id, cur)) {
            ids[n] = id;
            n++;
        }
    }
    best = h1;
    pos[1] -= o->h;
    for (i = 0; i < n; i++) {
        func_00115408(ids[i], cur, &hit[1], 0);
        d = fabsf(pos[1] - hit[1]);
        if (d < best) {
            if (hit[1] < cur[1] - o->h) {
                if (d < o->h) {
                    best = d;
                    h1 = hit[1];
                    best1 = ids[i];
                }
            } else {
                best = d;
                h1 = hit[1];
                best1 = ids[i];
            }
        }
    }
    if (best2 == -1) {
        if (best1 == -1) {
            o->x3C = -1;
            func_002675a8(o->out, cur);
            return acc1 | acc0;
        }
        if (D_002C12C0) func_00115408(best1, cur, &h1, 1);
        y = h1;
        tf = 0;
    } else if (h1 < h2) {
        if (D_002C12C0) func_00115408(best1, cur, &h1, 1);
        y = h1;
        tf = 0;
    } else {
        y = h2;
        tf = 1;
        o->x2C = tri;
    }
    if (o->fl & 1) {
        if (!tf) {
            func_00104eb0(best1, tmp2);
            func_00104f10(best1, tmp);
        } else {
            func_0011a9c8(tri, best2, tmp2);
            func_0011a978(tri, best2, tmp);
        }
        if (func_00115158(cur, tmp2, tmp)) {
            o->st |= 1;
        } else {
            if (!tf) {
                if ((((ColTri *) &D_002A6238[best1].f)->w & 0xFF) >> 4 == 11) o->st |= 1;
                else o->st &= ~1;
            } else if ((func_0011ab38(tri, best2)->w & 0xFF) >> 4 == 11) o->st |= 1;
            else o->st &= ~1;
            cur[1] = y;
        }
    } else {
        if (p1[1] + o->h * 0.5f < y) o->st |= 1;
        else cur[1] = y;
        if (!tf) {
            if ((((ColTri *) &D_002A6238[best1].f)->w & 0xFF) >> 4 == 11) o->st |= 1;
        } else if ((func_0011ab38(tri, best2)->w & 0xFF) >> 4 == 11) o->st |= 1;
    }
    o->x68 = y;
    if (!tf) {
        k = o->st;
        o->x3C = best1;
        if (!(k & 1)) {
            ep = &D_002A6238[best1];
            if (ep->xA) {
                o->x38 = ep->xA;
                o->x3A = best1;
                o->st = k | 2;
                if (ep->f.b15 == 1) o->st = k | 6;
            }
        }
    } else {
        o->x3C = best2;
    }
    func_002675a8(o->out, cur);
    return acc0 | acc1;
}
