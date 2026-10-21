#include "common.h"

typedef struct Prm {
    s32 x0;         /* 0x00 */
    u8 pad4[0x10];
    f32 x14;        /* 0x14 */
    f32 x18;        /* 0x18 */
    f32 x1c;        /* 0x1C */
    f32 x20;        /* 0x20 */
} Prm;
typedef struct { u8 pad[0xc]; Prm *xc; } P160;
typedef struct P40 {
    u64 b0:2;
    u64 b2:2;
    u64 rest:60;
    u8 pad8[0x50 - 8];
    f32 x50;
} P40;

typedef struct Ob {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[4];
    s32 x54;        /* 0x54 */
    u8 pad58[0x68 - 0x58];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x160 - 0x6c];
    P160 *x160;     /* 0x160 */
    s32 x164;       /* 0x164: sub-state */
} Ob;

typedef struct Wk {
    u8 pad0[0x70];
    s32 x70;
    u8 pad74[0x144 - 0x74];
    Ob *x144;       /* 0x144 */
} Wk;

typedef struct { f32 x, y, z, w; } V4;
typedef struct Prm2 {
    s32 x0;
    f32 x4, x8, xc, x10, x14, x18, x1c, x20;
} Prm2;
typedef struct { u8 pad[0xc]; Prm2 *xc; } Q160;
typedef struct Ac {
    u8 pad0[0x38];
    union { u64 d; s32 w; } flags; /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    s32 x48;        /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[4];
    s32 x54;        /* 0x54 */
    u8 pad58[0x68 - 0x58];
    f32 x68;        /* 0x68 */
    u8 pad6c[0x90 - 0x6c];
    s32 x90;        /* 0x90 */
    u8 pad94[0x9c - 0x94];
    f32 x9c, xa0;   /* 0x9C */
    u8 pada4[0xcc - 0xa4];
    f32 xcc;        /* 0xCC */
    V4 xd0;         /* 0xD0 */
    u8 pade0[0x120 - 0xe0];
    V4 x120;        /* 0x120 */
    u8 pad130[0x160 - 0x130];
    V4 x160;        /* 0x160 */
} Ac;
typedef struct Wk2 {
    u8 pad0[0x30];
    V4 x30;
    u8 pad40[0x70 - 0x40];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    u64 x90;
} Wk2;

typedef struct Task { u8 pad[0xc]; void *cb; } Task;
typedef struct Prm3 {
    s32 x0;
    f32 x4, x8, xc, x10, x14, x18, x1c, x20, x24;
} Prm3;
typedef struct { u8 pad[0xc]; Prm3 *xc; } R160;
typedef struct Ac3 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    void *x48;      /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x90 - 0x50];
    s32 x90;        /* 0x90 */
    u8 pad94[0x164 - 0x94];
    f32 x164;
    u8 pad168[0x170 - 0x168];
    R160 *x170;
    s32 x174;
    s32 x178;
} Ac3;
typedef struct Wk3 {
    u8 pad0[0x14];
    f32 x14;
} Wk3;

typedef struct Ac4 {
    u8 pad0[0x38];
    u64 flags;      /* 0x38 */
    P40 *x40;       /* 0x40 */
    u8 pad44[4];
    void *x48;      /* 0x48 */
    s32 x4c;        /* 0x4C */
    u8 pad50[0x90 - 0x50];
    s32 x90;
    u8 pad94[0x160 - 0x94];
    R160 *x160;
    s32 x164;
} Ac4;

s32 func_0016dd30(Wk *, Ob *, P160 *, s32);
void func_0013df40(Wk *, s32);
f32 func_00171aa8(f32, f32);
s32 func_00171ae8(Wk *, Ob *);
s16 *func_00171b80(Wk *, Ob *, s32);
void func_0014a0f0(P40 *);
s32 func_00171a88(Wk3 *, void *, s32);
s32 func_0016b670(Wk3 *, void *, R160 *, s32);
s32 func_00130340(Wk3 *, s32, f32);
Task *func_00130578(Wk3 *, s32, f32);
void func_001731f8(void);
void func_00148a40(Wk3 *, s32);
void func_00170f90(void);
extern u8 D_0035BE40[];
void func_00170fa8(Wk3 *, void *, void *, void *, f32);
s32 *func_0013dbe0(Wk3 *, s32);
s32 *func_001477c8(s32);
void func_001412f8(Wk3 *, s32);
void func_00173610(void);
void func_001734f8(void);
void func_00170f50(Wk3 *, void *, void *, s32, s32);
void func_001740e8(void);
extern u8 D_0035C1E0[];
void func_001742b0(void);
void func_001741a0(void);
void func_00174ad8(void);
extern u8 D_0035C350[];
void func_00174ca8(void);
void func_00174b90(void);
typedef struct Ppp {
u8 pad0[0x88];
s32 x88;
u8 pad8c[0x93 - 0x8c];
u8 x93;
void *x94;
s32 x98;
u8 pad9c[0xa8 - 0x9c];
s32 xa8;
} Ppp;
typedef struct Obj3C {
void *x0, *x4, *x8, *xc, *x10;
s32 x14;
void *x18, *x1c, *x20, *x24, *x28, *x2c;
s32 x30;
void *x34;
} Obj3C;
extern s32 D_0035C6F8;
extern s32 D_0035C6FC;
void func_00181fe0(Ppp **);
s32 func_00181410(s32);
void func_001803f0(s32, s32, s32 *, Ppp *);
s32 func_00181318(void);
s32 func_00181368(s32);
void func_00182c10(Ppp *, s32, s32);
void func_00182840(Ppp *);
#include "data/types/nostrict_text_00170000_h61.h"
extern T44 D_005757B0[];
extern f32 D_002BBDFC;
extern u8 D_002C5AD2[][112];
void func_00176ba8(H20 *, s32);
void func_00176c60(s32);

s32 func_00172810(Wk *w, Ob *o, P160 *p, s32 a3) {
    Prm *q = p->xc;
    switch (a3) {
    case 1:
        if (w->x70 == 24) return 0;
    case 0:
        if (w->x70 == 8) return 0;
        if (!q) return 0;
        return func_0016dd30(w, o, p, a3);
    case 2:
        func_0016dd30(w, o, p, a3);
        if (o->x54 == 0) {
            func_0013df40(w, 0);
            o->x68 = func_00171aa8(q->x14, q->x18);
        }
        if (!func_00171ae8(w, o)) {
            func_00171b80(w, o, q->x0);
            if (func_00171ae8(w, o)) {
                o->x40->b2 = 1;
                o->x40->x50 = q->x1c;
            }
        } else {
            o->x40->b2 = 1;
            func_0014a0f0(o->x40);
        }
        return 1;
    }
    return 1;
}

s32 func_00172bc8(Wk3 *w, Ac3 *o, R160 *p, s32 a3) {
    Prm3 *q = p->xc;
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 31)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        if (!o->x90) return 0;
        return func_0016b670(w, o, p, 1);
    case 2:
        o->flags |= 0x800;
        func_00130340(w, 0x10000ce, 8.0f);
        o->x4c = 206;
        o->x170 = p;
        o->x178 = 0x40000000;
        o->x174 = 0;
        o->x164 = w->x14 - q->x24;
        func_00130578(w, 0x40000000, 8.0f)->cb = func_001731f8;
        func_00148a40(w, 0);
        func_00170fa8(w, o, func_00170f90, D_0035BE40, 30.0f);
        func_001412f8(w, func_001477c8(func_0013dbe0(w, q->x0)[1])[12]);
        o->x48 = func_00173610;
        func_00170f50(w, o, func_001734f8, 3, 0);
        return 1;
    }
    return 1;
}

s32 func_00173d00(Wk3 *w, Ac4 *o, R160 *p, s32 a3) {
    Prm3 *q = p->xc;
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 49)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        return func_0016b670(w, o, p, 1);
    case 2:
        o->flags |= 0x800;
        func_00130340(w, 0x10000ca, 8.0f);
        o->x4c = 202;
        func_00130578(w, 0x40000000, 8.0f)->cb = func_001740e8;
        o->x160 = p;
        o->x164 = 0;
        func_00148a40(w, 0);
        func_00170fa8(w, o, func_00170f90, D_0035C1E0, 30.0f);
        func_001412f8(w, func_001477c8(func_0013dbe0(w, q->x0)[1])[12]);
        o->x48 = func_001742b0;
        func_00170f50(w, o, func_001741a0, 3, 0);
        return 1;
    }
    return 1;
}

s32 func_00174798(Wk3 *w, Ac4 *o, R160 *p, s32 a3) {
    Prm3 *q = p->xc;
    switch (a3) {
    case 0:
        return 0;
    case 1:
        if (!func_00171a88(w, o, 44)) return 0;
        if (!((s32)(o->flags >> 2) & 1)) return 0;
        if (!o->x90) return 0;
        return func_0016b670(w, o, p, 1);
    case 2:
        o->flags |= 0x800;
        func_00130340(w, 0x10000ca, 8.0f);
        o->x4c = 202;
        func_00130578(w, 0x40000075, 8.0f)->cb = func_00174ad8;
        o->x160 = p;
        o->x164 = 0;
        func_00148a40(w, 0);
        func_00170fa8(w, o, func_00170f90, D_0035C350, 30.0f);
        func_001412f8(w, func_001477c8(func_0013dbe0(w, q->x0)[1])[12]);
        o->x48 = func_00174ca8;
        func_00170f50(w, o, func_00174b90, 3, 0);
        return 1;
    }
    return 1;
}

s32 func_00176658(s32 a0, Obj3C *o, s32 size, s32 a3) {
    Ppp *p;
    s32 q;
    s32 ok = 1;
    q = 0;
    p = 0;
    func_00181fe0(&p);
    if (!p) {
        if (!func_00181410(a3)) {
            ok = 0;
            goto end;
        }
        func_00181fe0(&p);
    }
    p->x88 = a0;
    p->x93 = size;
    p->x94 = o;
    p->xa8 = D_0035C6F8++;
    o->x14 = 17;
    o->x0 = p;
    o->x4 = (u8 *)p + 16;
    o->x8 = (u8 *)p + 32;
    o->xc = (u8 *)p + 48;
    o->x10 = (u8 *)p + 133;
    o->x18 = (u8 *)p + 160;
    o->x20 = (u8 *)p + 177;
    o->x24 = (u8 *)p + 64;
    o->x28 = (u8 *)p + 96;
    o->x2c = p;
    o->x30 = D_0035C6FC++;
    o->x34 = (u8 *)p + 183;
    func_001803f0(a0, size, &q, p);
    p->x98 = a3;
    if (!q) {
        ok = 0;
    } else {
        if (func_00181318() > 0x7ffff) {
            do {
                if (!func_00181368(a3)) {
                    ok = 0;
                    goto end;
                }
            } while (func_00181318() > 0x7ffff);
        }
        func_00182c10(p, q, 1);
    }
end:
    if (!ok && p) func_00182840(p);
    return ok;
}

void func_00176cc8(s32 i) {
    T44 *s = &D_005757B0[i];
    s32 j;
    F20 *e;
    if (!s->h) return;
    for (j = 0; j < 2; j++) {
        u8 *p;
        e = &s->e[j];
        if (e->c <= 0) continue;
        p = e->b;
        if (p == e->a) {
            e->e = p[1];
        } else {
            e->e = ((f32)p[1] - (f32)p[-1]) / p[0] * e->d + p[-1];
            e->d += D_002BBDFC;
        }
        if (e->e < 0.0f) e->e = 0.0f;
        if (e->e >= 256.0f) e->e = 255.0f;
        D_002C5AD2[i][j] = e->e;
        if (p[0] <= e->d) {
            e->d -= p[0];
            e->b = p + 2;
            e->c--;
        }
    }
    if (s->e[0].c > 0) return;
    if (s->e[1].c > 0) return;
    if (s->h->x4 & 1) {
        func_00176ba8(s->h, i);
        return;
    }
    func_00176c60(i);
}
#include "data/data_0035.h"
#include "data/pieces/D_002C5AD0.h"
