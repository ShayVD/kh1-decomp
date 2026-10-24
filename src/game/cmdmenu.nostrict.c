/* The command menu (a guess from the code): the command lists in D_002E2FD8
 * (func_0012cb78 / func_0012cc38 add an entry, func_0012cb40 sets one), the
 * submenu stack D_00524F40 over D_002E3170 (func_0012dce0 pushes,
 * func_0012dd38 pops), the pad input func_0012e1b0, the choice func_0012dea0
 * (an entry's record from func_001478c8; a beep through func_0011d768 when
 * it is greyed out), the per-frame update func_0012e4b0; then the action
 * command: its target and kind D_002E31B0 / D_002E31B8 (func_0012fb20 sets
 * them, func_0012fc20 clears, func_0012f868 picks the nearest target) and
 * the range test func_0012fa98. Flag mode: nostrict (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350D88.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E2780.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/types/nostrict_text_00120000_h54.h"
#include "data/pieces/D_00304B78.h"
#include "data/types/nostrict_text_00120000_s6_05_p.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002C5960.h"

/* func_0012ca38 (from hand/nostrict/text_00120000_s6_05.c). */
typedef Q8_2e3170 Q8;
extern Q8 D_002E2FD8[7];
extern Q8 **D_00524F40;
void func_0012ca38(void) {
    s32 i;
    for (i = 7; i >= 0; i--) D_002E3170[i] = 0;
    D_00524F40 = D_002E3170;
    D_002E3170[0] = D_002E2FD8;
    D_002E319C = D_002E31A0 = 0;
    D_002E2FD8[0].fc = 0;
}

/* func_0012cd10 (from hand/nostrict/text_00120000_cc.c). */
typedef struct { u8 pad[0x44]; f32 r; u8 pad48[0x16]; u8 kind; } CdInfo;
typedef struct Actor_2cd10 {
    u8 pad[0x10];
    f32 pos[4];
    u8 pad20[0x10];
    f32 dir[4];
    u8 pad40[0x98 - 0x40];
    struct Actor_2cd10 *f98;
    u8 pad9c[0x130 - 0x9c];
    CdInfo *info;
} E15;
void func_00267530(f32 *, f32 *, f32 *);
void func_00121fc4(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00120bf8(f32 *);
void func_0012ec88(E15 *, f32 *);
f32 func_00267390(f32 *, f32 *);
/* func_0012cf48 only matches with its callee func_0012cd10 defined above it. */
s32 func_0012cd10(E15 *o, E15 *t) {
    f32 d[4];
    f32 ay, k;
    switch (o->info->kind) {
    case 0:
        func_00267530(d, o->pos, t->pos);
        ay = fabsf(d[1]);
        d[1] = 0.0f;
        func_00121fc4(d, d);
        if (d[3] < o->info->r) {
            if (ay < o->info->r) {
                k = 1.0f - func_00267390(t->dir, d);
                if (k < 1.0f) return d[3] + d[3] * k * 0.5f;
            }
        }
        break;
    case 1:
        func_00267530(d, o->pos, t->pos);
        if (fabsf(d[1]) < o->info->r) {
            if (func_00120c18(d) < o->info->r) return 0;
        }
        break;
    case 2:
        func_0012ec88(o, d);
        func_00267530(d, d, t->pos);
        if (func_00120bf8(d) < o->info->r) {
            d[1] = 0.0f;
            func_00121fc4(d, d);
            k = 1.0f - func_00267390(t->dir, d);
            return d[3] + d[3] * k * 0.5f;
        }
        break;
    case 3:
        func_00267530(d, o->pos, t->pos);
        d[1] = 0.0f;
        func_00121fc4(d, d);
        if (d[3] < o->info->r) {
            k = 1.0f - func_00267390(t->dir, d);
            if (k < 1.0f) return d[3] + d[3] * k * 0.5f;
        }
        break;
    }
    return -1;
}

/* func_0012cf48 (from hand/nostrict/text_00120000_cc.c). */
typedef struct Actor_2cf48 {
    u8 pad[0x10];
    f32 pos[4];
    u8 pad20[0x10];
    f32 dir[4];
    u8 pad40[0x98 - 0x40];
    struct Actor_2cf48 *f98;
    u8 pad9c[0x130 - 0x9c];
    CdInfo *info;
} E15_2cf48;
typedef struct { s32 d; E15_2cf48 *e; } P15;
extern s32 func_00122ff8();
extern s32 func_00122fd0(E15_2cf48 *);
extern E15_2cf48 *func_001230a0(E15_2cf48 *);
extern void func_00250360(void *, s32, s32, void *);
extern s32 func_0012cf38();
/* func_0012cf48 only matches with its callee func_0012cd10 defined above it. */
s32 func_0012cf48(E15_2cf48 *e, P15 *out) {
    s32 n = 0;
    s32 d;
    P15 *p;
    E15_2cf48 *it;
    if (D_002E31B8 >= 3) {
        if (func_00122ff8(D_002E31B0.f0)) {
            if (func_0012cd10(D_002E31B0.f0, e) >= 0) {
                out->d = 0;
                n = 1;
                out->e = D_002E31B0.f0;
            }
            goto done;
        }
    }
    it = 0;
    while ((it = func_001230a0(it)) != 0) {
        if (it != e && it != e->f98 && func_00122fd0(it)) {
            d = func_0012cd10(it, e);
            if (d >= 0) {
                out[n].d = d;
                out[n].e = it;
                n++;
            }
        }
    }
    func_00250360(out, n, 8, func_0012cf38);
done:
    return n;
}

/* func_0012d188 (from hand/nostrict/text_00120000_h54.c). */
extern Q5 D_002E3010;
extern L5 D_002E3080;
extern u32 D_002C5958;
extern void func_0013ab08() __attribute__((weak));
extern void func_0012cb40(Q5 *, s32, s32);
extern s32 func_0013a910(s32);
void func_0012d188(s32 a0, u32 *a1) {
    s32 buf[7];
    s32 n, i, m;
    Q5 *q = &D_002E3010;
    L5 *l;
    if (func_0013ab08 && ((*(u32 *)&D_00304B78) >> 3 & 1)) {
        func_0012cb40(q, q->n++, 79);
        return;
    }
    l = &D_002E3080;
    n = 0;
    m = -1;
    for (i = 0; i < 7; i++) {
        s32 v = D_00304BE8->x7d0[i];
        if (v != -1) {
            l->ids[n] = v + 47;
            buf[n] = v;
            if (func_0013a910(v)) m &= ~(1 << n);
            n++;
        }
    }
    l->n = n;
    if (n > 0) {
        n = q->n++;
        func_0012cb40(q, n, 6);
        if ((D_00304BE8->f874 & 4) || (D_002C5958 >> 13 & 1) || (D_002E31A8 >> 1 & 1)) {
            q->f4 |= 1 << n;
            q->f8 |= 1 << n;
        } else if (m == -1) {
            q->f4 |= 1 << n;
        }
    }
    l->f8 = m;
    l->f4 = m;
}

/* func_0012d6c0 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { u8 pad[0x21]; u8 n; u8 f22[1]; } T7;
typedef struct { u8 pad[0xc8]; T7 *fc8; } U7;
typedef struct { u8 pad[0x6c]; U7 *f6c; } A7;
extern void func_0012ccb0(s32);
extern Q38 D_002E2FD8_0012d6c0[7] __asm__("D_002E2FD8");
#define D_002E2FD8 D_002E2FD8_0012d6c0
void func_0012d6c0(A7 *a0, u32 *a1) {
    Q38 *g;
    Q38 *p;
    T7 *t;
    s32 m, cnt, i;
    if (D_00304BE8->f874 & 0x10) return;
    g = D_002E2FD8;
    func_0012cb40((Q5 *)g, 2, 3);
    p = &g[2];
    p->f8 = 0;
    m = -1;
    p->f4 = 0;
    i = 0;
    t = a0->f6c->fc8;
    cnt = 0;
    for (; i < t->n; i++) {
        if (t->f22[i]) {
            D_00524F68[cnt] = i;
            m &= ~(1 << cnt);
            p->ids[cnt] = t->f22[i] + 30;
            cnt++;
        }
    }
    p->n = cnt;
    if (cnt > 0) {
        if (!(p->fc < cnt)) p->fc = cnt - 1;
        if (!(D_00304BE8->f874 & 2)) {
            if (!(*a1 >> 6 & 1)) {
                m = -1;
                g->f4 |= 4;
            }
            p->f8 = m;
            p->f4 = m;
            return;
        }
    }
    do { func_0012ccb0(2); } while (0);
}
#undef D_002E2FD8

/* func_0012d930 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct T23 { u8 b0; u8 pad[19]; } T23;
typedef struct Info { u8 pad[4]; u32 f4; u8 pad8[0x57]; u8 f5f; } Info;
typedef struct Info2 { u8 pad[7]; u8 f7; u8 pad8[0x14]; T23 *f1c; } Info2;
typedef struct Actor_2d930 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2d930 *f98;
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
typedef S31b0_2e31b0 V8;
typedef struct Hit { s32 f0; Ent *e; } Hit;
extern u32 D_00524F44;
extern void (*D_00524F74)(void);
extern void func_0012fc58(void);
extern s32 func_00137330(Ent *, Ent *, s32);
extern Hit *func_00122048(s32, s32);
extern void func_001220b8(Hit *);
extern void func_00245238(s32, Ent *);
extern void func_0012fb20(V8 *, s32);
extern void func_00158960(void);
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
#define func_0012cf48 ((s32 (*)(Ent *, Hit *)) func_0012cf48)
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
    tmp.f0 = 0;
    tmp.f4 = 0;
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
                    tmp.f0 = e;
                    m = 0;
                    k = pl->f70;
                    if (k && k != 24 && k != 8) func_0012ccb0(0);
                }
                break;
            case 2:
                if (func_0012cc38(3, 5)) {
                    m = 1;
                    tmp.f0 = e;
                    if ((D_002C5958 & 1) || ((k = pl->f70) && k != 24 && k != 8)) func_0012ccb0(3);
                }
                break;
            case 3: {
                u32 *fq = &D_00524F44;
                old = *fq;
                func_00137330(e, pl, -1);
                if (*fq != old) {
                    tmp.f0 = e;
                    m = 1;
                }
                break;
            }
            case 4:
                if (func_0012cc38(0, 1)) {
                    tmp.f0 = e;
                    m = 0;
                }
                break;
            }
            if (tmp.f0) break;
        }
        func_001220b8(h);
    }
    if (tmp.f0) {
        func_00245238(m, pl);
        if (D_002E31B8 < 3) func_0012fb20(&tmp, 1);
        if ((D_002C5958 >> 13) & 1) func_0012ccb0(3);
    }
    func_00158960();
}
#undef func_0012cf48

/* func_0012dd70 (from hand/nostrict/text_00120000_s6_05.c). */
typedef O8_2e319c O8;
typedef struct Actor_2dd70 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2dd70 *f98;
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
} Ent_2dd70;
extern s32 func_00130030(Ent_2dd70 *);
extern s32 func_001443a8(Ent_2dd70 *);
extern s32 func_0013db30(Ent_2dd70 *);
s32 func_0012dd70(O8 *o) {
    Ent_2dd70 *p = D_002E26A0[0];
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

/* func_0012e4b0 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct Actor_2e4b0 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2e4b0 *f98;
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
} Ent_2e4b0;
extern s32 D_00524F48;
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
extern St3190 D_002E3190;
extern Pad D_002C5BB0;
extern s32 D_002E27A8;
extern void *memset(void *, s32, u32);
extern void func_0012dc70(void);
extern s32 func_001375d8(Ent_2e4b0 *);
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
#define func_00122ff8 ((s32 (*)(Ent_2e4b0 *)) func_00122ff8)
s32 func_0012e4b0(void) {
    Ent_2e4b0 *e;
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
    if (!func_00122ff8(D_002E31B0.f0)) func_0012fc58();
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
#undef func_00122ff8

/* func_0012ea38 (from hand/nostrict/text_00120000_s6_05.c). */
extern void func_0012e970(void);
extern s32 func_0011ef38(void *);
extern void func_0011ef10(s32, void *);
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

/* func_0012f040 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct Actor_2f040 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2f040 *f98;
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
} Ent_2f040;
CONTEXT_ONLY s32 func_00122ff8(Ent_2f040 *o) {
    s32 r = 0;
    if (o) {
        if ((o->f370 & 0x300000000) == 0x100000000) r = 1;
    }
    return r;
}
s32 func_0012f040(Ent_2f040 *o, s32 i) {
    Info2 *in;
    if (!func_00122ff8(o) || ((u32)(o->f370 >> 47) & 1) || (o->f0 & 0x200)) return 0;
    if (i >= 0) {
        in = o->f134;
        if (!in) return 1;
        if (in->f7 && !(in->f1c[i].b0 & 0xf) && (o->f3ac & (1 << i))) return 0;
    }
    return 1;
}

/* func_0012f3d0 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct Actor_2f3d0 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2f3d0 *f98;
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
} Ent_2f3d0;
extern V8 D_00524F80[];
extern void func_001315c0(Ent_2f3d0 *, s32, f32 *, f32);
extern s32 func_0012f0f8(f32 *, f32 *, s32);
extern s32 func_0012eaf8(Ent_2f3d0 *);
extern f32 func_0012ec60(Ent_2f3d0 *, s32, f32 *);
typedef union { u64 x; struct { u32 lo0; u32 x32:3; u32 f35:1; u32 x36:1; u32 kind:2; u32 hi:25; } b; } F370b;
typedef struct { u8 pad[0x370]; F370b f370; } E9;
CONTEXT_ONLY s32 func_0012f218(f32 *pos, V8 *a, s32 lim) {
    f32 tmp[4];
    f32 d[4];
    f32 r;
    s32 s, v;
    r = func_0012ec60(a->f0, a->f4, tmp);
    func_00267530(d, tmp, pos);
    r = func_00120bf8(d) - r;
    if (func_0012eaf8(a->f0) && r > 1200.0f) return -1;
    s = r;
    if (!(r > 0.0f)) s = 0;
    if (D_002E319C) {
        switch (((E9 *)a->f0)->f370.b.kind) {
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
    if (((E9 *)a->f0)->f370.b.f35 && func_0012f0f8(&D_002E2780.x, tmp, 0)) return s;
    if (!func_0012f0f8(pos, tmp, 0)) return -1;
    if (func_0012eaf8(a->f0)) s |= 0x10000;
    return s;
}
CONTEXT_ONLY s32 func_0012ee70(Ent_2f3d0 *e, s32 i) {
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
#define func_001230a0 ((Ent_2f3d0 *(*)(Ent_2f3d0 *)) func_001230a0)
void func_0012f3d0(V8 *out) {
    f32 pos[4];
    V8 cur;
    Ent_2f3d0 *pl = D_002E26A0[0];
    s32 n = D_0052528C;
    V8 *tbl = D_00524F80;
    s32 best = -1;
    s32 i, r;

    func_001315c0(pl, 0x8003, pos, 0.0f);
    out->f0 = 0;
    cur.f0 = 0;
    while ((cur.f0 = func_001230a0(cur.f0)) != 0) {
        if (cur.f0 == pl) continue;
        if (cur.f0 == pl->f98) continue;
        if (!func_0012f040(cur.f0, -1)) continue;
        cur.f4 = -1;
        while ((cur.f4 = func_0012ee70(cur.f0, cur.f4)) >= 0) {
            for (i = 0; i < n; i++) {
                if (tbl[i].f0 == cur.f0 && tbl[i].f4 == cur.f4) break;
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
#undef func_001230a0

/* func_0012f868 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct Actor_2f868 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2f868 *f98;
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
} Ent_2f868;
extern s32 func_00123368(Ent_2f868 *);
extern f32 func_0012ed88(Ent_2f868 *, V8 *, f32 *, f32 *);
extern f32 func_00121b38(f32 *, f32 *);
extern float fabsf(float);
#define func_0012ee70 ((s32 (*)(Ent_2f868 *, s32)) func_0012ee70)
#define func_001315c0 ((void (*)(Ent_2f868 *, s32, f32 *, f32)) func_001315c0)
#define func_001230a0 ((Ent_2f868 *(*)(Ent_2f868 *)) func_001230a0)
void func_0012f868(V8 *out) {
    V8 cur;
    f32 pos[4];
    f32 b[4];
    f32 c[4];
    Ent_2f868 *pl = D_002E26A0[0];
    f32 best = -1.0f;
    f32 d, t;

    func_001315c0(pl, 0, pos, 1.0f);
    cur.f0 = 0;
    out->f0 = 0;
    while ((cur.f0 = func_001230a0(cur.f0)) != 0) {
        if (((((Ent_2f868 *)cur.f0)->f370 >> 37) & 3) != 2 && !(((Ent_2f868 *)cur.f0)->f130->f4 & 0x8000)) continue;
        if (!func_00123368(cur.f0)) continue;
        if (!func_0012f040(cur.f0, -1)) continue;
        cur.f4 = -1;
        while ((cur.f4 = func_0012ee70(cur.f0, cur.f4)) >= 0) {
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
#undef func_0012ee70
#undef func_001315c0
#undef func_001230a0

/* func_0012fcd0 (from hand/nostrict/text_00120000_s6_05.c). */
typedef struct Actor_2fcd0 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0x24];
    struct Actor_2fcd0 *f98;
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
} Ent_2fcd0;
extern s32 D_002E31BC;
extern f32 D_00524F78;
extern f32 D_002BBDFC;
extern u32 D_002C5BB8;
extern V8 *D_00525288;
extern s32 func_00219288(void);
extern void func_0017eff8(void);
extern void func_0012fc20(void);
extern void func_00123030(Ent_2fcd0 *, s32, s32);
CONTEXT_ONLY s32 func_0012eb08(V8 *p) {
    f32 a[4];
    f32 b[4];
    if (!func_0012f040(D_002E31B0.f0, D_002E31B0.f4)) return 1;
    if (func_0012eaf8(p->f0)) {
        if (func_0012ed88(D_002E26A0[0], p, a, b) > 1500.0f) return 1;
        if (fabsf(b[1]) > 1000.0f) return 1;
    }
    return 0;
}
CONTEXT_ONLY void func_0012fa98(void) {
    f32 a[4];
    f32 b[4];
    f32 d = func_0012ed88(D_002E26A0[0], &D_002E31B0, a, b);
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
s32 func_0012fcd0(void) {
    Ent_2fcd0 *pl = D_002E26A0[0];
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
        if (func_0012eb08(&D_002E31B0)) func_0012fc58();
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
            if (func_0012f040(src->f0, src->f4) && !func_0012eb08(src)) {
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
        if (!func_0012f040(D_002E31B0.f0, D_002E31B0.f4)) func_0012fc58();
        break;
    case 0:
    case 2:
        if (func_00219288() != 1 && D_002E319C && (D_002E319C->f0 & 4)) {
            func_0012f868(&tmp);
            if (tmp.f0) func_0012fb20(&tmp, 2);
        }
        break;
    case 4:
        break;
    }
    if (D_002E31B8 >= 3) func_0012fa98();
    return 0;
}

