#include "common.h"
#include "data/pieces/D_002E31B0.h"
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

typedef S31b0_2e31b0 V8;

/* ---- data ---- */
extern Node D_004F8310[64];
extern Q8 D_002E2FD8[7];
extern Q8 **D_00524F40; /* src/data/bss_0052.c: void **D_00524F40 */
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31B8.h"
extern s32 D_002E31BC;
extern u32 D_00524F44;
extern f32 D_002BBDFC;
#include "data/pieces/D_002E2780.h"

/* ---- functions ---- */
extern void func_0012cb40(Q8 *, s32, u8);
extern void func_0012fc58(void);
extern s32 func_0012ee70(Ent *, s32);
extern f32 func_0012ed88(Ent *, V8 *, f32 *, f32 *);
extern s32 func_0012f0f8(f32 *, f32 *, s32);
extern s32 func_0012eaf8(Ent *);
extern f32 func_0012ec60(Ent *, s32, f32 *);
extern f32 func_00120bf8(f32 *);
extern void func_00267530(f32 *, f32 *, f32 *);
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

#include "data/types/nostrict_text_00120000_s6_05_p.h"
typedef struct { u32 x0; u32 x4; u32 x8; } Pad;
extern s32 func_00122ff8(Ent *);
extern s32 func_0012e1b0(Pad *);
extern O8 *func_001478c8(s32);
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

CONTEXT_ONLY s32 func_00122ff8(Ent *o) {
    s32 r = 0;
    if (o) {
        if ((o->f370 & 0x300000000) == 0x100000000) r = 1;
    }
    return r;
}

/* func_0012f218 (src/hand/nostrict_nofill/text_00120000_h54.c). */
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

/* func_0012eb08, func_0012fa98 (src/hand/text_00120000_h5.c), func_0012fc58 (src/auto). */
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

/* rodata: jump tables at 0x48d550, 0x48d570 */
extern s32 func_00167698(s32);

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

void sceVu0CopyMatrix(C01Mat, C01Mat);
void func_00267530(f32 *, f32 *, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_002672f8(f32 *, C01Mat, f32 *);
void func_00130660(C01Obj3 *, C01Mat, s32, f32, f32);
void func_00130598(C01Obj3 *, C01Mat, f32, f32);
void func_001655e0(C01Mat, s32, f32, s32);

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

#include "data/types/nostrict_text_00120000_s6_05.h"
QD D_005297C0 ALIGNED(64);
#include "data/data_002E.h"
#include "data/pieces/D_002BBDFC.h"
