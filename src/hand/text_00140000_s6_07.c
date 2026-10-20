#include "common.h"

#include "platform/math.h"
#include "data/bss_0054.h"

void func_00121fc4(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void func_0014d570(f32 *v, f32 lo, f32 hi, f32 max, f32 g) {
    f32 h;
    f32 a;
    f32 c;
    f32 t;
    f32 b;
    f32 k;

    h = -v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    k = 0.5f;
    a = g * k;
    c = a * 4.0f * h;
    t = MIN(MAX(lo, v[3] / max), hi);
    b = (-g * t) * k;
    t = (PlatSqrtf(b * b - c) - b) / (a + a);
    func_00267560(v, v, MIN(v[3] / t, max));
    v[1] = b;
}


typedef struct { s32 f0, f4; } S31b0;
extern S31b0 D_002E31B0;
f32 func_0012ec60(s32, s32, f32 *);
void func_001315c0(void *, s32, f32, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
f32 func_00121748(f32 *, f32 *);
f32 func_00120c18(f32 *);

void func_0014d988(void *o, s32 unused, f32 *v, f32 r, f32 off, f32 scale, f32 lim) {
    f32 p[4];
    f32 d[4];
    f32 h;
    f32 s;
    f32 y;
    f32 z;
    f32 t;

    z = 0.0f;
    h = func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, d);
    func_001315c0(o, 0x8003, z, p);
    func_00267530(d, d, p);
    if (r < func_00121748(d, v)) {
        s = (func_00120c18(d) - h - off) * scale;
        if (z < s) {
            y = d[1] / s * v[3];
            if (y < -lim) t = -lim; else if (lim < y) t = lim; else t = y;
            v[1] = t;
        }
    }
}


typedef struct { union { u64 x; u8 id; } f; u8 pad8[8]; f32 mn[4]; f32 mx[4]; } W34Box;
typedef struct { u8 pad[4]; u8 n; u8 pad5[0xb]; W34Box box[1]; } W34Boxes;
extern W34Boxes *D_00350D78;
extern s32 D_0054F44C;
typedef struct { u8 x[20]; } Col20;
typedef struct { u8 pad[5]; u8 n; u8 pad6[0xe]; Col20 *cols; } ColSet;
typedef struct { u8 pad[0x134]; ColSet *cs; } Ob88;
typedef struct { f32 a[4]; f32 b[4]; } Cap88;
void func_0015bad0(Ob88 *, Col20 *, void *);
void func_00267518(f32 *, f32 *, f32 *);
s32 func_0014ee08(f32 *, f32 *, f32 *);

s32 func_0014ee88(Ob88 *o) {
    Cap88 cap;
    f32 lo[4];
    f32 hi[4];
    f32 q[4];
    s32 i;
    s32 m;
    W34Box *b;
    ColSet *cs;

    if (!D_00350D78 || !o || !(cs = o->cs) || !cs->n) return 0;
    i = 0;
    m = 0;
    func_0015bad0(o, cs->cols, &cap);
    q[0] = q[2] = cap.a[1];
    q[1] = cap.a[2];
    func_00267530(lo, cap.b, q);
    func_00267518(hi, cap.b, q);
    b = D_00350D78->box;
    for (; i < D_00350D78->n; i++, b++) {
        if ((b->f.x & 0x200) || func_0014ee08(lo, hi, (f32 *)b)) m |= 1 << (b->f.id - 1);
    }
    return m & D_0054F44C;
}


void func_00152ba8(void *, f32 *, f32);


typedef struct { u8 pad[0x10]; f32 pos[4]; } O2c28;

void func_00152c28(O2c28 *o, f32 *dst, f32 g) {
    f32 v[4];
    f32 h;
    f32 a;
    f32 c;
    f32 t;
    f32 b;
    f32 k;

    func_00267530(v, dst, o->pos);
    h = -v[1];
    v[1] = 0.0f;
    func_00121fc4(v, v);
    k = 0.5f;
    a = g * k;
    c = a * 4.0f * h;
    t = MIN(MAX(20.0f, v[3] / 20.0f), 30.0f);
    b = (-g * t) * k;
    t = (PlatSqrtf(b * b - c) - b) / (a + a);
    func_00267560(v, v, MIN(v[3] / t, 20.0f));
    v[1] = b;
    func_00152ba8(o, v, g);
}


typedef struct { u8 pad[0x70]; s32 x70; u8 pad74[0x164 - 0x74]; s32 x164; } A3e80;
void func_00130340(A3e80 *, s32, f32);
void func_00130578(A3e80 *, s32, f32);
CONTEXT_ONLY void func_00153d88(A3e80 *a) { a->x70 = 0; }

void func_00153e80(A3e80 *a) {
    if (a->x70 == 17) {
        func_00130340(a, 0x100006d, 16.0f);
        func_00130578(a, 0x4000002d, 0.0f);
    } else {
        switch (a->x164) {
        case 67:
        case 108:
            func_00130340(a, 0x1000044, 8.0f);
            func_00130578(a, 0x40000000, 8.0f);
            break;
        case 141:
            func_00130340(a, 0x100008e, 8.0f);
            func_00130578(a, 0x40000075, 8.0f);
            break;
        }
    }
    func_00153d88(a);
}


typedef struct { s8 id; u8 n; u8 x2; u8 x3; u8 pad[0x44 - 4]; s32 x44; } E5878;
typedef struct { u8 pad[0x1c]; s32 off; s32 end; u8 rest[0x40000 - 0x24]; } R5878;
extern s32 D_002C5958;
extern E5878 D_00550400[];
extern R5878 D_00FE0000[];
void func_00146928(s32);
void func_00146b90(void *, s32, s32, s32);

void func_00155878(void) {
    s32 i, j;
    E5878 *p;
    R5878 *r;

    D_002C5958 &= ~0x40000;
    func_00146928(-6);
    for (i = 0; i < 64; i++) {
        p = &D_00550400[i];
        if (p->id != i) continue;
        if (!(*(u32 *)p & 0x10000)) continue;
        for (j = 0; j < p->n; j++) {
            if (p->id != p[j].id) { p = 0; break; }
        }
        if (!p) continue;
        r = &D_00FE0000[i];
        if (r->end - r->off > 0) func_00146b90((u8 *)r + r->off, -6, 0, 0);
    }
}


CONTEXT_ONLY void func_00155be0(s32 a) { D_00550400[a].x3 = 0; }

void func_00155cf8(s32 a0, s32 a1, s32 key) {
    s32 i;
    E5878 *p;

    p = D_00550400;
    for (i = 0; i < 64; i++, p++) {
        if (p->id == i && p->x44 == key) break;
    }
    p->x3++;
    func_00155be0(key);
}


typedef struct { s32 x0; s32 idx; s32 x8; s32 xc; f32 k[32][4]; } D9c10;
extern D9c10 D_00551740;
void func_002675a8(f32 *, f32 *);
void func_002674f0(f32 *, f32 *, f32 *, f32);

void func_00159c10(f32 *out, f32 t) {
    s32 i, cur, nx;

    cur = D_00551740.idx;
    for (i = 0; i < 32; i++) {
        if (D_00551740.k[cur][3] == 0.0f) {
            func_002675a8(out, D_00551740.k[cur]);
            return;
        }
        nx = (cur + 31) % 32;
        if (!(D_00551740.k[cur][3] < t)) {
            func_002674f0(out, D_00551740.k[nx], D_00551740.k[cur], t / D_00551740.k[cur][3]);
            return;
        }
        t -= D_00551740.k[cur][3];
        cur = nx;
    }
}
