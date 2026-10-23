#include "common.h"
#include "data/pieces/D_00350D88.h"
#include "data/bss_0052.h"

/* Hand-matched functions 0x0012b7a8-0x0012fcd0 (session 6, worker 05). Nostrict region. */

/* ---- shared types ---- */

/* 0x730-byte pool node (D_004F8310[64]). */
typedef struct Node {
    union {
        u64 flags;
        struct { s32 w0; s32 f4; } w;
    };
    s32 f8;
    s32 *cur;
    s32 *f10;
    u8 pad014[0xc];
    s32 l20[0x100];
    s32 l420[0xc0];
    struct Node *next;
    s16 h724[6];
} Node;

/* 0x38-byte menu cursor block (D_002E2FD8[7]); D_002E3170 is a stack of them. */
#include "data/pieces/D_002E3170.h"
typedef Q8_2e3170 Q8;

/* Menu item (func_001478c8 result). */
#include "data/pieces/D_002E319C.h"
typedef O8_2e319c O8;

typedef struct T23 { u8 b0; u8 pad[19]; } T23;
typedef struct Info { u8 pad[4]; u32 f4; u8 pad8[0x57]; u8 f5f; } Info;
typedef struct Info2 { u8 pad[7]; u8 f7; u8 pad8[0x14]; T23 *f1c; } Info2;
typedef struct Actor {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor *f98;
    u8 pad9c[0x130 - 0x9c];
    Info *f130;
    Info2 *f134;
    u8 pad138[0x164 - 0x138];
    s32 f164;
    u8 pad168[4];
    f32 f16c;
    u8 pad170[0x370 - 0x170];
    u64 f370;
    u8 pad378[0x3ac - 0x378];
    u32 f3ac;
    u8 pad3b0[0x440 - 0x3b0];
    u64 f440;
} Ent;

typedef struct V8 { Ent *a; s32 b; } V8;
typedef struct Hit { s32 f0; Ent *e; } Hit;
#include "data/pieces/D_00304BE8_s.h"

/* ---- data ---- */
extern Node D_004F8310[64];
extern Q8 D_002E2FD8[7];
extern Q8 **D_00524F40; /* src/data/bss_0052.c: void **D_00524F40 */
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E31B0.h"
extern s32 D_002E31BC;
extern u32 D_00524F44;
extern s32 D_00524F48;
extern s32 D_00524F4C;
extern void (*D_00524F74)(void);
extern f32 D_00524F78; /* src/data/bss_0052.c: s32 D_00524F78 */
extern u32 D_002C5958;
extern f32 D_002BBDFC;
extern u32 D_002C5BB8;
extern s32 D_0052528C;
extern V8 D_00524F80[]; /* src/data/bss_0052.c: P5c0 D_00524F80[0x61] */
extern V8 *D_00525288; /* src/data/bss_0052.c: s32 D_00525288 */
#include "data/pieces/D_002E2780.h"

/* ---- functions ---- */
extern void func_0012cb40(Q8 *, s32, u8);
extern void func_0012fc58(void);
extern s32 func_00137330(Ent *, Ent *, s32);
extern Hit *func_00122048(s32, s32);
extern s32 func_0012cf48(Ent *, Hit *);
extern void func_001220b8(Hit *);
extern void func_00245238(s32, Ent *);
extern void func_0012fb20(V8 *, s32);
extern void func_00158960(void);
extern s32 func_00130030(Ent *);
extern s32 func_001443a8(Ent *);
extern s32 func_0013db30(Ent *);
extern s32 func_0012e4b0(void);
extern void func_0012e970(void);
extern s32 func_0011ef38(void *);
extern void func_0011ef10(s32, void *);
extern void func_001315c0(Ent *, s32, f32 *, f32);
extern s32 func_0012ee70(Ent *, s32);
extern Ent *func_001230a0(Ent *);
extern s32 func_00123368(Ent *);
extern f32 func_0012ed88(Ent *, V8 *, f32 *, f32 *);
extern f32 func_00121b38(f32 *, f32 *);
extern s32 func_0012f0f8(f32 *, f32 *, s32);
extern s32 func_0012eaf8(Ent *);
extern f32 func_0012ec60(Ent *, s32, f32 *);
extern f32 func_00120bf8(f32 *);
extern void func_00267530(f32 *, f32 *, f32 *);
extern s32 func_00219288(void);
extern void func_0017eff8(void);
extern void func_0012fc20(void);
extern void func_00123030(Ent *, s32, s32);
extern float fabsf(float);

Node *func_0012b7a8(s32 a) {
    Node *n = D_004F8310;
    s32 i;
    for (i = 0; i < 64; i++, n++) {
        if (!(n->flags & 1)) {
            n->w.w0 = 0;
            n->flags |= 1;
            n->flags |= 2;
            n->f8 = a;
            n->w.f4 = a;
            n->cur = n->l20;
            *n->cur++ = 0;
            *n->cur++ = 0;
            *n->cur++ = 0;
            *n->cur++ = 0;
            n->f10 = n->l420;
            n->next = 0;
            { s32 j; for (j = 0; j < 5; j++) n->h724[j] = 0; }
            break;
        }
    }
    return n;
}

void func_0012ca38(void) {
    s32 i;
    for (i = 7; i >= 0; i--) D_002E3170[i] = 0;
    D_00524F40 = D_002E3170;
    D_002E3170[0] = D_002E2FD8;
    D_002E319C = D_002E31A0 = 0;
    D_002E2FD8[0].fc = 0;
}

CONTEXT_ONLY s32 func_0012cc38(s32 i, s32 v) {
    u32 *p = &D_00524F44;
    if ((*p >> i) & 1) return 0;
    func_0012cb40(D_002E2FD8, i, v);
    *p |= 1 << i;
    return 1;
}

CONTEXT_ONLY void func_0012ccb0(s32 i) {
    u32 m = 1 << i;
    D_002E2FD8[0].f4 |= m;
    D_002E2FD8[0].f8 |= m;
    D_00524F44 &= ~m;
}

void func_0012d930(u32 *a0) {
    V8 tmp;
    s32 m;
    Ent *pl;
    Ent *e;
    Hit *h;
    s32 n, i, k;
    u32 old;
    u32 *fp;

    if (D_002E31B8 == 1) func_0012fc58();
    if (D_00304BE8->f874 & 0x20) return;
    D_002E2FD8[0].ids[3] = 0;
    m = 0;
    pl = D_002E26A0[0];
    tmp.a = 0;
    tmp.b = 0;
    fp = &D_00524F44;
    *fp = 0;
    if (D_00524F74) D_00524F74();
    if (pl->f98) func_00137330(pl->f98, pl, -1);
    if (*fp & 8) return;
    if ((*a0 >> 8) & 1) return;
    if (!(pl->f0 & 0x2000000)) {
        h = func_00122048(0x300, 4);
        n = func_0012cf48(pl, h);
        for (i = 0; i < n; i++) {
            e = h[i].e;
            switch (e->f130->f5f) {
            case 1:
                if (!pl->f98 && !(D_002C5958 & 1) && func_0012cc38(0, 4)) {
                    tmp.a = e;
                    m = 0;
                    k = pl->f70;
                    if (k && k != 24 && k != 8) func_0012ccb0(0);
                }
                break;
            case 2:
                if (func_0012cc38(3, 5)) {
                    m = 1;
                    tmp.a = e;
                    if ((D_002C5958 & 1) || ((k = pl->f70) && k != 24 && k != 8)) func_0012ccb0(3);
                }
                break;
            case 3: {
                u32 *fq = &D_00524F44;
                old = *fq;
                func_00137330(e, pl, -1);
                if (*fq != old) {
                    tmp.a = e;
                    m = 1;
                }
                break;
            }
            case 4:
                if (func_0012cc38(0, 1)) {
                    tmp.a = e;
                    m = 0;
                }
                break;
            }
            if (tmp.a) break;
        }
        func_001220b8(h);
    }
    if (tmp.a) {
        func_00245238(m, pl);
        if (D_002E31B8 < 3) func_0012fb20(&tmp, 1);
        if ((D_002C5958 >> 13) & 1) func_0012ccb0(3);
    }
    func_00158960();
}

s32 func_0012dd70(O8 *o) {
    Ent *p = D_002E26A0[0];
    s32 k;
    if (o->f6 == 71) return 1;
    k = o->f6;
    switch (k) {
    case 4: case 5: case 55:
        if (func_00130030(p) || (p->f0 & 0x400)) return 0;
    }
    if ((o->f6 != 100 && func_001443a8(p)) || p->f70 == 1) return 0;
    if (func_0013db30(p)) return 1;
    if (*(u16 *)&o->f6 == 2 && (p->f164 == 61 || p->f164 == 138) && p->f16c >= 14.0f) return 1;
    if (o->f6 == 99 && p->f16c >= 12.0f) return 1;
    return 0;
}

#include "data/types/nostrict_text_00120000_s6_05_p.h"
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
extern St3190 D_002E3190;
#include "data/pieces/D_002E3168.h"
extern Pad D_002C5BB0;
#include "data/pieces/D_002C5960.h"
extern s32 D_002E27A8;
extern s32 D_00524F50;
extern void *memset(void *, s32, u32);
extern s32 func_00122ff8(Ent *);
extern void func_0012dc70(void);
extern s32 func_001375d8(Ent *);
extern s32 func_0012e1b0(Pad *);
extern O8 *func_001478c8(s32);
extern s32 func_0012dea0(Q8 *, s32);
extern void func_0012e120(void);
extern void func_0012f700(Pad *);
extern void func_0011d768(s32);
extern void func_0012dce0(Q8 *);
extern Q8 *func_0012dd38(void);
CONTEXT_ONLY s32 func_0012e1b0(Pad *pad) {
    Q8 *q;
    Q8 *cur;
    O8 *o;
    u32 k;
    s32 r;
    s32 snd;

    D_00524F40 = D_002E3170;
    while ((q = D_00524F40[1]) && q->n && !((*D_00524F40)->f8 & (1 << (*D_00524F40)->f34))) {
        cur = *D_00524F40;
        o = func_001478c8(cur->ids[cur->f34]);
        if (q != &D_002E2FD8[o->f8]) break;
        q = *++D_00524F40;
        if (q->fc >= 0) {
            if (q->fc >= q->n) q->fc = q->n - 1;
            if (q->f8 & (1 << q->fc)) break;
        }
    }
    D_00524F40[1] = 0;
    q = *D_00524F40;
    if (q->fc < 0) return 1;
    r = 0;
    o = func_001478c8(q->ids[q->fc]);
    k = pad->x8;
    if (k == 0x100) {
        if (q->f8 & (1 << q->fc)) {
            snd = 4;
            goto play;
        }
        if (o->f8 > 0) {
            q->f34 = q->fc;
            func_0012dce0(&D_002E2FD8[o->f8]);
        }
        goto end;
    } else if (k == 0x80 || (k & 2)) {
        if (D_00524F40 > D_002E3170) {
            q = func_0012dd38();
            snd = 3;
            if ((pad->x8 & 2) && q->fc >= 0) q->fc = 0;
            goto play;
        } else if (k & 0x80) {
            snd = 1;
            if (q->fc >= 0) q->fc = 0;
            goto play;
        }
        r = 1;
        goto end;
    } else if (k == 0x20) {
        s32 v = q->fc;
        if (v <= 0) v = q->n;
        q->fc = v - 1;
        snd = 1;
        goto play;
    } else if (k == 0x40) {
        if (q->fc < q->n - 1) q->fc = q->fc + 1;
        else q->fc = 0;
        snd = 1;
        goto play;
    }
    r = 1;
    goto end;
play:
    func_0011d768(snd);
end:
    D_002E319C = (*(O8 **)&D_002E31A0) = func_001478c8(q->ids[q->fc]);
    return r;
}

s32 func_0012e4b0(void) {
    Ent *e;
    u32 f;
    s32 k;
    u32 mask;
    Pad *p;
    D_002E3168 = 0;
    memset(&D_002E3190, 0, 12);
    f = D_002C5958;

    D_002E3190.w |= 0x2000000;
    D_002E319C = D_002E31A0 = 0;
    D_00524F48 = (D_00524F48 & 0xc) | ((f & 0x104004) != 0);

    if (f & 0x8000004) {
        D_00524F48 |= 8;
    } else {
        if (D_00524F48 & 8) func_0012ca38();
        D_00524F48 &= ~8;
    }
    if (!func_00122ff8((*(V8 *)&D_002E31B0).a)) func_0012fc58();
    e = D_002E26A0[0];
    if (!(((*(u32 *)&D_002C5960) >> 2) & 1) && e && D_002E27A8 != 2 && !((D_002C5958 >> 27) & 1)) {
    p = &D_002C5BB0;
    if (D_002C5958 & 0x104004) {
        if (p->x8 & 4) D_002E3190.w |= 0x1000000;
        func_0012ca38();
        return 0;
    }
    D_00524F48 |= 2;
    func_0012dc70();
    if (func_001375d8(e)) D_00524F50 = 0;
    if (D_002E3170[0] == &D_002E2FD8[0]) {
        if (D_00524F50 && (p->x4 & 0x40000)) {
            memset(D_002E3170, 0, 32);
            D_002E3170[0] = &D_002E2FD8[5];
            D_00524F40 = D_002E3170;
        }
    } else if (!(p->x4 & 0x40000) || !D_00524F50) {
        memset(D_002E3170, 0, 32);
        D_002E3170[0] = &D_002E2FD8[0];
        D_002E2FD8[0].fc = 0;
        D_00524F40 = D_002E3170;
    }
    if (func_001375d8(e)) return 0;
    if (!((e->f370 >> 34) & 1)) goto out;
    {
    if (D_00524F40 == D_002E3170) {
        k = e->f70;
        if (k - 24 < 2u || k == 33 || k == 8) {
            if (p->x4 & 4) D_002E3190.w |= 0x8000000;
        } else if (p->x8 & 4) {
            D_002E3190.w |= 0x1000000;
            return 0;
        }
    }
    if (D_002E3170[0]->f0 == 5) {
        mask = 0x390000;
    } else {
        if (p->x8 & 8) D_002E3168 |= 1;
        k = e->f70;
        if (k - 24 < 2u || k == 33 || k == 8) {
            if (p->x4 & 0x10) D_002E3190.w |= 0x10000000;
        } else if (p->x8 & 0x10) {
            D_002E3190.w |= 0x4000000;
            return 0;
        }
        mask = 0x10000;
    }
    if (func_0012e1b0(p)) {
        if (D_002E319C) {
            if ((D_002E319C->f0 & 0x10) ? (p->x4 & mask) : (p->x8 & mask)) {
                if (!(p->x8 & mask)) D_002E3190.w &= ~0x2000000;
                func_0012e120();
            }
        } else {
            D_002E319C = (*(O8 **)&D_002E31A0) = func_001478c8(67);
            if (p->x8 & 0x80000) func_0012dea0(*D_00524F40, 0);
            else if (p->x8 & 0x100000) func_0012dea0(*D_00524F40, 1);
            else if (p->x8 & 0x200000) func_0012dea0(*D_00524F40, 2);
        }
    }
    func_0012f700(p);
    }
    }
out:
    return 0;
}

void func_0012ea38(void) {
    s32 i;
    func_0012ca38();
    D_002E31A8 = 0;
    D_00524F48 = D_00524F4C = 0;
    D_00524F74 = 0;
    if (func_0011ef38(func_0012e4b0)) return;
    for (i = 6; i >= 0; i--) D_002E2FD8[i].fc = 0;
    D_002E2FD8[5].fc = -1;
    func_0011ef10(0xd6d8, func_0012e4b0);
    func_0011ef10(0x2980f, func_0012e970);
}

CONTEXT_ONLY s32 func_00122ff8(Ent *o) {
    s32 r = 0;
    if (o) {
        if ((o->f370 & 0x300000000) == 0x100000000) r = 1;
    }
    return r;
}

s32 func_0012f040(Ent *o, s32 i) {
    Info2 *in;
    if (!func_00122ff8(o) || ((u32)(o->f370 >> 47) & 1) || (o->f0 & 0x200)) return 0;
    if (i >= 0) {
        in = o->f134;
        if (!in) return 1;
        if (in->f7 && !(in->f1c[i].b0 & 0xf) && (o->f3ac & (1 << i))) return 0;
    }
    return 1;
}

/* func_0012f218 (src/hand/nostrict_nofill/text_00120000_h54.c). */
typedef union { u64 x; struct { u32 lo0; u32 x32:3; u32 f35:1; u32 x36:1; u32 kind:2; u32 hi:25; } b; } F370b;
typedef struct { u8 pad[0x370]; F370b f370; } E9;
CONTEXT_ONLY s32 func_0012f218(f32 *pos, V8 *a, s32 lim) {
    f32 tmp[4];
    f32 d[4];
    f32 r;
    s32 s, v;
    r = func_0012ec60(a->a, a->b, tmp);
    func_00267530(d, tmp, pos);
    r = func_00120bf8(d) - r;
    if (func_0012eaf8(a->a) && r > 1200.0f) return -1;
    s = r;
    if (!(r > 0.0f)) s = 0;
    if (D_002E319C) {
        switch (((E9 *)a->a)->f370.b.kind) {
        case 1:
            v = D_002E319C->f9;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        case 2:
            v = D_002E319C->fa;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        case 0:
        case 3:
            v = D_002E319C->fb;
            if (v < 0) return -1;
            s |= v << 24;
            break;
        }
    }
    if (lim >= 0 && !(s < lim)) return -1;
    if (((E9 *)a->a)->f370.b.f35 && func_0012f0f8(&D_002E2780.x, tmp, 0)) return s;
    if (!func_0012f0f8(pos, tmp, 0)) return -1;
    if (func_0012eaf8(a->a)) s |= 0x10000;
    return s;
}

/* func_0012ee70 (src/hand/text_00120000_h31.c). */
CONTEXT_ONLY s32 func_0012ee70(Ent *e, s32 i) {
    Info2 *m = e->f134;
    if (i < 0) {
        if (!m || !m->f7) return 0;
        i = 0;
    } else {
        if (!m || !m->f7) return -1;
        i++;
    }
    for (; i < e->f134->f7; i++) {
        if (!(e->f3ac & (1 << i)) && !(e->f134->f1c[i].b0 & 0xf)) return i;
    }
    return -1;
}

void func_0012f3d0(V8 *out) {
    f32 pos[4];
    V8 cur;
    Ent *pl = D_002E26A0[0];
    s32 n = D_0052528C;
    V8 *tbl = D_00524F80;
    s32 best = -1;
    s32 i, r;

    func_001315c0(pl, 0x8003, pos, 0.0f);
    out->a = 0;
    cur.a = 0;
    while ((cur.a = func_001230a0(cur.a)) != 0) {
        if (cur.a == pl) continue;
        if (cur.a == pl->f98) continue;
        if (!func_0012f040(cur.a, -1)) continue;
        cur.b = -1;
        while ((cur.b = func_0012ee70(cur.a, cur.b)) >= 0) {
            for (i = 0; i < n; i++) {
                if (tbl[i].a == cur.a && tbl[i].b == cur.b) break;
            }
            if (i < n) continue;
            r = func_0012f218(pos, &cur, best);
            if (r >= 0) {
                *out = cur;
                best = r;
            }
        }
    }
}

void func_0012f868(V8 *out) {
    V8 cur;
    f32 pos[4];
    f32 b[4];
    f32 c[4];
    Ent *pl = D_002E26A0[0];
    f32 best = -1.0f;
    f32 d, t;

    func_001315c0(pl, 0, pos, 1.0f);
    cur.a = 0;
    out->a = 0;
    while ((cur.a = func_001230a0(cur.a)) != 0) {
        if (((cur.a->f370 >> 37) & 3) != 2 && !(cur.a->f130->f4 & 0x8000)) continue;
        if (!func_00123368(cur.a)) continue;
        if (!func_0012f040(cur.a, -1)) continue;
        cur.b = -1;
        while ((cur.b = func_0012ee70(cur.a, cur.b)) >= 0) {
            d = func_0012ed88(pl, &cur, b, c);
            if (d > 300.0f) continue;
            t = func_00121b38(pl->f30, c);
            d *= (1.0f - t) * 0.5f * 0.5f + 1.0f;
            d += fabsf(c[1]) * 0.19999999f;
            if (best >= 0.0f && d > best) continue;
            if (c[1] < -350.0f) continue;
            if (c[1] > 350.0f) continue;
            if (!func_0012f0f8(pos, b, 0)) continue;
            *out = cur;
            best = d;
        }
    }
}

/* func_0012eb08, func_0012fa98 (src/hand/text_00120000_h5.c), func_0012fc58 (src/auto). */
CONTEXT_ONLY s32 func_0012eb08(V8 *p) {
    f32 a[4];
    f32 b[4];
    if (!func_0012f040((*(V8 *)&D_002E31B0).a, D_002E31B0.f4)) return 1;
    if (func_0012eaf8(p->a)) {
        if (func_0012ed88(D_002E26A0[0], p, a, b) > 1500.0f) return 1;
        if (fabsf(b[1]) > 1000.0f) return 1;
    }
    return 0;
}

CONTEXT_ONLY void func_0012fa98(void) {
    f32 a[4];
    f32 b[4];
    f32 d = func_0012ed88(D_002E26A0[0], ((V8 *)&D_002E31B0), a, b);
    s32 *o = &D_002E31BC;
    O8 *x = D_002E31A0;
    s32 r = 0;
    if (x) {
        if (!(d < x->f0c)) {
            if (d < x->f0e) r = 1;
            else r = 2;
        }
        *o = r;
    }
}

CONTEXT_ONLY void func_0012fc58(void) {
    if (D_002E31B8 != 0) {
        if (D_002E31B8 >= 3) func_0017eff8();
        func_0012fc20();
        if (D_002E26A0[0] != 0) func_00123030(D_002E26A0[0], 0, 0);
    }
}

/* rodata: jump tables at 0x48d550, 0x48d570 */
s32 func_0012fcd0(void) {
    Ent *pl = D_002E26A0[0];
    V8 tmp;
    if (!pl || ((s32)(pl->f440 >> 32) & 1)) {
        func_0012fc58();
        return 0;
    }
    if (D_002E31B8 >= 3 && pl->f70 != 1 && !((D_00350D88[pl->f70].f0 >> 2) & 1)) {
        func_0012fc58();
        return 0;
    }
    switch (D_002E31B8) {
    case 4: {
        f32 *p = &D_00524F78;
        *p += D_002BBDFC;
        if (*p >= 90.0f || (D_002C5BB8 & 0x400000)) {
            func_0012fc58();
            break;
        }
    }
    case 3:
        if (func_0012eb08(((V8 *)&D_002E31B0))) func_0012fc58();
        break;
    case 0:
    case 2:
        func_0012fc58();
        break;
    case 1:
        break;
    }
    switch (D_002E31B8) {
    case 3: {
        V8 *dst = D_00524F80;
        V8 *src = dst;
        s32 i;
        for (i = 0; i < D_0052528C; i++, src++) {
            if (func_0012f040(src->a, src->b) && !func_0012eb08(src)) {
                if (src != dst) {
                    V8 **pp = &D_00525288;
                    *dst = *src;
                    if (src == *pp) *pp = dst;
                }
                dst++;
            }
        }
        D_0052528C = dst - D_00524F80;
        break;
    }
    case 1:
        if (!func_0012f040((*(V8 *)&D_002E31B0).a, D_002E31B0.f4)) func_0012fc58();
        break;
    case 0:
    case 2:
        if (func_00219288() != 1 && D_002E319C && (D_002E319C->f0 & 4)) {
            func_0012f868(&tmp);
            if (tmp.a) func_0012fb20(&tmp, 2);
        }
        break;
    case 4:
        break;
    }
    if (D_002E31B8 >= 3) func_0012fa98();
    return 0;
}

typedef struct Ob {
    u8 pad[6];
    u8 f6;
    u8 pad7[0x160 - 7];
    u32 b0:1;
    u32 b1:1;
    u32 b2:30;
    s32 f164;
    s32 f168;
    f32 f16c;
    u8 pad170[8];
    s32 f178;
    u8 pad17c[0x1d4 - 0x17c];
    s32 *f1d4;
    u64 pad1d8;
} Ob;
extern s32 func_00130190(Ob *);
extern s32 func_00167698(s32);
extern s32 func_00130270(Ob *, s32);
extern s32 func_001302d0(Ob *, s32, f32, f32);

void func_00130398(Ob *o, s32 a1, f32 t) {
    s32 r, k, v;
    f32 f, a, b;
    o->f178 = 0;
    r = func_00130190(o);
    if (!(r & 0x200000) && (r & 0xffff) == o->f168) return;
    if (o->f6 == 3) {
        k = (u16)a1;
        if (o->b1) {
            v = o->f164;
            if ((u32)(v - 1) < 2 || v == 172 || v == 173) {
                if ((u32)(k - 1) < 2 || k == 172 || k == 173) {
                    a = func_00167698(o->f1d4[o->f168]);
                    b = func_00167698(o->f1d4[r]);
                    f = b * ((o->f16c + D_002BBDFC + t) / a);
                    while (b <= f) f -= b;
                    goto call;
                }
            }
        }
        if (k == 1 && o->f164 == 0) f = t * 0.5f;
        else f = 0.0f;
    } else {
        f = 0.0f;
    }
call:
    func_001302d0(o, func_00130270(o, a1), f, t);
    o->b0 = 1;
}


typedef f32 C01Mat[4][4];
typedef struct { u32 b0 : 1; u32 r : 31; } C01B32;
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u32 flags0;
    u8 pad004[0x10 - 0x4];
    f32 x10[4];
    u8 pad020[0x50 - 0x20];
    f32 x50[4];
    u8 pad060[0xd0 - 0x60];
    C01Mat xd0;
    u8 pad110[0x130 - 0x110];
    C01Sub130 *x130;
    u8 pad134[0x15c - 0x134];
    s32 x15c;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    u32 rest : 20;
    s32 x164;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    s32 x178;
    u8 pad17c[0x180 - 0x17c];
    f32 f180;
    u8 pad184[0x1cc - 0x184];
    s32 x1cc;
    u8 pad1d0[4];
    s32 *x1d4;
    u8 pad1d8[0x1f0 - 0x1d8];
    u8 x1f0[0x10];
    f32 x200[4];
    f32 x210[4];
    u8 pad220[0x230 - 0x220];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
    f32 f288;
    f32 f28c;
    f32 f290;
} __attribute__((aligned(8))) C01Obj3;

extern void *D_002E31E8;
#include "data/pieces/D_002C58A0.h"

void sceVu0CopyMatrix(C01Mat, C01Mat);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_002672f8(f32 *, C01Mat, f32 *);
s32 func_0012ffd0(C01Obj3 *);
void func_00167688(s32, s32, void *);
void func_00130898(C01Obj3 *, C01Mat);
s32 func_00130e48(C01Obj3 *, C01Mat);
void func_00130c28(C01Obj3 *, f32, f32);
void func_00130660(C01Obj3 *, C01Mat, s32, f32, f32);
void func_00130210(C01Obj3 *, s32);
void func_00130598(C01Obj3 *, C01Mat, f32, f32);
void func_001655e0(C01Mat, s32, f32, s32);
s32 func_00167680(s32);
void func_001752a0(s32, void *);
void func_001676b0(s32, f32 *);
void func_00167d70(s32, f32);

typedef struct {
    u8 pad0[0x50];
    f32 x50[4];
    u8 pad60[0x15c - 0x60];
    s32 x15c;
    u64 flags;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    u8 pad178[0x1d4 - 0x178];
    s32 *x1d4;
    u8 pad1d8[0x220 - 0x1d8];
    f32 x220[4];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
} __attribute__((aligned(8))) O660;
void func_00166248(C01Mat, s32, s32);
void func_00165cf8(C01Mat, s32, f32, s32);
void func_001676d8(s32, f32 *);
void func_002673f8(C01Mat, C01Mat);
void func_001675c0(s32);
s32 func_00167698(s32);
void func_00130648(C01Obj3 *);

/* func_00130660: closest draft (7 words off: f20/f21 swapped), context for func_00130f18. */
CONTEXT_ONLY void func_00130660(C01Obj3 *a, C01Mat m, s32 idx, f32 d, f32 e) {
    O660 *o = (O660 *)a;
    f32 v[4];
    C01Mat t;
    f32 k = D_002BBDFC * o->f284;
    s32 s = o->x1d4[idx];
    if (((s32)(o->flags >> 1) & 1) && k < e) {
        if (0.0f < o->f170) {
            func_00166248(m, o->x15c, s);
        } else {
            sceVu0CopyMatrix(t, m);
            if ((s32)(o->flags >> 12) & 1) {
                func_002675a8(t[3], o->x50);
                t[3][3] = 1.0f;
            }
            func_00165cf8(t, o->x15c, d, s);
        }
        func_001676d8(o->x15c, v);
        v[3] = 0;
        func_002673f8(t, m);
        func_002672f8(o->x270, t, v);
        o->x270[3] = 0;
        o->f170 = e;
        o->f174 = k;
        func_002675a8(v, o->x220);
        v[3] = 0;
        func_002672f8(v, o->x230, v);
        func_00267518(m[3], m[3], v);
        func_00130598(a, m, k / e, 1.0f - k / e);
    } else {
        if (0.0f < o->f170) func_001675c0(o->x15c);
        o->f170 = 0.0f;
        func_001655e0(m, o->x15c, d, s);
        o->f280 = func_00167698(s);
        if (!((s32)(o->flags >> 6) & 1)) func_00130648(a);
    }
    if (s) o->flags |= 2;
    o->x168 = idx;
    o->f16c = d;
}

void func_00130f18(C01Obj3 *o, f32 dt) {
    f32 a[4];
    f32 b[4];
    C01Mat m;
    f32 *t3;
    s32 fl;
    s32 has4;
    s32 did;
    s32 old;
    f32 d;
    f32 n;
    f32 h;

    D_002E31E8 = (u8 *)o->x130 + 0x68;
    if (o->b4) return;
    sceVu0CopyMatrix(m, o->xd0);
    if (o->b2) {
        t3 = o->x210;
        func_00267530(m[3], m[3], t3);
        m[3][3] = 1.0f;
    } else {
        t3 = o->x210;
    }
    func_002675a8(a, m[3]);
    fl = o->x1cc;
    if ((o->flags0 & 0x10) || o->b11) fl &= ~1;
    if (o->x130->x4c == 507) {
        has4 = fl & 4;
        fl &= ~4;
    } else {
        has4 = 0;
    }
    did = 0;
    func_00167688(o->x15c, func_0012ffd0(o) ? fl | 0x20 : fl, o->x1f0);
    o->b8 = 0;
    if (((s32 *)o)[0x160 / 4] & 1) {
        func_00130898(o, m);
        did = 1;
        func_00130e48(o, m);
        o->b0 = 0;
        o->b8 = 1;
    } else {
        dt *= o->f284;
        if (o->f170 > 0.0f) {
            n = o->f174 + dt;
            d = n - o->f170;
            o->f174 = n;
            if (!(d < 0.0f)) {
                func_00130c28(o, o->f16c, o->f16c + d);
                func_00130660(o, m, o->x168, o->f16c + d, 0.0f);
                func_00130210(o, o->x164);
            } else {
                h = n / o->f170;
                func_00130598(o, m, h, 1.0f - h);
            }
        } else if (!func_00130e48(o, m)) {
            h = o->f16c;
            n = h + dt;
            o->f16c = n;
            func_00130c28(o, h, n < o->f280 ? n : o->f280);
            d = o->f16c - o->f28c;
            if (d < 0.0f) {
                func_001655e0(m, o->x15c, o->f16c, o->x1d4[o->x168]);
            } else if (o->x178 > 0) {
                o->f180 += d;
                func_00130898(o, m);
                func_002675a8(a, m[3]);
                func_00130e48(o, m);
            } else {
                if (o->b2) {
                    func_00267518(m[3], m[3], t3);
                    func_002675a8(a, m[3]);
                    func_002675a8(t3, (*(f32 (*)[0x4])&D_002C58A0));
                }
                if (o->b3) {
                    func_00130660(o, m, o->x168, o->f280, 0.0f);
                } else {
                    func_00130660(o, m, o->x168, o->f288 + d, o->f290);
                    func_00130c28(o, o->f288, o->f288 + d);
                }
            }
        }
    }
    fl = o->x1cc;
    o->x1cc = func_00167680(o->x15c);
    if (fl & 1) o->x1cc |= 1;
    if (o->x1cc & 0x100000) o->flags0 &= ~0x1004;
    if (has4) {
        func_001752a0(o->x15c, o->x1f0);
        o->b10 = 1;
    } else {
        o->b10 = 0;
    }
    if (o->f170 > 0.0f) {
        func_002672f8(b, m, o->x270);
        func_00267518(o->x50, o->x10, b);
    } else {
        func_001676b0(o->x15c, o->x50);
    }
    if (o->b2 && o->f170 <= 0.0f && !did) {
        func_00267530(b, o->x50, a);
        func_00267530(o->x200, b, t3);
        func_002675a8(t3, b);
    } else {
        func_002675a8(o->x200, (*(f32 (*)[0x4])&D_002C58A0));
        func_002675a8(t3, (*(f32 (*)[0x4])&D_002C58A0));
    }
    sceVu0CopyMatrix(o->x230, m);
    func_00167d70(o->x15c, dt);
}

#include "data/types/nostrict_text_00120000_s6_05.h"
typedef struct { u8 p0[0x10]; V4D f10; } XD;
typedef struct {
    u32 b0:12;
    u32 k:2;
    u32 b14:9;
    u32 b23:1;
    u32 b24:8;
    s32 f4;
    s32 f8;
    u8 pc[4];
    V4D f10;
    u8 p20[0x30 - 0x20];
    union { u64 d; struct { u32 f30; XD *f34; } s; } u30;
    u8 p38[0x5c - 0x38];
    PD *f5c;
} AD;
typedef struct { u8 p0[5]; u8 f5; u8 p6[0x14 - 6]; f32 *f14; } ID;
typedef struct {
    u8 p0[0x10];
    V4D f10;
    u8 p20[0x30 - 0x20];
    V4D f30;
    u8 p40[0x88 - 0x40];
    u32 f88;
    u8 p8c[0x134 - 0x8c];
    ID *f134;
    u8 p138[0x370 - 0x138];
    u64 f370;
    u8 p378[0x3e0 - 0x378];
    u32 mask;
    u8 p3e4[0x3ec - 0x3e4];
    QD *head;
} BD;
typedef struct GD { u8 p0[0x88]; u32 f88; } GD;
extern QD D_005267C0[];
extern QD D_005277C0[];
QD D_005297C0 ALIGNED(64);
#include "data/pieces/D_00350CE0.h"
extern QD *func_00134f80(QD *, s32);
extern void func_00135000(BD *, QD *);
extern f32 func_00176850(void);
extern s32 func_00176578(s32, s32, s32, s32);
extern s32 func_00134ba8(AD *, BD *, u32 *);
extern void func_00121fc4(V4D *, V4D *);
QD *func_001350d8(AD *a, u32 mask, BD *b) {
    QD *q;
    u32 fl;
    GD *g;
    V4D v;
    f32 lim;
    if (mask && (b->mask & mask)) return 0;
    fl = a->u30.s.f30;
    if (((s32)(a->u30.d >> 6) & 0xf) == 9) {
        q = func_00134f80(D_005267C0, 64);
        if (q) {
            q->next = b->head;
            b->head = q;
        } else {
            q = &D_005297C0;
        }
    } else if ((b->f88 & 1) || (b->head && b->head->u8.b.n > 0)) {
        q = func_00134f80(D_005277C0, 128);
        fl |= 0x800;
        if (b->f88 & 1) fl |= 0x10000;
        if (b->head) {
            { s32 t = func_00176850() * 6.0f; fl &= 0xffff0fff; fl |= ((t + 6) & 0xf) << 12; }
        }
        if (q) func_00135000(b, q);
        else q = &D_005297C0;
        if (a->b23) {
            q->f34 = D_00350CE0;
            q->f38 = 9;
        } else if (a->f8) {
            q->f34 = a->f8;
            q->f38 = func_00176578(a->f8, 128, 1 << a->f5c->f28, 0);
        } else {
            q->f34 = 0;
        }
        if (q - D_005277C0 >= 96) {
            g = 0;
            while ((g = (GD *)func_001230a0((Ent *)g)) != 0) g->f88 &= ~1;
        }
    } else {
        q = func_00134f80(D_005267C0, 64);
        if (q) func_00135000(b, q);
        else q = &D_005297C0;
    }
    q->mask = mask;
    b->mask |= mask;
    q->k = a->k;
    q->u8.w.fc = fl;
    if (((b->f370 >> 37) & 3) == 2) q->u8.b.c0 = a->f5c->fc;

    q->u8.w.f8 = func_00134ba8(a, b, &q->u8.w.fc);
    q->f4 = (s32)a->u30.s.f34;
    q->f2c = a->f5c;
    q->f20 = -1;

    func_00267530((f32 *)&v, (f32 *)&b->f10, (f32 *)&a->f10);
    v.y = 0.0f;
    func_00121fc4(&v, &v);
    if (b->f134 && b->f134->f5) lim = b->f134->f14[3] * 0.5f;
    else lim = 0.0f;
    if (v.w <= lim) {
        if (a->u30.s.f34) {
            func_00267530((f32 *)&v, (f32 *)&b->f10, (f32 *)&a->u30.s.f34->f10);
            v.y = 0.0f;
            func_00121fc4(&q->f10, &v);
        } else {
            func_00267530((f32 *)&q->f10, (*(f32 (*)[0x4])&D_002C58A0), (f32 *)&b->f30);
        }
    } else {
        func_002675a8((f32 *)&q->f10, (f32 *)&v);
    }
    q->f10.w = 1.0f;
    return q;
}

typedef struct { u64 f0; u8 p8[8]; f32 f10[2]; f32 f18; } E39;
typedef struct { u8 p0[0x20]; f32 f20[3]; f32 f2c; f32 f30[4]; u8 p40[0x88-0x40]; u32 f88; u8 p8c[0x150-0x8c]; f32 f150; u8 p154[0x3e4-0x154]; f32 f3e4; u8 p3e8[2]; u16 f3ea; } O39;
extern s32 func_0014f600(O39 *);
extern s32 func_00130040(O39 *, s32);
extern void func_00139170(O39 *, E39 *);
extern f32 func_00267390(f32 *, f32 *);
extern s32 func_00130340(O39 *, s32, f32);
extern void *func_00130578(O39 *, s32, f32);
extern f32 atan2f(f32, f32);
extern void func_00137688(O39 *, f32);
extern void func_00138a20(O39 *, f32, f32 *);
void func_00139240(O39 *o, E39 *e, s32 k, f32 a, f32 b, f32 c) {
    f32 ang;
    if (!k) k = func_0014f600(o) ? 92 : 82;
    if (!func_00130040(o, k)) {
        func_00139170(o, e);
        return;
    }
    o->f3ea = k;
    if (func_00267390(o->f30, e->f10) < 0.0f) {
        func_00130340(o, o->f3ea | 0x1000000, 0.0f);
        func_00130578(o, o->f3ea + 1, 0.0f);
        ang = atan2f(-e->f10[0], -e->f18);
    } else {
        func_00130340(o, (o->f3ea + 5) | 0x1000000, 0.0f);
        func_00130578(o, o->f3ea + 6, 0.0f);
        ang = atan2f(e->f10[0], e->f18);
    }
    func_00137688(o, ang);
    o->f150 = ang;
    func_002675a8(o->f20, e->f10);
    o->f2c = b;
    func_00138a20(o, a, o->f20);
    if (!(o->f88 & 2)) o->f3e4 = c;
    e->f0 |= 2;
}
#include "data/data_002E.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002E3190.h"
#include "data/pieces/D_002BBDFC.h"
