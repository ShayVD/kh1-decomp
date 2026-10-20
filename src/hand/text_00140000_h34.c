/* Hand-matched functions near 0x148BC0-0x14EE00 (worker 34). */
#include "common.h"
#include "platform/math.h"
#include "data/bss_0054.h"

/* ---- shared data ---- */
extern f32 D_002BBDFC;

/* party member records (D_00304BE8->m[i], 0x74 bytes each) */
typedef struct {
    u8 lv;
    u8 hp;
    u8 hpmax;
    u8 mp;
    u8 mpmax;
    u8 pad05[0x6f];
} W34Member;
typedef struct {
    u8 pad000[4];
    W34Member m[10];
    u8 x48c;
    u8 x48d;
    u8 party[3];
} W34Save;
extern W34Save *D_00304BE8;

/* actors: x6c stats, x370 flag word */
typedef struct { u8 pad[0x3c]; s32 cur; s32 max; s32 mcur; s32 mmax; } W34St;
typedef union { u64 x; struct { u32 lo; u32 l19:19; u32 b51:1; u32 hi:12; } b; } W34F370;
typedef struct { u8 pad[0x6c]; W34St *st; u8 pad70[0x370 - 0x70]; W34F370 x370; } W34Act;
W34Act *func_00123488(u32);

/* list walker entries (func_00132040) */
typedef struct { s32 x0; u8 pad4[0x44]; s16 x48; u8 pad4a[0xe]; u8 x58; u8 x59; } W34Ent;
W34Ent *func_00132040(W34Ent *);
s32 func_00142240(s32);

/* summon/effect slots: D_0054C1B0[3] (0x20 bytes), D_0054C218[9] (0x3c bytes) */
typedef struct { u8 pad[0x4]; s32 x4; s32 x8; } W34R10;
typedef struct {
    u32 b0:1;
    u32 cnt:2;
    u32 r:29;
    s32 x4;
    s32 x8;
    s32 xc;
    W34R10 *x10;
    s32 x14;
    s32 x18;
    void (*x1c)(s32);
} W34E32;
extern W34E32 D_0054C1B0[]; /* src/data/bss_0054.c: Ent9c D_0054C1B0[0x3] */
#include "data/types/text_00140000_h34.h"
extern W34E3C D_0054C218[];
extern u32 D_0054C434;
typedef struct { u8 pad[0x4c]; u16 x4c; } W34O130;
typedef struct { u8 pad[0x130]; W34O130 *x130; u8 pad134[0x18]; W34E3C *x14c; u8 pad150[0x370 - 0x150]; u64 x370; } W34Obj;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; } W34Hdr;
W34E32 *func_00149780(s32 a);
W34E3C *func_00149810(void);
s32 func_001497c8(W34Hdr *);

/* player x148 block */
typedef struct { u8 pad[0x100]; f32 x100; u64 f:32; } W34Tm;

/* ---- callees ---- */
s32 func_00122ff8(s32);
void func_00121eb0(void *);
void func_00148a40(s32, s32);
void func_00148b70(s32, s32, s32, f32);
void func_00148b98(s32, s32, s32);
void func_00148df8(void);
void func_0011efa8(void *, void *, s32, s32);
s32 func_0011ef38(void (*f)(void));
void func_0011ef10(s32 a, void (*f)(void));
void func_00141468(W34Act *, s32);
void func_00141540(W34Act *, s32);
void func_00162110(s32, void *);
void func_00176358(s32, s32);
s32 func_00149740(s32);
void func_00162070(s32, void *, s32, s32);
void func_00162058(void *);
void func_001763f0(void *);
void func_00146928(s32);
void func_00149b40(W34E32 *);
void func_00146a68(W34Hdr *, s32, void (*)(W34E32 *), W34E32 *);
s32 func_00149c80(s32, void (*)(void));
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267810(f32 (*)[4], f32 *, f32);
void func_002672f8(f32 *, f32 (*)[4], f32 *);
f32 func_00121748(f32 *, f32 *);
f32 func_00120bf8(f32 *);
void func_0014c448();
s32 func_00130340(void *, s32, f32);
void func_00130578(void *, s32, f32);
void func_0014f658(void *, s32);
f32 func_0014cc88(void *, f32);
void func_00130398(void *, s32, f32);
f32 atan2f(f32, f32);

/* 0x148BC0 */
typedef struct { u8 pad[4]; u8 kind; u8 id; u8 pad6[2]; s32 a; f32 f; } W34T20;
typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[8]; f32 t; W34T20 *x20; } W34Tsk;
s32 func_00148bc0(W34Tsk *a) {
    W34T20 *s = a->x20;
    if (func_00122ff8(a->x10)) {
        if (!(a->t <= 0.0f)) goto dec;
        switch (s->kind) {
        case 0: func_00148a40(a->x10, s->id); break;
        case 1: func_00148b70(a->x10, s->id, s->a, s->f); break;
        case 2: func_00148b98(a->x10, s->id, s->a); break;
        }
    }
    func_00121eb0(s);
    return 4;
dec:
    a->t -= D_002BBDFC;
    return 0;
}

/* 0x148F08 */
extern W34Mdl3C D_00547C00[256];
extern W34Mdl3C *D_0054B800;
extern u8 D_0054B808[];
u8 D_0054B818[0x908] ALIGNED(8);
void func_00148f08(void) {
    s32 i;
    for (i = 0; i < 256; i++) D_00547C00[i].x14 = 0;
    D_0054B800 = D_00547C00;
    func_0011efa8(D_0054B808, D_0054B818, 36, 64);
    if (func_0011ef38(func_00148df8) == 0) func_0011ef10(0x222DF, func_00148df8);
}

/* 0x148FB0: restore HP */
s32 func_00148fb0(u32 id, s32 add) {
    W34Act *a = func_00123488(id);
    if (a) {
        if (a->st->cur < a->st->max) {
            func_00141468(a, add);
            return 1;
        }
    } else if (((id >> 16) & 0xff) == 1) {
        u32 i = id & 0xffff;
        if (i < 10) {
            W34Member *m = &D_00304BE8->m[i];
            if (m->hp < m->hpmax) {
                s32 v = m->hp + add;
                m->hp = (v < m->hpmax) ? v : m->hpmax;
                return 1;
            }
        }
    }
    return 0;
}

/* 0x149090: restore MP */
s32 func_00149090(u32 id, s32 add) {
    W34Act *a = func_00123488(id);
    if (a) {
        if (a->st->mcur < a->st->mmax) {
            func_00141540(a, add);
            return 1;
        }
    } else if (((id >> 16) & 0xff) == 1) {
        u32 i = id & 0xffff;
        if (i < 10) {
            W34Member *m = &D_00304BE8->m[i];
            if (m->mp < m->mpmax) {
                s32 v = m->mp + add;
                m->mp = (v < m->mpmax) ? v : m->mpmax;
                return 1;
            }
        }
    }
    return 0;
}

/* 0x149170: use a recovery item (needs func_00148fb0 defined above) */
typedef struct { u8 x0, x1, x2, x3, x4, x5, x6, x7; u8 pad8[0x6c]; } W34Mem8;
typedef struct { u8 pad[6]; s16 x6; } C4R;
C4R *func_00147840(s32);
s32 func_00149170(s32 a, u32 b) {
    C4R *q;
    W34Mem8 *p;
    s32 r;
    s32 v;

    q = func_00147840(a);
    p = (((b >> 16) & 0xff) == 1 && (b & 0xffff) < 10) ? (W34Mem8 *)&D_00304BE8->m[b & 0xffff] : 0;
    r = 0;
    switch (a) {
    case 1: case 2: case 6:
        if (func_00148fb0(b, q->x6)) r = 2;
        break;
    case 142:
        if (func_00148fb0(b, 9999)) r = 2;
        break;
    case 3: case 7:
        if (func_00149090(b, q->x6)) r = 4;
        break;
    case 143:
        r = func_00148fb0(b, 9999) ? 8 : 0;
        if (func_00149090(b, q->x6)) r |= 8;
        break;
    case 4: case 8: case 144:
        r = func_00148fb0(b, 9999) ? 8 : 0;
        if (func_00149090(b, 9999)) r |= 8;
        break;
    case 152:
        if (p && p->x6 < 100) {
            p->x6 = (p->x6 + q->x6 > 100) ? 100 : p->x6 + q->x6;
            r = 16;
        }
        break;
    case 153:
        if (p && p->x7 < 100) {
            p->x7 = (p->x7 + q->x6 > 100) ? 100 : p->x7 + q->x6;
            r = 32;
        }
        break;
    case 154:
        if (p && p->x5 < 100) {
            p->x5 = (p->x5 + q->x6 > 100) ? 100 : p->x5 + q->x6;
            r = 64;
        }
        break;
    }
    return r;
}

/* 0x149860 */
void func_00149860(W34Obj *o) {
    W34E3C *e = o->x14c;
    if (e) {
        s32 i = e - D_0054C218;
        W34E32 *s;
        if (e->x0) func_00162110(e->x0, e->x8);
        s = func_00149780(o->x130->x4c);
        s->cnt--;
        if (s->cnt == 1) {
            func_00176358(s->x18, s->x10->x8 - s->x10->x4);
            s->cnt = 0;
        }
        o->x14c = 0;
        D_0054C434 &= ~(1 << i);
    }
}

/* 0x1499A0 */
W34E3C *func_001499a0(W34Obj *o) {
    s32 id = o->x130->x4c;
    W34E32 *s = func_00149780(id);
    if (s) {
        if (s->x8 > 0) {
            W34E3C *e;
            o->x370 |= 1LL << 36;
            e = func_00149810();
            e->x14 = s->x18;
            e->x18 = func_00149740(id);
            e->x28 = 0;
            e->x29 = 0;
            e->x2c = 0;
            e->x0 = s->x14;
            if (e->x0) func_00162070(e->x0, e->x4, 0, 0);
            s->cnt++;
            return e;
        }
    }
    return 0;
}

/* 0x149A88 */
void func_00149a88(s32 a, s32 b, W34Hdr *h) {
    W34E32 *e = &D_0054C1B0[func_001497c8(h)];
    u8 *p = (u8 *)h + h->x8;
    u8 *q;
    if (h->xc - h->x8 > 0) {
        e->x14 = (s32)p;
        func_00162058(p);
    } else {
        e->x14 = 0;
    }
    q = (u8 *)h + h->x4;
    if (h->x8 - h->x4 > 0) {
        e->x18 = (s32)q;
        func_001763f0(q);
    } else {
        e->x18 = 0;
    }
    if (e->x1c) e->x1c(e->x4);
}

/* 0x149BD0 */
void func_00149bd0(s32 n, s32 b, W34Hdr *h) {
    s32 i = func_001497c8(h);
    if (n > 0) {
        func_00146928(-3 - i);
        func_00146a68(h, -3 - i, func_00149b40, &D_0054C1B0[i]);
    } else {
        func_00149b40(&D_0054C1B0[i]);
    }
}

/* 0x149FA0 */
extern s32 D_0054C43C;
extern void (*D_0054C438)(s32);
void func_00149fa0(void) {
    while (D_0054C43C < 3) {
        s32 c = D_00304BE8->party[D_0054C43C++];
        if (c != 0xff && func_00149c80(c, func_00149fa0)) return;
    }
    if (D_0054C438) D_0054C438(-1);
}

/* 0x14A0F0 */
typedef struct { u8 pad[0x3e0]; s32 x3e0; } W34A3e0;
typedef struct { u8 pad[0x9c]; s32 x9c; } W34A9c;
typedef struct { u8 pad[0x50]; f32 x50; s32 x54; u8 pad58[0xa4 - 0x58]; f32 xa4; } W34Tmr;
W34A3e0 *func_001230a0(W34A3e0 *);
W34A9c *func_0014a398(W34A9c *);
void func_0014a0f0(W34Tmr *a) {
    if (a->x50 > 0.0f) {
        a->xa4 += D_002BBDFC;
        if (a->x50 <= a->xa4) {
            W34A3e0 *p;
            W34A9c *q;
            for (p = 0; (p = func_001230a0(p)); ) p->x3e0 &= ~a->x54;
            for (q = 0; (q = func_0014a398(q)); ) q->x9c &= ~a->x54;
            a->xa4 -= a->x50;
        }
    }
}

/* 0x14A238 */
typedef struct { u8 pad[4]; f32 x4; f32 x8; u8 padc[4]; f32 pos[4]; } W34Fol;
typedef struct { u8 pad[0x10]; f32 pos[4]; } W34Pos;
void func_0014a238(W34Pos *a, W34Fol *b, f32 *out) {
    f32 v[4] __attribute__((aligned(16)));
    f32 y, k, t, lim;
    func_00267530(v, a->pos, b->pos);
    y = v[1];
    lim = b->x8;
    if (lim < y) y = lim;
    else { t = -lim; if (y < t) y = t; }
    t = fabsf(y / lim);
    k = (1.0f < t) ? 1.0f : t;
    k = PlatSqrtf(1.0f - k * k);
    v[1] = 0.0f;
    func_002673b8(v, v);
    func_00267560(v, v, b->x4 * k);
    v[1] = y;
    func_00267518(out, b->pos, v);
}

/* 0x14AF60 */
typedef struct { u8 pad[0x30]; f32 x30[4]; u8 pad40[0x10]; f32 x50[4]; } W34Xf;
typedef struct { u8 pad[0x60]; f32 x60; f32 x64; } W34Rng;
typedef struct {
    u64 x0;
    u8 pad8[8];
    f32 x10[4];
    u8 pad20[0x10];
    union { u64 d; struct { s32 lo; W34Xf *x34; } w; } x30;
    u8 pad38[0x24];
    W34Rng *x5c;
    u8 pad60[0x10];
    f32 x70[4];
} W34Act2;
extern f32 D_002C58D0[];
s32 func_0014af60(W34Act2 *a, W34Act2 *b) {
    f32 m[4][4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    s32 k;
    s32 r;
    if (!((s32)(b->x0 >> 6) & 1)) {
        k = (s32)(a->x0 >> 17) & 7;
        if (k == 1 || k == 3 || k == 4 || k == 2) {
            func_00267810(m, D_002C58D0, a->x5c->x60);
            func_002675a8(v, a->x30.w.x34->x30);
            v[3] = 0;
            func_002672f8(v, m, v);
            if ((s32)(b->x30.d >> 10) & 1) func_00267530(d, b->x70, b->x10);
            else func_00267530(d, b->x30.w.x34->x50, a->x30.w.x34->x50);
            if (func_00121748(v, d) < a->x5c->x64) { r = 0; return r; }
            r = 1;
        } else r = 1;
    } else r = 1;
    return r;
}

/* 0x14C5C8 */
typedef struct { u8 pad[4]; s32 x4; } W34Pad;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 pad40[0x148 - 0x40]; W34Tm *x148; } W34Pl;
void func_0014c5c8(W34Pl *o, W34Pad *b, f32 *v) {
    s32 m;
    if (v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f) {
        func_002675a8(v, o->pos);
        v[3] = 0.0f;
    }
    if (o->x148->x100 > 0.0f) {
        o->x148->x100 -= D_002BBDFC;
    } else {
        if (o->x148->f & 1) m = b->x4 & 0x10;
        else m = b->x4 & 4;
        if (!m) func_0014c448(o, b->x4);
    }
}

/* 0x14CA38 */
typedef struct { s32 x0; u8 pad4[0xc]; f32 x10[4]; u8 pad20[0x50]; s32 x70; u8 pad74[0x148 - 0x74]; W34Tm *x148; u8 pad14c[0x490 - 0x14c]; f32 x490[4]; } W34Pl2;
extern u32 D_002C5958;
extern f32 D_0054F444;
s32 func_0014db20(W34Pl2 *);
s32 func_0014ca38(W34Pl2 *o, s32 a) {
    f32 v[4] __attribute__((aligned(16)));
    if ((D_002C5958 >> 5 & 1) && func_0014db20(o)) {
        o->x0 &= ~4;
        return 8;
    }
    if (!a) goto call;
    if (o->x148->x100 <= 0.0f) {
        func_00267530(v, o->x10, o->x490);
        if (v[1] < 0.0f) {
        call:
            func_0014c448(o);
        } else if (func_00120bf8(v) / D_0054F444 < 0.7f) func_0014c448(o);
    }
    return o->x70;
}

/* 0x14CB90 */
extern u32 D_002E27C8;
typedef struct { u32 x0; u8 pad4[0x144]; W34Tm *x148; u8 pad14c[0x3b0 - 0x14c]; f32 x3b0; u8 pad3b4[0x3d0 - 0x3b4]; s32 x3d0; } W34Pl3;
s32 func_0014cb90(W34Pl3 *o) {
    s32 r;
    if (o->x0 & 0x2000) o->x3d0 = 171;
    else if (D_002E27C8 >> 9 & 1) o->x3d0 = 5;
    else o->x3d0 = 0;
    r = func_00130340(o, (o->x3d0 + 4) | 0x10000, 0.0f);
    func_0014f658(o, 1);
    o->x3b0 = 0.0f;
    o->x148->x100 = 0.0f;
    return r;
}

/* 0x14D070 */
typedef struct {
    u8 pad[0x70];
    s32 x70;
    u8 pad74[0x2a0 - 0x74];
    f32 x2a0[4];
    u8 pad2b0[0x20];
    s32 x2d0;
    u8 pad2d4[0xc];
    f32 x2e0[4];
    u8 pad2f0[0x3b4 - 0x2f0];
    f32 x3b4;
    u8 pad3b8[0x3c4 - 0x3b8];
    f32 x3c4;
    u8 pad3c8[8];
    s32 x3d0;
} W34Pl4;
void func_0014d070(W34Pl4 *o, f32 *b) {
    f32 v[4] __attribute__((aligned(16)));
    func_00267530(v, o->x2e0, o->x2a0);
    if (b[1] < v[1]) {
        switch (o->x70) {
        case 2:
            o->x3b4 += v[1] - b[1];
            if (b[1] < 0.0f && (o->x2d0 & 8)) {
                func_0014cc88(o, 0.0f);
                o->x3b4 = o->x2e0[1];
                func_00130340(o, o->x3d0 + 5, 6.0f);
                func_00130578(o, o->x3d0 + 6, 0.0f);
            }
            break;
        case 3:
            if (b[1] < 0.0f && (o->x2d0 & 8)) o->x3c4 = 0.0f;
            break;
        }
    }
}

/* 0x14D210 */
typedef struct { u32 x0; u8 pad4[0x1c]; f32 x20[4]; u8 pad30[0x150 - 0x30]; f32 x150; u8 pad154[0x10]; s32 x164; } W34Pl5;
extern s32 D_002C5C54;
s32 func_0014d180(W34Pl5 *);
s32 func_00140370(W34Pl5 *, f32 *);
s32 func_0013f618(W34Pl5 *, f32 *);
s32 func_0015cc48(W34Pl5 *, f32 *);
s32 func_001507d0(W34Pl5 *, f32 *);
s32 func_00144510(W34Pl5 *, f32 *);
void func_0014d210(W34Pl5 *o, f32 *v) {
    if (!(o->x0 & 0x2000) && func_0014d180(o)) {
        if (func_00140370(o, v)) return;
        if (func_0013f618(o, v)) return;
        if (!D_002C5C54 && func_0015cc48(o, v)) return;
        if (func_001507d0(o, v)) return;
    }
    if (func_00144510(o, v)) return;
    if (v[3] > 0.0f && !(o->x0 & 0x400)) {
        o->x150 = atan2f(v[0], v[2]);
        if (o->x164 == 220) func_00130398(o, 6, 8.0f);
    }
    func_002675a8(o->x20, v);
}

/* 0x14E400 */
typedef struct { u8 pad[0x100]; union { u64 x; struct { u32 lo; u32 l2:2; u32 b34:1; u32 hi:29; } b; } x100; } W34T148b;
typedef struct {
    u8 pad[0x130];
    W34O130 *x130;
    u8 pad134[0x14];
    W34T148b *x148;
    u8 pad14c[0x370 - 0x14c];
    union { u64 x; struct { u32 lo; u32 l28:28; u32 b60:1; u32 hi:3; } b; } x370;
    u8 pad378[0x3cc - 0x378];
    f32 x3cc;
} W34Pl6;
void func_0014e3a0(W34Pl6 *);
s32 func_0014e400(W34Pl6 *o, s32 a) {
    W34T148b *t = o->x148;
    if ((t && t->x100.b.b34) || o->x3cc <= 0.0f || a) {
        if (t) t->x100.x &= ~(1LL << 34);
        return 8;
    }
    if (o->x130->x4c == 8) return 8;
    if (o->x370.b.b60) return 8;
    func_0014e3a0(o);
    return 2;
}

/* 0x14E510 */
s32 func_0014e510(s32 key) {
    W34Ent *p = 0;
    s32 n = 0;
    while ((p = func_00132040(p))) {
        if (p->x58 == key) {
            W34Act *a = func_00123488(p->x0);
            if (!a) {
                if (func_00142240(p->x0) != 1) n++;
            } else if (!a->x370.b.b51) n++;
        }
    }
    return n;
}

/* 0x14E5B8 */
typedef struct { union { u64 x; u8 id; } f; u8 pad8[8]; f32 mn[4]; f32 mx[4]; } W34Box;
typedef struct { u8 pad[4]; u8 n; u8 pad5[0xb]; W34Box box[1]; } W34Boxes;
extern W34Boxes *D_00350D78;
s32 func_0014e5b8(f32 *p) {
    W34Box *b;
    s32 m, n, i;
    if (!D_00350D78) return 0;
    n = D_00350D78->n;
    b = D_00350D78->box;
    m = 0;
    for (i = 0; i < n; i++, b++) {
        if ((b->f.x & 0x200) || (p[0] >= b->mn[0] && p[0] <= b->mx[0] && p[2] >= b->mn[2] && p[2] <= b->mx[2]))
            m |= 1 << (b->f.id - 1);
    }
    return m;
}

/* 0x14EC60 */
typedef struct { s32 x0; s32 x4; f32 x8; f32 xc; s32 x10; s32 x14; } W34Grp;
extern W34Grp D_0054F450[]; /* src/data/bss_0054.c: Grp57_f1b8 D_0054F450[0x1f] */
void func_0014ec60(s32 g) {
    W34Grp *e = &D_0054F450[g - 1];
    s32 n = 0;
    W34Ent *p = 0;
    while ((p = func_00132040(p))) {
        if (p->x58 == g && e->x14 >= p->x48 && func_00142240(p->x0) != 1) n += p->x59;
    }
    if (e->x10 >= n) e->x14++;
}

/* 0x14ED30 (calls func_0014ec60 above) */
extern W34Grp D_0054F438[];
extern s32 D_0054F448;
typedef struct { u8 pad[0x58]; u8 x58; } W34O130b;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x128]; W34O130b *x130; u8 pad134[0x370 - 0x134]; W34F370 x370; } W34Act4;
void func_001421d0(s32, s32);
void func_0014ed30(W34Act4 *o) {
    s32 i;
    if (o->x370.b.b51) {
        if (o->x130->x58) {
            if (!(D_0054F438[o->x130->x58].x0 & 1)) func_001421d0(o->x4, 1);
            func_0014ec60(o->x130->x58);
        } else {
            func_001421d0(o->x4, 1);
        }
    }
    for (i = 0; i < 31; i++) {
        if (D_0054F448 >> i & 1) D_0054F450[i].xc = D_0054F450[i].x8;
    }
}
#include "data/data_002C.h"
