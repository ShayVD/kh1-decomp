/* 11w off (nostrict): only s4/s5 swap between param lv and buf (global-alloc prio 0.2439 vs 0.2474). */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4f;
typedef union {
    u64 x;
    struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b;
} B370;
typedef struct Ea4 Ea4;
struct Ea4 {
    u32 flags;
    u8 pad4[0xc];
    V4f x10;
    u8 pad20[0x74 - 0x20];
    Ea4 *x74;
    u8 pad78[4];
    Ea4 *x7c;
    s32 x80;
    u8 pad84[4];
    u32 x88;
    u8 pad8c[0x370 - 0x8c];
    B370 x370;
};
typedef struct { s32 d; Ea4 *e; } Pa4;
void *func_00122048(s32, s32);
void func_001220b8(void *);
Ea4 *func_00123158(Ea4 *, Ea4 *);
s32 func_001375d8(Ea4 *);
void func_00267530(V4f *, V4f *, V4f *);
f32 func_00120bf8(V4f *);
void func_00250360(void *, s32, s32, void *);
s32 func_0013a430();
f32 func_00176850(void);
Ea4 *func_0013a440(Ea4 *o, s32 *w, s32 lv, f32 range) {
    V4f t;
    Pa4 *buf, *p;
    Ea4 *e = 0;
    s32 n, v;
    f32 d;
    buf = func_00122048(0x300, 4);
    p = buf;
    while ((e = func_00123158(o, e)) != 0) {
        if (e->x370.b.kind == 3) continue;
        if (!(e->flags & 0x8000)) continue;
        if (e->x88 & 0x20) continue;
        if (func_001375d8(e)) continue;
        func_00267530(&t, &e->x10, &o->x10);
        d = func_00120bf8(&t);
        if (e->x80 < lv && d < range) {
            p->d = d;
            p->e = e;
            p++;
        }
    }
    n = p - buf;
    func_00250360(buf, n, 8, func_0013a430);
    if (n > 0) e = buf[0].e;
    v = func_00176850() * 100.0f;
    v -= w[0];
    if (v >= 0) {
        v -= w[1];
        if (v < 0) {
            if (n >= 2) e = buf[1].e;
        } else {
            v -= w[2];
            if (v < 0) {
                if (n > 0) e = buf[n - 1].e;
            } else {
                v -= w[3];
                if (v < 0) {
                    if (o->x74) {
                        func_00267530(&t, &o->x74->x10, &o->x10);
                        if (func_00120bf8(&t) < range) e = o->x74;
                    }
                } else {
                    if (o->x7c) {
                        func_00267530(&t, &o->x7c->x10, &o->x10);
                        if (func_00120bf8(&t) < range) e = o->x7c;
                    }
                }
            }
        }
    }
    func_001220b8(buf);
    return e;
}
