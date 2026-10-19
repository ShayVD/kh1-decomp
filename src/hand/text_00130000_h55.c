/* Hand-matched functions near 0x139000-0x13c000 (worker 55). */
#include "common.h"

extern u32 D_002C5958;
extern u32 D_00304B84;
extern u8 *D_00308CDC;
void func_00130340(void *o, s32 a, f32 f);
void *func_00130578(void *, s32, f32);
s32 func_0014f600(void *o);
typedef struct {
    u8 pad00[0x6c];
    u8 *x6c;
    s32 x70;
    u8 pad74[0x164 - 0x74];
    s32 x164;
} W55ObA;
typedef struct { u8 pad[0x38]; f32 x38; } W55CamA;
extern s32 D_00304AF0[];
extern s32 D_00304AE0[];
extern u8 *D_00308CDC;
void func_00138a78(void *o, void *b);
f32 func_00176850(void);
void func_002675a8(void *d, void *s);
void func_00138a20(void *o, void *v, f32 f);

void func_00139840(W55ObA *o, u8 *b) {
    f32 v[4];
    s32 i;
    func_00138a78(o, b);
    if (func_0014f600(o)) {
        i = (s32)(func_00176850() * 2.0f);
        if (o->x164 == D_00304AF0[i]) i = (i + 1) & 1;
        func_00130340(o, D_00304AF0[i] | 0x1000000, 0.0f);
        func_00130578(o, 0x40000006, 8.0f);
        func_002675a8(v, b + 16);
        v[3] = ((W55CamA *)D_00308CDC)->x38 * *(f32 *)(o->x6c + 0xc4);
        func_00138a20(o, v, 20.0f);
        return;
    }
    i = (s32)(func_00176850() * 4.0f);
    if (o->x164 == D_00304AE0[i]) i = (i + 1) & 3;
    func_00130340(o, D_00304AE0[i] | 0x1000000, 0.0f);
    func_00130578(o, 0x40000000, 8.0f);
}
typedef struct W55ObC {
    u32 x0;
    u8 pad04[0x10 - 0x4];
    f32 pos[4];
    u8 pad20[0x6c - 0x20];
    s32 *x6c;
    u8 pad70[0x74 - 0x70];
    struct W55ObC *x74;
    u8 pad78[0x7c - 0x78];
    struct W55ObC *x7c;
    s32 x80;
    u8 pad84[0x88 - 0x84];
    s32 x88;
    u8 pad8c[0x370 - 0x8c];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } x370;
} W55ObC;
typedef struct { s32 d; W55ObC *p; } W55EntC;
void *func_00122048(s32 n, s32 a);
void func_001220b8(void *p);
W55ObC *func_00123158(W55ObC *o, W55ObC *p);
s32 func_001375d8(W55ObC *p);
f32 func_00176850(void);
void func_00250360(void *b, s32 n, s32 sz, void *cmp);
void func_00267530(f32 *d, f32 *a, f32 *b);
f32 func_00120bf8(f32 *v);
s32 func_0013a430();

W55ObC *func_001231b8(W55ObC *o, W55ObC *p);
W55ObC *func_0013a670(W55ObC *o, s32 *w, f32 rng, f32 lim) {
    f32 v[4];
    W55ObC *p = 0;
    W55EntC *e, *base;
    s32 n, r;
    f32 q;
    base = e = func_00122048(0x300, 4);
    while ((p = func_001231b8(o, p))) {
        if (p->x6c[16] <= 0) continue;
        q = (f32)p->x6c[15] / (f32)p->x6c[16];
        if (lim < q) continue;
        func_00267530(v, p->pos, o->pos);
        if (rng < func_00120bf8(v)) continue;
        e->p = p;
        e->d = q * 100.0f;
        e++;
    }
    n = e - base;
    func_00250360(base, n, 8, func_0013a430);
    if (n > 0) p = base[0].p;
    r = (s32)(func_00176850() * 100.0f);
    if ((r -= w[0]) >= 0) {
        if ((r -= w[1]) >= 0 && n >= 3) {
            p = base[2].p;
        } else if (n >= 2) {
            p = base[1].p;
        }
    }
    func_001220b8(base);
    return p;
}
typedef struct { u8 pad[0x44]; s32 x44; } W55Stat;
typedef struct {
    u8 pad00[0x6c];
    W55Stat *x6c;
    s32 x70;
} W55Pl;
typedef struct { u64 x0; u8 padx[0x18]; } W55Ent32;
typedef struct { u8 pad[0x98]; u8 x98; u8 pad99[7]; } W55Lv;
extern u32 D_002E31A8;
extern W55Pl *D_002E26A0[];
extern W55Ent32 D_00350D88[];
extern s32 D_002BC128;
extern s32 D_002BC130;
extern u32 D_00304B84;
s32 func_00153d78(W55Pl *p);
s32 func_0012f040(W55Pl *p, s32 a);

s32 func_0013a910(s32 n) {
    W55Pl **pp;
    s32 i;
    if ((D_002E31A8 >> 2) & 1) return 0;
    if (!((D_00350D88[D_002E26A0[0]->x70].x0 >> 7) & 1)) return 0;
    if ((D_002C5958 >> 16) & 1) return 0;
    if (D_002E26A0[0]->x6c->x44 < D_00308CDC[n * 8 + 0x98]) return 0;
    if (!(D_002C5958 & 1)) return 0;
    if (D_002BC128 == 3 && D_002BC130 == 20) return 1;
    if (D_00304B84 & (1 << n)) return 0;
    for (i = 0; i < 3; i++) {
        if (!D_002E26A0[i] || func_00153d78(D_002E26A0[i]) || !func_0012f040(D_002E26A0[i], -1)) return 0;
    }
    return 1;
}
typedef struct { u32 lv:3; u32 on:1; u32 rest:28; } W55Bf;
extern W55Bf D_00304B78;
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern f32 D_00304B80;
extern s32 D_0052AE38;
extern s32 D_0052AE50;
extern s32 D_0052AE54;
extern void *D_0052AE58;
extern s32 D_00304B00[];
extern s32 D_00304B68;
extern char D_0048DCB0[];
extern u8 D_0052AD68[];
u8 D_0052AD78[0xc0] ALIGNED(8);
f32 func_0013bb20(void);
void func_00141540(s32 a, s32 b);
void func_001575b0(s32 a);
void *func_001559f0(s32 a, s32 b);
s32 sprintf(char *buf, const char *fmt, ...);
s32 func_00120748(char *name, void *dst, void (*cb)(), s32 d);
void func_0013ba18();
void func_0013b958();
void func_0011efa8(void *a, void *b, s32 c, s32 d);
void func_0011ef10(s32 a, void (*f)());

void func_0013bb60(s32 o, s32 n) {
    char buf[32];
    u32 *fl = &D_002C5958;
    W55Bf *bf = &D_00304B78;
    u32 *msk = &D_00304B84;
    u8 **lv = &D_00308CDC;
    f32 *fp;
    void **hp;
    *fl |= 0x102000;
    bf->lv = n;
    bf->on = 1;
    D_00304B70 = *lv + n * 8 + 0x98;
    *msk |= 1 << n;
    fp = &D_00304B7C;
    *fp = D_00304B80 = func_0013bb20();
    func_00141540(o, -(*lv)[n * 8 + 0x98]);
    D_0052AE38 = o;
    D_0052AE50 = n;
    func_001575b0(1);
    func_001575b0(2);
    func_001575b0(3);
    D_0052AE54 = 0;
    hp = &D_0052AE58;
    *hp = func_001559f0(52, 12);
    sprintf(buf, D_0048DCB0, D_00304B00[n], D_00304B68);
    func_00120748(buf, *hp, func_0013ba18, 0);
    func_0011efa8(D_0052AD68, D_0052AD78, 24, 8);
    func_0011ef10(0xcb20, func_0013b958);
}

/* needs make: uses rodata */
typedef struct {
    u8 pad00[0x88];
    s32 x88;
    u8 pad8c[0x3e4 - 0x8c];
    s32 x3e4;
} W55ObB;
typedef struct { u64 x0; u64 x8; } W55Msg;
W55Msg *func_00134928(W55ObB *o);
void func_00134998(W55ObB *o);
void func_001350d0(W55Msg *m);
void func_00138900(W55ObB *o);
void func_00138c30(W55ObB *o, W55Msg *m);
void func_00138e58(W55ObB *o, W55Msg *m);
void func_00139170(W55ObB *o, W55Msg *m);
void func_00139408(W55ObB *o, W55Msg *m);
void func_00139568(W55ObB *o, W55Msg *m);
void func_00139b98(W55ObB *o, W55Msg *m);
s32 func_00139cb8(W55ObB *o, W55Msg *m);
s32 func_0014f5c8(void *o);

void func_00139da8(W55ObB *o) {
    W55Msg *m = 0;
    s32 best = 0;
    s32 fl = o->x88;
    s32 k;
    for (;;) {
        if (m) func_001350d0(m);
        m = func_00134928(o);
        if (!m) break;
        if (o->x88 & 2) o->x88 = (o->x88 | 0x100) & ~2;
        k = func_00139cb8(o, m);
        o->x88 &= ~0x100;
        if (!k) continue;
        if (m->x0 & 0x22) continue;
        if ((s32)(m->x8 >> 43) & 1) {
            k = (s32)((s64)m->x8 >> 32) & 0x1f;
            switch (k) {
            case 2: case 3: case 4: case 5: func_00139840((void *)o, (void *)m); break;
            case 8: func_00139568(o, m); break;
            default: func_00134998(o); break;
            }
        } else {
            s32 j = (s32)((s64)m->x8 >> 32) & 0x1f;
            if (best < j) {
                best = j;
                switch (best) {
                case 0: case 1: break;
                case 2: func_00138c30(o, m); break;
                case 3: func_00138e58(o, m); break;
                case 5:
                    if (func_0014f5c8(o)) {
                case 4:
                        func_00139170(o, m);
                    } else {
                        func_00139408(o, m);
                    }
                    break;
                case 6: case 7: func_00139b98(o, m); break;
                case 8: func_00139568(o, m); break;
                }
            }
        }
    }
    if ((fl & 2) && !(o->x88 & 2)) {
        if (!best) {
            if (!(o->x88 & 1)) o->x3e4 = 0;
        } else {
            func_00138900(o);
        }
    }
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048DCB8[];
s32 D_00304B68 ALIGNED(8) = (s32)D_0048DCB8;
