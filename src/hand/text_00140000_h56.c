#include "common.h"
typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    V4 p;
    V4 d;
    V4 h;
    s16 idx;
    s16 pad;
    s32 sub;
    s32 pad2[2];
} Ray;
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00118608(Ray *);
void func_00118668(Ray *);
s32 func_00105b68(s32, s32);

s32 func_00142b30(u8 *o, f32 *v) {
    Ray r;
    f32 *pos = (f32 *)(o + 0x10);
    s32 res = 0;
    f32 t, d;

    func_002675a8(&r.p.x, pos);
    r.p.y -= *(f32 *)(o + 0x2c4) * 0.5f;
    r.d.x = v[0];
    r.d.z = v[2];
    r.p.w = 1.0f;
    r.d.y = 0.0f;
    r.d.w = 1.0f;
    func_00118608(&r);
    if (r.idx >= 0) {
        if (func_00105b68(r.sub, r.idx)) res = 3;
    }
    func_00267518(&r.p.x, pos, v);
    r.p.w = 1.0f;
    r.d.w = 1.0f;
    r.d.x = 0.0f;
    r.d.z = 0.0f;
    r.d.y = v[3] - v[1];
    func_00118668(&r);
    if (r.idx < 0) {
        res = 3;
    } else {
        d = r.h.y - *(f32 *)(o + 0x14);
        t = *(f32 *)(o + 0x2c4);
        if (d < -t * 0.5f) {
            res = 1;
        } else if (t < d) {
            res = 2;
        }
    }
    return res;
}

typedef struct { u8 pad[0x18]; f32 f18; u8 pad1c[0x54 - 0x1c]; s8 b54; } Prm130;
typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    u8 pad20[0x70 - 0x20];
    s32 st70;
    u8 pad74[0x120 - 0x74];
    f32 v120[4];
    Prm130 *p130;
} Ch;
s32 func_001425d0(Ch *);
f32 func_00121748(f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
#include "data/pieces/D_002C58B0.h"

void func_00143660(Ch *a, f32 *dir, Ch *b, f32 *out) {
    f32 t[4];
    f32 fa, fb;

    if (func_001425d0(a)) {
        if (func_001425d0(b)) {
            switch (a->st70) {
            case 10:
                if (func_00121748(out, dir) > 0.0f) {
                    func_002675a8(out, dir);
                    out[1] = 0.0f;
                    return;
                }
                break;
            case 13:
                func_00267530(out, b->pos, a->pos);
                if (func_00121748(out, dir) >= 0.0f) {
                    func_002675a8(out, dir);
                    return;
                }
                break;
            default:
                func_002675a8(out, dir);
                return;
            }
        } else if (a->p130->b54 == 9) {
            func_00267530(out, b->pos, a->pos);
            if (func_00121748(out, dir) >= 0.5f) {
                func_002675a8(out, dir);
                return;
            }
        }
        func_002675a8(out, (*(f32 (*)[0x4])&D_002C58B0));
    } else if (!func_001425d0(b)) {
        fa = a->p130->f18;
        fb = b->p130->f18;
        func_00267560(t, out, fa / (fa + fb));
        func_00267560(out, t, fb / fa);
        func_00267518(b->v120, b->v120, t);
    }
}

typedef struct { u8 x[20]; } Col20;
typedef struct { u8 pad[5]; u8 n; u8 pad6[0xe]; Col20 *cols; } ColSet;
typedef struct {
    u8 pad0[0x98];
    void *o98;
    u8 pad9c[0x134 - 0x9c];
    ColSet *cs;
    u8 pad138[0x398 - 0x138];
    void *o398;
    u8 pad39c[0x3a4 - 0x39c];
    u32 mask;
} Ch2;
typedef struct { f32 a[4]; f32 b[4]; f32 c[8]; } Cap;
s32 func_00123330(Ch2 *);
Cap *func_00122048(s32, s32);
void func_001220b8(Cap *);
Ch2 *func_001230a0(Ch2 *);
void func_0015bad0(Ch2 *, Col20 *, void *);
s32 func_0015b998(Cap *, void *);
void func_0015c5d0(Cap *, void *, f32 *);
void func_00142fe0(Ch2 *, Ch2 *);

void func_00143818(Ch2 *a, f32 *v) {
    Cap *cap;
    Ch2 *o;
    s32 i, j;
    f32 t[4];

    if (!func_00123330(a)) return;
    cap = func_00122048(0x40, 0x10);
    for (i = 0; i < a->cs->n; i++) {
        if (a->mask & (1 << i)) continue;
        o = NULL;
        func_0015bad0(a, &a->cs->cols[i], cap);
        func_00267518(cap->b, cap->b, v);
        while ((o = func_001230a0(o)) != NULL) {
            if (o == a) continue;
            if (!func_00123330(o)) continue;
            if (o == a->o398) continue;
            if (o->o398 == a) continue;
            if (o == a->o98) continue;
            if (o->o98 == a) continue;
            for (j = 0; j < o->cs->n; j++) {
                if (o->mask & (1 << j)) continue;
                func_0015bad0(o, &o->cs->cols[j], cap->c);
                if (func_0015b998(cap, cap->c)) {
                    func_0015c5d0(cap, cap->c, t);
                    func_00143660((Ch *)a, v, (Ch *)o, t);
                    func_00267530(cap->b, cap->b, t);
                    func_00267530(v, v, t);
                    func_00142fe0(a, o);
                }
            }
        }
    }
    func_001220b8(cap);
}
