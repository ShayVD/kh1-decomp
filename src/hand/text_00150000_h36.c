/* Hand-matched functions near 0x159000-0x165000 (worker 36). */
#include "common.h"
#include "platform/math.h"

typedef struct { f32 v[3]; f32 len; } Seg16;
typedef struct { s32 w0; void *obj; s32 pad[2]; f32 a[4]; f32 b[4]; f32 f30; f32 f34; } Tr700;
typedef union { u64 d; struct { s32 lo; s32 head; s32 w8; s32 wC; } s; } TrHdr;
typedef struct { TrHdr h; Seg16 e[32]; } Trail;
typedef struct { u8 pad[0x10]; f32 pos[4]; } ObjP;
typedef struct { u8 pad[4]; f32 r; f32 h; u8 padc[4]; f32 pos[4]; } Cyl;

extern Tr700 D_00551700;
extern Trail D_00551740;
extern u32 D_002C5958;

void func_002675a8(void *, void *);
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
s32 func_00159cd8();
s32 func_0013f510(void *, s32);
s32 func_001401d8(void *, s32);
s32 func_001404d8(void *, s32);
s32 func_00144410(void *, s32);
void func_0014f658(void *, s32);
void func_00159f78(void *, s32, s32);
s32 func_0015d770(void *, s32);
s32 func_0015dd50(void *, s32);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267548(f32 *, f32 *, f32 *);
f32 func_00267390(f32 *, f32 *);

Tr700 *func_00159ea8(ObjP *obj, void *a, void *b) {
    D_00551700.obj = obj;
    func_002675a8(D_00551700.a, a);
    func_002675a8(D_00551700.b, b);
    if (func_0011ef38(func_00159cd8) == 0) {
        D_00551700.f30 = 1.0f;
        D_00551700.f34 = 300.0f;
        D_00551700.w0 = 0;
        D_00551740.h.s.head = 0;
        func_002675a8(&D_00551740.e[0], obj->pos);
        D_00551740.e[0].len = 0;
        D_00551740.h.s.w8 = 0;
        D_00551740.h.d |= 1;
        func_0011ef10(0x18894, func_00159cd8);
    }
    return &D_00551700;
}

void func_0015a258(void *a, s32 b) {
    if (func_001404d8(a, b)) return;
    if (func_001401d8(a, b)) return;
    if (func_0013f510(a, b)) return;
    if (func_0015d770(a, b)) return;
    if (func_00144410(a, b)) return;
    if (func_0015dd50(a, b)) return;
    if ((D_002C5958 >> 17) & 1) {
        func_0014f658(a, 30);
        return;
    }
    func_00159f78(a, b, 0);
}

s32 func_0015b4a8(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 s[4];
    f32 one = 1.0f;
    s[0] = s[2] = one / (a->r + b->r);
    s[1] = one / (a->h + b->h);
    func_00267530(d, b->pos, a->pos);
    func_00267548(d, d, s);
    return func_00267390(d, d) < one;
}

s32 func_0015b550(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 ad, rr;
    func_00267530(d, b->pos, a->pos);
    ad = fabsf(d[1]);
    if (a->h + b->h <= ad) return 0;
    if (b->h < ad) {
        ad = (ad - b->h) / a->h;
        rr = PlatSqrtf(1.0f - ad * ad) * a->r + b->r;
    } else {
        rr = a->r + b->r;
    }
    d[1] = 0;
    return func_00267390(d, d) < rr * rr;
}

s32 func_0015b6c0(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 r, rr, s;
    func_00267530(d, a->pos, b->pos);
    d[1] = fabsf(d[1]);
    if (a->h + b->h <= d[1]) return 0;
    if (b->h < d[1]) {
        r = (d[1] - b->h) / a->h;
        r = PlatSqrtf(1.0f - r * r) * a->r;
    } else r = a->r;
    d[0] = fabsf(d[0]);
    d[2] = fabsf(d[2]);
    if (d[0] < d[2]) {
        d[1] = d[0];
        d[0] = d[2];
        d[2] = d[1];
    }
    s = r + b->r;
    if (s <= d[2]) return 0;
    if (b->r < d[2]) {
        rr = (d[2] - b->r) / r;
        rr = PlatSqrtf(1.0f - rr * rr) * r + b->r;
    } else rr = s;
    return d[0] < rr;
}

s32 func_0015b7e8(Cyl *a, Cyl *b) {
    f32 d[4];
    f32 r, rr;
    func_00267530(d, a->pos, b->pos);
    d[1] = fabsf(d[1]);
    rr = a->h + b->h;
    if (rr <= d[1]) return 0;
    d[0] = fabsf(d[0]);
    d[2] = fabsf(d[2]);
    if (d[0] < d[2]) {
        d[1] = d[0];
        d[0] = d[2];
        d[2] = d[1];
    }
    r = a->r + b->r;
    if (r <= d[2]) return 0;
    if (b->r < d[2]) {
        rr = (d[2] - b->r) / a->r;
        rr = PlatSqrtf(1.0f - rr * rr) * a->r + b->r;
    } else rr = r;
    return d[0] < rr;
}
