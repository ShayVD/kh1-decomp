#include "common.h"
#include "data/bss_004E.h"
typedef struct {
    s32 id;
    s32 x4;
    s32 x8;
    s32 handle;
    s32 x10;
    u8 active;
    u8 x15;
    u8 kind;
    u8 x17;
} SndSlot;
extern s32 D_004E344C;
extern SndSlot *D_004E3450;
void func_001ed2d8(s32, s32, s32);
void func_001ed370(s32, s32, s32, s32, s32);
CONTEXT_ONLY void func_0011c850(s32 a, s32 b, s32 c) { func_001ed2d8(a, b, c); }
CONTEXT_ONLY void func_0011c868(s32 a, s32 b, s32 c, s32 d, s32 e) { func_001ed370(a, b, c, d, e); }

void func_0011d350(s32 a0, s32 a1) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) {
            e->active = 0;
            func_0011c850(e->handle, a0, a1);
            return;
        }
    }
}

void func_0011d3c8(s32 a0, s32 a1, s32 a2) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->id == a0 && e->x10 == a1) {
            e->active = 0;
            func_0011c868(e->handle, a0, a1, -1, a2);
            return;
        }
    }
}

void func_0011d448(void) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active && e->kind == 4) {
            e->active = 0;
            func_0011c850(e->handle, e->id, e->x10);
        }
    }
}

void func_0011d4e0(s32 a0) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active && e->kind == 4) {
            e->active = 0;
            func_0011c868(e->handle, e->id, e->x10, -1, a0);
        }
    }
}

void func_0011d5f0(void) {
    s32 i;
    SndSlot *e = D_004E3450;
    for (i = 0; i < D_004E344C; i++, e++) {
        if (e->active && e->kind == 2) {
            e->active = 0;
            func_0011c850(e->handle, e->id, e->x10);
        }
    }
}

typedef struct { s32 off; s32 size; } Chunk;
typedef struct { u8 pad[16]; Chunk c[2]; } SndHdr;
extern void (*D_004E3430)(void);
void func_001ed128(s32, s32);
s32 func_001ed220();
void func_001ed658(s32, void *, s32);
void func_001edba0(void);
s32 func_001ecfd8(void);
void func_001104e0(void);
extern char D_0048D158[];
void func_0011ef10(s32, void (*)(void));
void func_0011cba0(void);
s32 strcmp(const char *, const char *);
typedef struct { s32 n; u8 pad[12]; Chunk c[1]; } SndHdr2;

void func_0011cd20(s32 a0, SndHdr *a1, void (*a3)(void)) {
    Chunk *c = &a1->c[0];
    s32 off0 = c->off, sz0 = c->size;
    s32 off1, sz1;
    u8 *p0, *p1;
    c = &a1->c[1];
    off1 = c->off; sz1 = c->size;
    D_004E3430 = a3;
    p0 = (u8 *)a1 + off0;
    p1 = (u8 *)a1 + off1;
    func_001ed128(0, 2);
    func_001ed128(2, 2);
    func_001ed220(a0, p0, sz0);
    func_001ed658(a0, p1, sz1);
    func_001edba0();
    while (!func_001ecfd8()) func_001104e0();
}

void func_0011cdf0(s32 a0, SndHdr2 *h, void (*cb)(void)) {
    s32 i, cnt, total, n;
    Chunk *c;
    u8 *p0;
    Chunk *c0;
    char *s;
    cnt = 0;
    total = 0;
    c = c0 = h->c;
    n = h->n;
    p0 = (u8 *)h + c->off;
    for (i = 0; i < n; i++, c++) {
        s = (char *)h + c->off;
        if (strcmp(s, D_0048D158) == 0) {
            cnt++;
            total += *(s32 *)(s + 12) + 16;
        }
    }
    if (cnt) {
        func_001ed128(0, a0);
        func_001ed128(3, a0);
        func_001ed220(a0, p0, total);
        c = c0 + cnt;
        for (i = 0; i < n - cnt; i++, c++) {
            func_001ed658(a0, (u8 *)h + c->off, c->size);
        }
        D_004E3430 = cb;
        func_0011ef10(10000, func_0011cba0);
    } else {
        cb();
    }
}

extern s32 D_002C1388;
extern void (*D_004E3434)(void);
extern s32 D_004E3444;
extern s32 D_002C1390;
CONTEXT_ONLY void func_0011e528(void) { D_002C1390 = 0; }
typedef struct { u32 b0 : 1; u32 rest : 31; } Bits5958;
extern Bits5958 D_002C5958;
extern s32 D_004E3438, D_004E343C, D_004E3440;
extern s32 D_002C1364;
void func_0011c7c0(s32, s32, s32);
void func_0011c7a8(s32, s32, s32, s32, s32, s32);
CONTEXT_ONLY void func_0011e610(void) {
    if (D_002C5958.b0 == 1) {
        func_0011c7c0(0, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(1, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(1, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 1;
    } else {
        func_0011c7c0(1, 0, 240);
        if (D_004E3440 == 0) func_0011c7a8(0, 0x3000, 0x3000, 0, 0, 120);
        else func_0011c7a8(0, 0, D_004E3438, D_004E343C, 0, 120);
        D_002C1364 = 0;
    }
}

void func_0011e700(void) {
    if (!D_002C1388) func_0011e528();
    if (!D_004E3444) func_0011e610();
    if (D_004E3434) D_004E3434();
}

typedef int u128 __attribute__((mode(TI)));
/* lq/sq quadword copy with one trailing nop. */
static inline void CopyQword1(void *dst, void *src) {
    __asm__ volatile("lq $6, 0(%1)\nsq $6, 0(%0)\nnop" : : "r"(dst), "r"(src) : "$6");
}
typedef struct { s16 v[10]; } Rec20s;
typedef struct { f32 x, y, z; } V3;
/* 64-byte table entries at D_004E2450 (= D_004E2430 + 0x20). */
typedef struct {
    u128 *x0;
    u128 *x4;
    Rec20s *x8;
    f32 *xc;
    u8 pad[48];
} Ent2450;
extern Ent2450 D_004E2450[];

s32 func_0011a868(s32 a0, s32 a1, f32 *a2) {
    Ent2450 *e = &D_004E2450[a0];
    V3 *b = (V3 *)e->xc;
    V3 *p0 = (V3 *)((u32)e->x8[a1].v[0] * 12 + (u32)b);
    V3 *p1 = (V3 *)((u32)e->x8[a1].v[1] * 12 + (u32)b);
    V3 *p2 = (V3 *)((u32)e->x8[a1].v[2] * 12 + (u32)b);
    V3 *p3 = (V3 *)((u32)e->x8[a1].v[3] * 12 + (u32)b);
    a2[0] = p0->x; a2[1] = p0->y; a2[2] = p0->z; a2[3] = 1.0f;
    a2[4] = p1->x; a2[5] = p1->y; a2[6] = p1->z; a2[7] = 1.0f;
    a2[8] = p2->x; a2[9] = p2->y; a2[10] = p2->z; a2[11] = 1.0f;
    if (e->x8[a1].v[3] == -1) return 3;
    a2[12] = p3->x; a2[13] = p3->y; a2[14] = p3->z; a2[15] = 1.0f;
    return 4;
}

s32 func_0011aa18(s32 a0, s32 a1, u128 *a2) {
    Ent2450 *e = &D_004E2450[a0];
    CopyQword1(&a2[0], &e->x0[e->x8[a1].v[0]]);
    CopyQword1(&a2[1], &e->x0[e->x8[a1].v[1]]);
    CopyQword1(&a2[2], &e->x0[e->x8[a1].v[2]]);
    if (e->x8[a1].v[3] == -1) return 3;
    CopyQword1(&a2[3], &e->x0[e->x8[a1].v[3]]);
    return 4;
}

typedef struct { f32 min[4]; f32 max[4]; u8 pad[32]; } Box64;
extern Box64 D_004E2430[];
s32 func_0011a728(f32 *a, s32 i) {
    if (a[3] >= D_004E2430[i].min[0] && D_004E2430[i].max[0] >= a[0] &&
        a[4] >= D_004E2430[i].min[1] && a[1] <= D_004E2430[i].max[1] &&
        a[5] >= D_004E2430[i].min[2] && a[2] <= D_004E2430[i].max[2]) return 1;
    return 0;
}

s32 func_001197e0(f32 *a, f32 *b, f32 *c) {
    s32 t;
    t = c[0] < a[0];
    if (b[0] < c[0]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    t = c[1] < a[1];
    if (b[1] < c[1]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    t = c[2] < a[2];
    if (b[2] < c[2]) { t ^= 1; if (!t) goto z1; } else if (!t) goto zero;
    return 1;
z1:
    return 0;
zero:
    return 0;
}

typedef f32 V4[4] __attribute__((aligned(16)));
static inline f32 vdot(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
void func_0011a9c8(s32, s32, V4 *);

f32 func_00119e80(s32 a0, s32 a1, f32 *n, f32 *p) {
    V4 v;
    f32 d;
    func_0011a9c8(a0, a1, &v);
    d = -vdot(n, v);
    return vdot(p, n) + d;
}

static inline f32 vdist2(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}
typedef struct { u8 pad[16]; s32 x10; } Rec20w;
typedef struct { Rec20w *x0; u8 pad[60]; } Ent2458;
extern Ent2458 D_004E2458[];
/* 16-byte collision entries at D_003044D8, D_003044D0 of them. */
typedef struct { u32 b0 : 1; u32 mask : 8; u32 rest : 23; } ColFlags;
typedef struct { s32 x0; u8 *x4; s32 x8; ColFlags flags; } ColEnt;
extern ColEnt D_003044D8[];
extern s32 D_003044D0;
void func_001158c8(void *);
s32 func_0011ab88(s32, s32, void *);
s32 func_0011bfc8(s32, s32, void *, void *, void *);
s32 func_001198c8(s32, s32, void *);

s32 func_0011c118(s32 a0, f32 *p, void *dir, void *q, f32 *out) {
    s32 ids[32];
    V4 hits[32];
    V4 tmp;
    V4 pad;
    u8 *h;
    u16 *list;
    Rec20w *rec;
    s32 i, n, best, idx;
    f32 min, d;
    h = D_003044D8[a0].x4;
    h += *(s32 *)(h + 16);
    list = (u16 *)(h + *(s32 *)(h + 32));
    rec = D_004E2458[a0].x0;
    func_001158c8(q);
    n = 0;
    for (i = 0; i < list[0]; i++) {
        idx = list[i + 1];
        { Rec20w *r = &rec[idx]; if (r->x10 & 0xe) continue; }
        if (func_0011ab88(a0, idx, q) && func_0011bfc8(a0, idx, p, dir, tmp) && func_001198c8(a0, idx, tmp)) {
            CopyQword1(hits[n], tmp);
            ids[n] = idx;
            n++;
        }
    }
    if (n != 0) {
        idx = 0;
        min = 1.0e12f;
        for (i = 0; i < n; i++) {
            d = vdist2(p, hits[i]);
            if (d < min) { min = d; idx = i; }
        }
        CopyQword1(out, hits[idx]);
        return ids[idx];
    }
    return -1;
}

void func_0011a410(s32);
s32 func_0011c338(f32 *box, f32 *p, void *dir, f32 *out, s32 mask, s32 *idout) {
    s32 list[64];
    V4 hits[64];
    s32 res[64];
    s32 i, cnt, best, id, r;
    f32 min, d;
    cnt = 0;
    if (mask == -1) {
        for (i = 0; i < D_003044D0; i++) {
            if (D_003044D8[i].flags.b0 == 1) continue;
            if (func_0011a728(box, i)) {
                func_0011a410(i);
                list[cnt++] = i;
            }
        }
    } else {
        for (i = 0; i < D_003044D0; i++) {
            if (D_003044D8[i].flags.b0 == 1) continue;
            if ((D_003044D8[i].flags.mask & mask) != mask) continue;
            if (func_0011a728(box, i)) {
                func_0011a410(i);
                list[cnt++] = i;
            }
        }
    }
    if (cnt == 0) return -1;
    if (cnt == 1) {
        i = list[0];
        r = func_0011c118(i, p, dir, box, out);
        *idout = i;
        return r;
    }
    min = 1.0e12f;
    best = 0;
    for (i = 0; i < cnt; i++) {
        res[i] = func_0011c118(list[i], p, dir, box, hits[i]);
        d = vdist2(p, hits[i]);
        if (d < min) { min = d; best = i; }
    }
    CopyQword1(out, hits[best]);
    *idout = list[best];
    return res[best];
}

typedef struct { f32 mn[3]; f32 mx[3]; s16 cnt; u8 pad[6]; } Qry;
typedef struct { V4 x0; V4 x10; f32 x20; u8 pad24[12]; V4 x30; } Mov;
typedef struct { u8 pad[0x20]; f32 r; f32 h; s32 flags; u8 pad2[0x54]; } ColObj;
extern f32 D_002C1250;
extern s32 D_002A62EC;
extern s32 D_002BD250[];
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_001047c8(void);
void func_00104528(void);
void func_00104f10(s32, f32 *);
u64 func_0011b6a0(ColObj *, f32 *, s32);
void func_00116368(Qry *, s32);
void func_00117db0(Qry *);
s32 func_00119a20(s32, f32 *, f32 *, f32 *, f32 *);
s32 func_00119ad8(s32, s32, f32 *, f32 *, f32 *, f32 *);

s32 func_00118868(Mov *o) {
    V4 a, b, c;
    Qry q;
    s32 miss[512];
    ColObj obj;
    s32 hit, retry;
    s64 res;
    s32 i, n, id;
    o->x0[3] = 1.0f;
    o->x10[3] = 1.0f;
    retry = 0;
    D_002C1250 = o->x20 - 0.007999999681f;
    func_00267518(a, o->x0, o->x10);
    obj.r = o->x20;
    obj.h = 0.0f;
    func_001047c8();
loop:
    hit = 0;
    res = ((s32 (*)(ColObj *, f32 *, s32))func_0011b6a0)(&obj, a, 1);
    q.mn[0] = a[0] - o->x20;
    q.mn[2] = a[2] - o->x20;
    q.mn[1] = a[1] - o->x20;
    q.mx[2] = a[2] + o->x20;
    q.mx[0] = a[0] + o->x20;
    q.mx[1] = a[1] + o->x20;
    if (D_002A62EC == 0) func_00116368(&q, 7);
    else func_00117db0(&q);
    b[3] = 1.0f;
    n = 0;
    for (i = 0; i < (u16)q.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, c);
        if (func_00119a20(id, c, a, b, &D_002C1250)) {
            hit = 1;
            func_00267e90(c, c, o->x20);
            func_00267518(a, b, c);
        } else {
            miss[n++] = id;
        }
    }
    for (i = 0; i < n; i++) {
        id = miss[i];
        func_00104f10(id, c);
        if (func_00119ad8(-1, id, c, a, b, &D_002C1250)) {
            func_00267530(a, a, b);
            hit = 1;
            func_002673b8(a, a);
            func_00267e90(a, a, o->x20);
            func_00267518(a, b, a);
        }
    }
    func_002675a8(o->x30, a);
    if ((hit || res) && retry < 3) {
        retry++;
        goto loop;
    }
    func_00104528();
    return retry != 0;
}

static inline void vapply(void *d, void *m, void *v) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 16(%1)\n"
        "lqc2 $vf6, 32(%1)\n"
        "lqc2 $vf7, 48(%1)\n"
        "lqc2 $vf8, 0(%2)\n"
        "vmulax.xyzw ACC, $vf4xyzw, $vf8x\n"
        "vmadday.xyzw ACC, $vf5xyzw, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6xyzw, $vf8z\n"
        "vmaddw.xyzw $vf9xyzw, $vf7xyzw, $vf8w\n"
        "sqc2 $vf9, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(m), "r"(v) : "memory");
}
typedef struct { V4 x0; V4 mn; V4 mx; V4 c[8]; } BoxWork;
void *func_00122048(s32, s32);
void func_001220b8(void *);
void func_0011a0a0(void) {
    BoxWork *w;
    s32 i, j, k;
    u8 *h;
    f32 mn, mx, v;
    w = func_00122048(176, 4);
    w->x0[3] = w->mn[3] = w->mx[3] = w->c[0][3] = w->c[1][3] = w->c[2][3] = w->c[3][3] = w->c[4][3] = w->c[5][3] = w->c[6][3] = w->c[7][3] = 1.0f;
    for (i = 0; i < D_003044D0; i++) {
        h = D_003044D8[i].x4;
        h += *(s32 *)(h + 16);
        h += *(s32 *)h;
        w->mn[0] = ((f32 *)h)[0];
        w->mn[1] = ((f32 *)h)[1];
        w->mn[2] = ((f32 *)h)[2];
        w->mx[0] = ((f32 *)h)[4];
        w->mx[1] = ((f32 *)h)[5];
        w->mx[2] = ((f32 *)h)[6];
        w->c[0][0] = w->mn[0]; w->c[0][1] = w->mn[1]; w->c[0][2] = w->mn[2];
        w->c[1][0] = w->mx[0]; w->c[1][1] = w->mn[1]; w->c[1][2] = w->mn[2];
        w->c[2][0] = w->mn[0]; w->c[2][1] = w->mx[1]; w->c[2][2] = w->mn[2];
        w->c[3][0] = w->mx[0]; w->c[3][1] = w->mx[1]; w->c[3][2] = w->mn[2];
        w->c[4][0] = w->mn[0]; w->c[4][1] = w->mn[1]; w->c[4][2] = w->mx[2];
        w->c[5][0] = w->mx[0]; w->c[5][1] = w->mn[1]; w->c[5][2] = w->mx[2];
        w->c[6][0] = w->mn[0]; w->c[6][1] = w->mx[1]; w->c[6][2] = w->mx[2];
        w->c[7][0] = w->mx[0]; w->c[7][1] = w->mx[1]; w->c[7][2] = w->mx[2];
        vapply(w->c[0], (f32 *)D_003044D8[i].x0, w->c[0]);
        vapply(w->c[1], (f32 *)D_003044D8[i].x0, w->c[1]);
        vapply(w->c[2], (f32 *)D_003044D8[i].x0, w->c[2]);
        vapply(w->c[3], (f32 *)D_003044D8[i].x0, w->c[3]);
        vapply(w->c[4], (f32 *)D_003044D8[i].x0, w->c[4]);
        vapply(w->c[5], (f32 *)D_003044D8[i].x0, w->c[5]);
        vapply(w->c[6], (f32 *)D_003044D8[i].x0, w->c[6]);
        vapply(w->c[7], (f32 *)D_003044D8[i].x0, w->c[7]);
        for (j = 0; j < 3; j++) {
            mn = mx = w->c[0][j];
            for (k = 1; k < 8; k++) {
                v = w->c[k][j];
                if (v < mn) mn = v;
                if (mx < v) mx = v;
            }
            D_004E2430[i].min[j] = mn;
            D_004E2430[i].max[j] = mx;
        }
    }
    func_001220b8(w);
}


extern void *D_002C1300;
void func_00116690(void);
void func_001166a0(void);
void func_001166b0(void);
void func_001166c0(void);
void func_001166c8(void);
void func_001166d8(void);
u64 func_0011b220(s32, f32 *, f32 *, s32, f32);
u64 func_0011b6a0(ColObj *o, f32 *pos, s32 a2) {
    f32 box[6];
    f32 box2[6];
    f32 r, g, y;
    s32 i;
    u64 res;
    switch (o->flags & 0x7c) {
    case 4: D_002C1300 = func_00116690; break;
    case 16: D_002C1300 = func_001166a0; break;
    case 8: D_002C1300 = func_001166b0; break;
    case 32: D_002C1300 = func_001166c0; break;
    case 64: D_002C1300 = func_001166c8; break;
    default: D_002C1300 = func_001166d8; break;
    }
    r = D_002C1250 + o->r * 0.5f;
    res = 0;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].flags.b0 == 1) continue;
        y = pos[1] - o->h;
        g = D_002C1250;
        box[0] = pos[0] - g;
        box[2] = pos[2] - g;
        box[1] = y - g;
        box[3] = pos[0] + g;
        box[5] = pos[2] + g;
        box[4] = y + g;
        if (func_0011a728(box, i)) {
            func_0011a410(i);
            box2[0] = pos[0] - r;
            box2[3] = pos[0] + r;
            pos[1] = pos[1] - o->h;
            box2[2] = pos[2] - r;
            box2[5] = pos[2] + r;
            box2[4] = pos[1] + r;
            box2[1] = pos[1] - r;
            res |= func_0011b220(i, pos, box2, a2, o->r);
            pos[1] = pos[1] + o->h;
        }
    }
    return res;
}

#include "data/bss_004E_mixed.h"
#include "data/data_002A.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
