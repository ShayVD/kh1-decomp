/* 00199ac8: LCS 28 words off (finding; s8 w9 draft is 22 with RO=48fb70), hand/nostrict_nofill, rodata 0x48fb70 (lchkro). Twin of 0019ab38 (same finding, same numbers): `k = 0;` right after `d = seg - same;` gives the orig bgtz/`move t0,zero` delay slot and the d<=0 arm, but cse1 folds `du = k` (orig keeps `move t4,t0`) and k (4*19/376 = .202) loses t0 to the case-6 hoisted 0x80000000 (3*11/158 = .209); the surviving du = k copy of the original is the one ref that would flip it. */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));
typedef struct {
    u8 b0;
    s8 type;
    s16 n;
    u8 pad4[12];
} ShipolyPrim;
typedef struct {
    s32 w0;
    s32 w4;
} ShipolyMdl;
typedef struct {
    s16 x, y, z;
} ShipolyEnt;
typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 padC[2];
    ShipolyEnt *ent;
    s32 pad18;
    ShipolyMdl *mdl;
    s32 unk20;
} ShipolySlot;
typedef struct {
    s32 frame;
    s32 id;
    u8 pad8[5];
    u8 bD;
    u8 padE[6];
    u8 b14;
    u8 b15;
} ShipolyKey;
typedef struct {
    u32 cur;
    u8 n;
    u8 b5;
    u8 pad6[2];
    f32 (*buf)[2][4];
} ShipolyWork;
typedef struct {
    u8 c[4][4];
    u16 idx[4];
    u16 uv[4][2];
} ShipolyVtx6;
typedef struct {
    u8 c[4][4];
    u16 idx[4];
} ShipolyVtx4;

extern f32 D_003701D0[4];
void func_00199908(ShipolyKey *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_001996d0(f32 (*)[4], s32, f32 (*)[4]);
void func_00199888(f32 *, f32 (*)[4], f32 (*)[4], f32);
void func_002674f0(f32 *, f32 *, f32 *, f32);
void func_001999f0(ShipolyKey *, s32 *, s32 *, s32 *, s32 *);

static inline void inl_alpha(u8 (*c)[4], s32 k, s32 d, f32 a, f32 db) {
    if (k >= d) {
        c[0][3] = c[1][3] = c[2][3] = c[3][3] = 0;
    } else {
        c[0][3] = c[1][3] = a;
        c[2][3] = c[3][3] = (u8) a - db;
    }
}

void func_00199ac8(ShipolySlot *r, ShipolyKey *key, ShipolyWork *w) {
    f32 pts[32][4] __attribute__((aligned(16)));
    f32 tmp[32][4] __attribute__((aligned(16)));
    f32 out[4] __attribute__((aligned(16)));
    f32 v[2][4] __attribute__((aligned(16)));
    s32 u0, u1, t0, t1;
    u32 cur;
    f32 (*buf)[2][4];
    u8 n;
    s32 seg, segs, same;
    ShipolyEnt *ent;
    s32 i, j, k, d;
    s32 i2, i3, i4;
    f32 a, da, db;
    u32 ui;
    ShipolyPrim *p;
    s32 sz, u, du;
    s32 idx;
    s32 m;
    s32 nu;

    cur = w->cur;
    buf = w->buf;
    n = w->n;
    seg = r->w8;
    same = 0;
    func_00199908(key, buf[cur][0], buf[cur][1]);
    segs = seg + 1;
    ent = r->ent;
    for (j = 0; j < 2; j++) {
        for (i = 0; (u32) i < n; i++) {
            idx = cur - i;
            idx += (idx < 0) * n;
            func_002675a8(pts[i], (f32 *) ((u32) buf + (idx * 2 + j) * 16));
            if (key->b15)
                func_00267530(pts[i], pts[i], D_003701D0);
        }
        func_001996d0(pts, n, tmp);
        for (i = 0; i < segs; i++) {
            func_00199888(out, pts, tmp, (f32) i / (f32) seg * (f32) (u32) (n - 1));
            ent[i * 2 + j].x = out[0];
            ent[i * 2 + j].y = out[1];
            ent[i * 2 + j].z = out[2];
        }
    }
    if (w->b5) {
        ShipolyEnt *e = r->ent;
        for (i2 = seg; i2 > 0; i2--) {
            if (e[i2 * 2].x != e[(i2 - 1) * 2].x || e[i2 * 2].y != e[(i2 - 1) * 2].y || e[i2 * 2].z != e[(i2 - 1) * 2].z)
                break;
            same++;
        }
    }
    if (key->b14) {
        ShipolyEnt *e2;
        a = 1.0f;
        da = 1.0f;
        e2 = r->ent;
        if (seg - same > 0)
            da = 1.0f / (f32) (same > 0 ? seg - same : seg);
        for (i2 = 0; i2 < segs; i2++) {
            for (j = 0; j < 2; j++) {
                v[j][0] = e2[i2 * 2 + j].x;
                v[j][1] = e2[i2 * 2 + j].y;
                v[j][2] = e2[i2 * 2 + j].z;
            }
            func_002674f0(v[0], v[0], v[1], a);
            a -= da;
            e2[i2 * 2].x = v[0][0];
            e2[i2 * 2].y = v[0][1];
            e2[i2 * 2].z = v[0][2];
            if (a <= 0.0f)
                a = 0.0f;
        }
    }
    if (w->b5) {
        p = (ShipolyPrim *) ((u8 *) r->mdl + r->mdl->w4);
        a = 128.0f;
        func_001999f0(key, &u0, &u1, &t0, &t1);
        db = 0.0f;
        d = seg - same;
        k = 0;
        if (d <= 0) {
            a = 0.0f;
            u = 0;
            du = 0;
        } else {
            u = u0;
            db = 128.0f / (f32) d;
            du = (u1 - u0) / d;
        }
        while (p->type != -1) {
            sz = 0;
            switch (p->type) {
            case 4: {
                ShipolyVtx4 *q = (ShipolyVtx4 *) (p + 1);
                for (m = 0; m < p->n; m++) {
                    inl_alpha(q->c, k, seg - same, a, db);
                    a -= db;
                    u += du;
                    if (u1 < u)
                        u = u1;
                    if (a < 0.0f)
                        a = 0.0f;
                    q++;
                    k++;
                }
                sz = 24;
                break;
            }
            case 6: {
                ShipolyVtx6 *q = (ShipolyVtx6 *) (p + 1);
                for (m = 0; m < p->n; m++) {
                    inl_alpha(q->c, k, seg - same, a, db);
                    q->uv[1][0] = u;
                    q->uv[0][0] = u;
                    nu = u + du;
                    q->c[0][2] = q->c[1][2] = q->c[2][2] = q->c[3][2] = 0xFF;
                    q->c[0][1] = q->c[1][1] = q->c[2][1] = q->c[3][1] = 0xFF;
                    q->c[0][0] = q->c[1][0] = q->c[2][0] = q->c[3][0] = 0xFF;
                    q->uv[3][0] = nu - 1;
                    q->uv[2][0] = nu - 1;
                    q->uv[0][1] = q->uv[2][1] = t1;
                    q->uv[1][1] = q->uv[3][1] = t0;
                    a -= db;
                    u = nu;
                    if (u1 < u)
                        u = u1;
                    if (a < 0.0f)
                        a = 0.0f;
                    q++;
                    k++;
                }
                sz = 40;
                break;
            }
            case 0: case 1: case 2: case 3: case 5: case 7:
                return;
            }
            p = (ShipolyPrim *) ((u8 *) p + sz * p->n);
            p++;
        }
    }
    if (key->bD == 0) {
        w->cur++;
        if (w->cur >= w->n) {
            w->b5 = 0;
            w->cur = 0;
        }
    }
}
