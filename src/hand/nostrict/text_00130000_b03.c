/* Hand-matched functions (worker b03), built without strict aliasing. */
#include "common.h"

typedef struct { u8 pad[0xcc]; f32 xcc; } B3Mv;
typedef struct {
    f32 x0[4];
    f32 x10[4];
    f32 x20[4];
    u8 pad30[0x40 - 0x30];
    f32 x40[4];
    f32 x50;
    f32 x54;
    u8 pad58[0x5c - 0x58];
    s32 x5c;
    u8 pad60[0x90 - 0x60];
    s32 x90;
    s32 x94;
    u8 pad98[0xa0 - 0x98];
    f32 xa0[4];
    f32 xb0, xb4, xb8, xbc;
    u8 padc0[0x100 - 0xc0];
    f32 x100;
    u8 pad104[0x170 - 0x104];
    f32 x170;
} B3Wk;
typedef struct { u8 pad[0x4c]; u16 x4c; } B3Inf;
typedef struct B3Ob {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 x10[4];
    f32 x20[4];
    f32 x30[3];
    f32 x3c;
    u8 pad40[0x6c - 0x40];
    B3Mv *x6c;
    u32 x70;
    u8 pad74[0x88 - 0x74];
    u32 x88;
    u8 pad8c[0x98 - 0x8c];
    void *x98;
    u32 x9c;
    u8 padA0[0xc0 - 0xa0];
    f32 xc0[3];
    f32 xcc;
    u8 padd0[0x130 - 0xd0];
    B3Inf *x130;
    u8 pad134[0x144 - 0x134];
    s32 x144;
    B3Wk *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[0x16c - 0x168];
    f32 x16c;
    u8 pad170[0x178 - 0x170];
    s32 x178;
    u8 pad17c[0x1cc - 0x17c];
    u32 x1cc;
    u8 pad1d0[0x280 - 0x1d0];
    f32 x280;
    u8 pad284[0x2a0 - 0x284];
    f32 x2a0[4];
    u8 pad2b0[0x2c0 - 0x2b0];
    f32 x2c0;
    u8 pad2c4[0x2cc - 0x2c4];
    s32 x2cc;
    u32 x2d0;
    f32 x2d4;
    u16 x2d8;
    u8 pad2da[0x2de - 0x2da];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x320 - 0x30e];
    f32 x320[4];
    u8 pad330[0x340 - 0x330];
    f32 x340[4];
    s32 x350[4];
    u8 pad360[0x370 - 0x360];
    u64 x370;
    s32 x378;
    u8 pad37c[0x398 - 0x37c];
    struct B3Ob *x398;
    u8 x39c;
    u8 pad39d;
    u8 x39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 x3c0[4];
    s32 x3d0;
    u8 pad3d4[0x3e4 - 0x3d4];
    f32 x3e4;
    u16 x3e8;
    u8 pad3ea[0x440 - 0x3ea];
    u64 x440;
    s32 x448;
    u8 pad44c[0x490 - 0x44c];
    f32 x490[4];
    u8 pad4a0[0x4ac - 0x4a0];
    f32 x4ac;
} B3Ob;
extern f32 D_002BBDFC;
extern u32 D_002C5958;
void func_00130340(B3Ob *o, s32 a, f32 f);
void func_00130398(B3Ob *o, s32 a, f32 f);
void *func_00130578(B3Ob *, s32, f32);
void func_002675a8(f32 *, f32 *);
typedef struct { u32 type:8; u32 id:16; u32 b24:1; u32 f25:1; u32 hi:6; void *x4; s32 x8; } B3Ev;
extern f32 D_002C58B0[4];
typedef struct {
    u8 x0, x1, x2, x3, x4, x5, x6, x7;
    u8 x8[16];
    u8 x18;
    u8 x19[8];
    u8 x21;
    u8 x22[16];
    u8 x32, x33, x34, x35;
    u16 x36, x38, x3a;
    s32 x3c;
    u8 x40[48];
    u8 x70[4];
} B3SvEnt;
typedef struct {
    B3SvEnt e[10];
    u8 x488[2];
    u8 x48a;
    u8 x48b[3];
    u8 x48e[7];
    u8 x495[256];
    u8 x595[48];
    u8 x5c5[0x7cc - 0x5c5];
    u8 x7cc[7];
    u8 x7d3[0x840 - 0x7d3];
    u8 x840[3];
} B3SvSub;
typedef struct {
    s32 x0;
    B3SvSub b;
} B3Sv;
extern B3Sv *D_00304BE8;

extern f32 D_002C5970;
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00121fc4(f32 *, f32 *);
void func_0014f658(B3Ob *o, s32 t);
void func_0013f6d0(B3Ob *, f32 *);
s32 func_0013f330(B3Ob *, s32);

void func_0013f910(B3Ob *o, f32 *v) {
    f32 t[4];
    f32 y, c, f;
    B3Wk *w;
    s32 k;

    func_00267560(v, v, v[3] * D_002BBDFC);
    if ((o->x2d0 & 0x10) && v[1] > 0.0f) {
        func_0014f658(o, 14);
        func_0013f6d0(o, o->x20);
        return;
    }
    func_00267518(t, v, o->x10);
    y = t[1];
    func_00267530(t, t, o->x148->x40);
    t[1] = 0.0f;
    func_002673b8(t, t);
    func_00267560(t, t, o->x148->x50 + o->x2c0);
    func_00267518(t, t, o->x148->x40);
    w = o->x148;
    if (y < w->x54) {
        t[1] = w->x54;
    } else if (w->x40[1] < y) {
        t[1] = w->x40[1];
    } else {
        t[1] = y;
    }
    func_00267530(t, t, o->x10);
    func_00121fc4(o->x20, t);
    o->x20[3] *= D_002C5970;
    if (o->x0 & 4) return;
    if (o->x20[1] < 0.0f && 1.0f < o->x20[3]) {
        k = 30;
    } else if (0.0f < o->x20[1]) {
        k = 32;
        if (7.0f < o->x20[3]) k = 31;
    } else {
        func_00267530(t, o->x10, o->x148->x40);
        c = t[0] * v[2] - t[2] * v[0];
        if (c < 0.0f) {
            k = 34;
        } else if (0.0f < c) {
            k = 33;
        } else {
            if (o->x1cc & 0x100000) return;
            if (o->x178 > 0) return;
            k = 27;
        }
    }
    if ((o->x164 == 27 || o->x164 == 36) && k == 30) {
        f = 0.0f;
    } else {
        f = 8.0f;
    }
    if (!((s32)(o->x440 >> 33) & 1)) {
        func_00130398(o, func_0013f330(o, k) | 0x40000000, f);
    }
}

typedef struct {
    u8 pad08[0x1c - 0x8];
    f32 x1c, x20, x24, x28, x2c, x30, x34, x38;
    s32 x3c, x40, x44, x48, x4c, x50;
    u8 pad54[0x5c - 0x54];
    f32 x5c;
    u8 pad60[0x68 - 0x60];
    s32 x68;
    u8 pad6c[0x78 - 0x6c];
    f32 x78[16];
    s32 xb8;
    u8 xbc;
    u8 xbd;
    u16 xbe, xc0, xc2;
    f32 xc4;
    B3SvEnt *xc8;
    u8 padcc[0xd0 - 0xcc];
    u8 xd0, xd1;
    u8 padd2[0xd4 - 0xd2];
    f32 xd4;
    u8 padd8[0xe0 - 0xd8];
    s32 xe0;
} B3StB;
typedef struct {
    s32 x0, x4;
    B3StB b;
} B3St;
typedef struct { u8 pad[0x30]; s8 x30; u8 pad31[7]; s8 x38; } B3Eq;
typedef struct { s8 x0, x1, x2, x3, x4, x5; s8 x6[16]; } B3It;
extern f32 D_00304C48[];
B3Eq *func_00149740(s32);
B3It *func_00147860(s32);
s32 func_0013c968(s32, s32);
s32 func_0013c598(s32);

void func_00141b10(s32 n, B3St *p) {
    B3StB *b;
    B3SvEnt *e = &D_00304BE8->b.e[n];
    B3Eq *r;
    B3It *q;
    s32 i, j;

    p->b.x40 = e->x2;
    p->b.x48 = e->x4;
    p->b.xbe = e->x38;
    p->b.x4c = e->x6;
    p->b.x50 = e->x7;
    p->b.xe0 = e->x5;
    p->b.xc0 = 0;
    p->b.xc2 = 0;
    p->b.xc4 = 1.0f;
    p->b.xb8 = 0;
    p->b.xbc = 0;
    for (i = 0, b = &p->b; i < 16; i++) p->b.x78[i] = e->x8[i] / 100.0f;
    r = func_00149740(n);
    if (r) {
        p->b.x4c += r->x30;
        p->b.x48 += r->x38;
    }
    for (i = 0; i < e->x18; i++) {
        if (e->x19[i]) {
            q = func_00147860(e->x19[i]);
            p->b.x40 += q->x0;
            p->b.x48 += q->x1;
            p->b.x4c += q->x2;
            p->b.x50 += q->x3;
            p->b.xe0 += q->x4;
            for (j = 0; j < 16; j++) b->x78[j] *= q->x6[j] / 100.0f;
        }
    }
    p->b.x3c = (e->x1 < p->b.x40) ? e->x1 : p->b.x40;
    p->b.x44 = (e->x3 < p->b.x48) ? e->x3 : p->b.x48;
    p->b.xbe = (e->x38 < p->b.x48 * 30) ? e->x38 : p->b.x48 * 30;
    p->b.x4c = (p->b.x4c < 101) ? p->b.x4c : 100;
    p->b.x50 = (p->b.x50 < 101) ? p->b.x50 : 100;
    p->b.xe0 = (p->b.xe0 < 101) ? p->b.xe0 : 100;
    p->b.xc8 = e;
    p->b.xd0 = func_0013c968(6, n) + 3;
    p->b.xd1 = func_0013c968(7, n) + 3;
    p->b.xd4 = (f32)func_0013c968(8, n) + 1.0f;
    p->b.x5c = D_00304C48[n];
    p->b.x68 = func_0013c598(n);
    p->b.x1c = 1.0471974909305573f;
    p->b.x38 = 0.87266458570957184f;
    p->b.x2c = 0.34906581789255142f;
    p->b.x20 = 1.570796400308609f;
    p->b.x34 = 0.87266458570957184f;
    p->b.x30 = 0.34906581789255142f;
    p->b.x24 = 0.017453290987759829f;
}

typedef struct { B3Ob *x0; s32 x4, x8, xc; } B3Tbl;
extern B3Tbl D_003044E0[];
extern B3Ob *D_002E26A0[];
f32 func_001427d0(B3Ob *, f32 *);
s32 func_0015c738(B3Ob *, f32 *);
void func_00137440(B3Ob *, s32);
void func_00143818(B3Ob *, f32 *, s32);
void func_00121fc4(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_002673b8(f32 *, f32 *);
void func_00143180(B3Ob *, f32 *);
void func_00151b98(B3Ob *, f32 *);
void func_001337e0(s32 a, void *b, s32 c);
void func_00117710(f32 *, f32 *);

void func_00143a70(B3Ob *o, f32 *v, s32 a2) {
    f32 t[4];
    f32 f, step;
    u32 fl;
    u16 last;
    B3Ob *p;
    s32 i;
    u16 k;

    f = func_001427d0(o, o->x2a0);
    step = (f < o->x4ac) ? f : o->x4ac;
    o->x4ac = f;
    if (o->x398) o->x370 &= ~0x20000000000000ULL;
    func_00137440(o, func_0015c738(o, v));
    func_00143818(o, v, a2);
    func_00121fc4(t, v);
    if (t[3] / step > 4.0f) t[3] = step * 4.0f;
    last = 0;
    fl = 1;
    do {
        if (step < t[3]) {
            func_00267560(v, t, step);
            t[3] -= step;
        } else {
            func_00267560(v, t, t[3]);
            t[3] = 0.0f;
        }
        func_001427d0(o, o->x2a0);
        func_00143180(o, v);
        fl |= o->x2d0 & ~1;
        fl &= (o->x2d0 & 1) | ~1;
        if (o->x130->x4c == 201) func_00151b98(o, v);
        func_00267518(o->x10, o->x10, v);
        if (o->x2d8) {
            k = o->x2d8;
            if (k != last) {
                if ((o->x2d0 & 4) || o == D_002E26A0[0]) {
                    func_001337e0(-2, o, k);
                }
                last = o->x2d8;
            }
        }
        o->x448 = o->x2d8;
    } while (t[3] > 0.0f);
    o->x2d0 = fl;
    func_00117710(o->x2a0, o->x320);
    func_002673b8(o->xc0, o->x340);
    o->xcc = 1.0f;
    p = o->x398;
    if (o->x2cc != -1) {
        p = D_003044E0[o->x2cc].x0;
        if (!(o->x2d0 & 1)) func_00137440(o, (s32)p);
    }
    if (p) {
        for (i = 0; i < 4; i++) o->x350[i] = p->x350[i];
    }
}

#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/pieces/D_00304D64.h"
extern u32 D_002C5BB4;
extern f32 D_002C5970;
s32 func_001232f0(B3Ob *);
void func_00121fc4(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
s32 func_00137660(B3Ob *);
void func_00144810(B3Ob *, f32 *);
f32 atan2f(f32, f32);

void func_00144958(B3Ob *o, f32 *v) {
    f32 t[4];
    f32 h, k, r, s, sc, nh;

    if (!func_001232f0(o)) {
        func_002675a8(o->x20, v);
        func_002675a8(o->x148->xa0, D_002C58B0);
        o->x148->xb0 = 0.0f;
        return;
    }
    func_002675a8(t, o->x148->xa0);
    t[1] = 0.0f;
    func_00121fc4(t, t);
    if (0.0f < o->x148->xb0) {
        if (0.0f < o->x148->xbc) {
            sc = 0.0f;
            s = 1.0f;
            o->x148->xbc -= D_002BBDFC;
        } else {
            if (o->x148->xb4 < o->x148->xb0) {
                s = o->x148->xb8;
                if (!(D_002C5BB4 & 4)) o->x148->xb0 = o->x148->xb4;
                sc = 0.0f;
            } else {
                r = o->x148->xb0 / o->x148->xb4;
                s = (o->x148->xb8 - 4.0f) * r + 4.0f;
                sc = r * -0.5f + 0.5f;
            }
            o->x148->xb0 -= D_002BBDFC;
        }
        func_00267560(t, t, s);
        t[3] = s;
    } else {
        sc = 0.5f;
        func_00267e90(t, t, t[3]);
        if (func_00137660(o)) {
            if (0.0f < v[3]) {
                func_00130398(o, 46, 16.0f);
            } else {
                func_00130398(o, 45, 16.0f);
            }
        }
    }
    h = o->x2d4 + D_00304D64[o->x130->x4c].x0 - o->x10[1];
    t[1] = h;
    nh = -h;
    if (h < 0.0f) {
        k = h * (D_002C5970 * 0.015f);
    } else {
        k = h * (D_002C5970 * 0.1f);
    }
    t[1] = k + o->x3c0[1];
    o->x3c0[1] = t[1] * 0.8f;
    func_002675a8(o->x20, t);
    if (t[0] != 0.0f && t[2] != 0.0f) o->x150 = atan2f(t[0], t[2]);
    if (0.0f < v[3]) {
        s = (20.0f < nh) ? 2.0f : 4.0f;
        func_00267560(v, v, sc);
        func_00267518(v, v, t);
        v[1] = 0.0f;
        func_00121fc4(v, v);
        func_00267560(t, v, v[3] < (t[3] < s ? s : t[3]) ? v[3] : (t[3] < s ? s : t[3]));
    } else {
        func_00267560(t, t, 0.9f);
    }
    func_002675a8(o->x148->xa0, t);
    func_00144810(o, v);
}

#include "data/types/nostrict_text_00130000_b03.h"
typedef struct {
    u8 pad0[0x10];
    union {
        u64 x;
        struct { u16 lo; u16 x12; u16 x14; u8 x16; u8 x17; } s;
        struct { u64 b0:2; u64 kind:16; u64 rest:46; } b;
    } x10;
    f32 x18;
    s32 x1c;
    f32 x20[4];
} B3Pj;
typedef struct { f32 x0; s32 x4, x8, xc, x10; } B3PjInf;
extern B3PjInf D_00304DB0[];
extern B3Col *D_00531B60;
extern f32 D_002C58A0[4];
void func_00116660(B3Col *);
void func_001166e8(B3Col *);
void func_00121fc4(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_001473a8(s32, s32, f32 *);
f32 fabsf(f32);

void func_00145528(B3Pj *o, f32 *v) {
    f32 t[4];
    f32 f;

    if (o->x10.s.x12) {
        o->x10.s.x12--;
        return;
    }
    f = D_00304DB0[o->x10.s.x14].x0;
    func_00116660(D_00531B60);
    D_00531B60->x20 = 55.0f;
    D_00531B60->x24 = 60.0f;
    func_002675a8(D_00531B60->x0, v);
    D_00531B60->x0[1] += f;
    D_00531B60->x28 = 33;
    if (o->x10.x & 0x10) {
        func_002675a8(D_00531B60->x10, D_002C58A0);
        o->x10.x &= ~0x10;
    } else {
        func_00121fc4(t, o->x20);
        if (45.0f < t[3]) func_00267560(o->x20, t, 45.0f);
        func_002675a8(D_00531B60->x10, o->x20);
        D_00531B60->x10[3] = 1.0f;
    }
    func_001166e8(D_00531B60);
    if (0.0f <= o->x20[1] && !(D_00531B60->x30 & 1)) {
        if (5.0f < o->x20[1]) {
            o->x20[1] *= -0.8f;
            if (++o->x10.s.x17 < 3) func_001473a8(D_00304DB0[o->x10.s.x14].xc, 0, D_00531B60->x40);
        } else {
            func_002675a8(o->x20, D_002C58A0);
            if (D_00531B60->x2c == -1) {
                o->x10.s.x16 = 1;
            } else {
                o->x10.s.x12 = 30;
            }
        }
    } else {
        func_00267530(t, D_00531B60->x40, D_00531B60->x0);
        if (0.1f < fabsf(t[0] - o->x20[0])) o->x20[0] = -o->x20[0];
        if (0.1f < fabsf(t[2] - o->x20[2])) o->x20[2] = -o->x20[2];
    }
    func_002675a8(v, D_00531B60->x40);
    v[1] -= f;
    v[3] = 1.0f;
    o->x20[1] += 3.0f;
    o->x20[0] *= 0.95f;
    o->x20[2] *= 0.95f;
    if (0.0f < o->x20[1]) o->x10.x |= 2;
}

typedef struct {
    u8 pad0[0x88];
    u32 x88;
    u8 pad8c[0x160 - 0x8c];
    union {
        struct { u64 b0:8; s64 b8:32; u64 b40:24; } f;
        struct { u32 lo; s32 hi; } w;
        u64 x;
    } x160;
    u8 pad168[0x370 - 0x168];
    u8 x370[3];
} C3Ob;
typedef struct {
    void *x0;
    u8 pad4[0xc - 0x4];
    f32 *xc;
    u8 pad10[0x14 - 0x10];
    u32 x14;
    u8 pad18[0x20 - 0x18];
    u8 *x20;
} C3Lk;
typedef struct {
    u32 x0;
    u8 x4;
    u8 pad5;
    s16 x6;
    u32 x8;
    f32 xc;
    f32 x10[4];
    f32 x20[4];
    f32 x30[12];
    f32 x60[4];
} C3D;
typedef struct {
    u8 pad0[0x10];
    C3Ob *x10;
    C3Lk *x14;
    u8 pad18[0x20 - 0x18];
    C3D *x20;
} C3S;
s32 func_00122ff8(C3Ob *);
void func_00176310(C3Lk *);
void func_00121eb0(C3D *);
void func_001315c0(s32, s32, f32, f32 *);
void func_001318e8(C3Ob *, u32, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00147e08(C3Lk *, f32 *);

s32 func_001480d0(C3S *s) {
    s32 f = 0;
    C3D *d = s->x20;
    f32 *v;
    u32 m;
    s32 i;

    if (!s->x14 || (s->x14->x14 & 3) != 1) {
        s->x14 = 0;
        goto fail;
    }
    if (!func_00122ff8(s->x10)) goto fail;
    if (d->x6 == -1) {
        d->x6 = s->x10->x160.w.hi;
    } else if (d->x6 >= 0) {
        if (s->x10->x160.w.hi != d->x6) f = 1;
        else if (((s32)((s64)(s->x10->x160.x << 24) >> 32) & 1)) {
        fail:
            f = 1;
        }
    }
    if (f) {
        if (s->x14) func_00176310(s->x14);
        func_00121eb0(d);
        return 4;
    }
    if (s->x10->x88 & 1) s->x14->x20[0] |= 4;
    else s->x14->x20[0] &= ~4;
    if (d->x0 & 1) {
        for (i = 0; i < 3; i++) s->x14->xc[i] = s->x10->x370[i] * (1.0f / 128.0f);
    }
    if (s->x14->x14 & 0x10) return 0;
    if (d->x8 & 0x10000) {
        m = d->x8 & ~0x10000;
        switch (d->x4) {
        case 1:
            v = d->x20;
            func_001315c0((s32)s->x10, m, d->xc, v);
            func_00267518(v, v, d->x10);
            func_002675a8(s->x14->x0, v);
            break;
        case 2:
            v = d->x30;
            func_001318e8(s->x10, m, v);
            func_00147e08(s->x14, v);
            break;
        case 3:
            v = d->x30;
            func_001318e8(s->x10, m, v);
            func_001315c0((s32)s->x10, m, d->xc, d->x60);
            func_00147e08(s->x14, v);
            break;
        }
        func_00121eb0(d);
        return 4;
    }
    switch (d->x4) {
    case 1:
        v = d->x20;
        func_002675a8(s->x14->x0, v);
        func_001315c0((s32)s->x10, d->x8, d->xc, v);
        func_00267518(v, v, d->x10);
        break;
    case 2:
        v = d->x30;
        func_00147e08(s->x14, v);
        func_001318e8(s->x10, d->x8, v);
        break;
    case 3:
        v = d->x30;
        func_00147e08(s->x14, v);
        func_001318e8(s->x10, d->x8, v);
        func_001315c0((s32)s->x10, d->x8, d->xc, d->x60);
        break;
    }
    return 0;
}

/* needs make: uses rodata */
void func_00141720(B3Ob *);
void func_0012bd98(B3Ob *, s32, u32, f32 *);
void func_00140d50(B3Ob *, f32 *);
void func_0013f6d0(B3Ob *, f32 *);
void func_00153e80(B3Ob *);
void func_00171fa0(B3Ob *);
void func_0013e000(B3Ob *);
void func_001550a0(B3Ob *, f32 *);
f32 func_00121b08(f32);
s32 func_001375d8(B3Ob *);

void func_0013e1f8(B3Ob *o, f32 *v) {
    func_00141720(o);
    func_002675a8(v, o->x20);
    if (o->x0 & 0x400) {
        switch (o->x70) {
        case 0:
        case 30:
            switch (o->x378) {
            case 31:
                func_0012bd98(o, o->x39e, 0x80000008, o->x10);
            case 2:
            case 3:
            case 16:
            case 21:
                func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
                func_00130578(o, (o->x0 & 0x2000) ? 0x400000ab : 0x40000000, 8.0f);
                o->x148->x90 = 0xffff;
                func_002675a8(v, o->x30);
                v[3] = 0.0f;
                break;
            case 10:
                func_00140d50(o, v);
                break;
            case 13:
                func_0013f6d0(o, v);
                break;
            case 17:
                if (o->x164 == 0x6c) {
                    func_00153e80(o);
                } else {
                    func_00130340(o, 0x40000000, 8.0f);
                }
                break;
            }
            break;
        case 2:
            func_00171fa0(o);
            func_00130398(o, 6, 8.0f);
            break;
        case 27:
            func_00130340(o, 0x10000bc, 6.0f);
            func_00130578(o, 0x400000bd, 0.0f);
            break;
        case 6:
            if (o->x378 == 2) {
                func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
                func_00130578(o, 0x400000ab, 8.0f);
                o->x148->x90 = 0xffff;
                func_002675a8(v, o->x30);
                v[3] = 0.0f;
            }
            break;
        case 8:
            if (!((s32)(o->x440 >> 33) & 1) && !((s32)(o->x370 >> 60) & 1)) {
                func_00130398(o, 0x75, 16.0f);
            }
            break;
        }
        o->x0 &= ~0x400;
    }
    func_0013e000(o);
    func_001550a0(o, v);
    if (!(o->x0 & 4)) o->x3e8 = 0;
    o->x148->x100 = func_00121b08(o->x148->x100);
    if (o->x88 & 8) {
        o->x148->x170 -= D_002BBDFC;
        if (o->x148->x170 < 0.0f || (D_002C5958 & 0x104000) || func_001375d8(o)) {
            o->x88 &= ~8;
            o->x148->x170 = 0.0f;
        }
    }
}

s32 func_00133000(B3Ob *o, s32 id);
void func_001333e0(B3Ob *o, s32 id, void *p);
void func_0013bb60(B3Ob *o, s32 id);
void func_0012c560(B3Ob *o, void *a, s32 id);
void func_001337e0(s32 a, void *b, s32 c);
void func_001376e8(B3Ob *o, f32 *q);
void func_00137330(void *a, B3Ob *o, s32 t);
void func_0014f658(B3Ob *o, s32 t);
void func_001519c0(B3Ob *o, void *a);
void func_00121fc4(f32 *, f32 *);

void func_0013e638(B3Ob *o, B3Ev *e, f32 *q) {
    f32 d;
    s32 k;
    switch (e->type) {
    case 0:
        break;
    case 2:
        if (func_00133000(o, e->id)) {
            if (!e->id) {
                func_00130340(o, 0x1000036, 0.0f);
                func_00130578(o, 61, 0.0f);
            } else {
                func_00130340(o, (e->id + 54) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000000, 0.0f);
            func_001333e0(o, e->id, &e->x4);
        }
        break;
    case 6:
        func_0013bb60(o, e->id);
        break;
    case 3:
        if (!e->x4 || e->x4 == o) {
            func_00130340(o, 0x100003e, 8.0f);
        } else {
            func_00130340(o, 0x100003f, 8.0f);
        }
        func_00130578(o, 0x40000000, 8.0f);
        func_0012c560(o, e->x4, e->id);
        break;
    case 4:
        o->x370 &= ~0x4000000000000ULL;
        func_00130398(o, 0x40000000, 16.0f);
        func_001337e0(0, e->x4, 0);
        func_002675a8(o->x3c0, D_002C58B0);
        break;
    case 5:
        o->x370 &= ~0x4000000000000ULL;
        func_00130398(o, 0x40000000, 16.0f);
        func_001337e0(4, e->x4, 0);
        func_002675a8(o->x3c0, D_002C58B0);
        break;
    case 28:
        func_001376e8(o, q);
        d = o->x10[1] - ((B3Ob *)e->x4)->x10[1];
        if (d < 20.0f) {
            k = 181;
        } else if (d < 80.0f) {
            k = 183;
        } else {
            k = 184;
        }
        func_00130340(o, k | 0x1000000, 8.0f);
        func_00130578(o, 0x400000b6, 0.0f);
        func_00137330(e->x4, o, 28);
        func_0014f658(o, 28);
        break;
    case 55:
        func_001519c0(o, e->x4);
        break;
    case 30:
        func_00137330(o->x98, o, e->type);
        break;
    default:
        func_001376e8(o, q);
        func_00137330(e->x4, o, e->type);
        break;
    }
    func_00121fc4(q, q);
    q[3] = 0.0f;
}

typedef struct { f32 x0[4]; f32 x10, x14; u64 x18; } B3PjE;
extern B3Pj D_0052EB60[]; /* src/data/bss_0052.c: u8 D_0052EB60[0x3000] */
extern B3PjE D_0035C710[];
extern f32 *D_00531B68;
extern f32 D_002C58D0[4];
extern f32 D_00306840;
void func_00145858(B3Pj *, B3PjE *);
s32 func_00145aa0(B3Pj *, B3PjE *);
void func_00267810(f32 *, f32 *, f32);
void func_002672f8(f32 *, f32 *, f32 *);
void func_00267e40(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_001315c0(s32, s32, f32, f32 *);
void func_00267518(f32 *, f32 *, f32 *);

s32 func_00145ce8(B3Pj *o) {
    f32 t[4];
    f32 u[4];
    f32 m[16];
    f32 s, r, a;
    B3PjE *e = &D_0035C710[o - D_0052EB60];

    switch (o->x10.s.x16) {
    case 0:
        switch ((u16)(o->x10.x >> 2) & 3) {
        case 0:
            func_00145528(o, e->x0);
            break;
        case 1:
            func_00145858(o, e);
            break;
        case 2:
            o->x10.x |= 2;
            o->x10.s.x16 = 1;
            break;
        }
    case 1:
        if (o->x10.x & 2) {
            if ((o->x1c = func_00145aa0(o, e))) {
                o->x10.s.x16 = 2;
                o->x18 = 40.0f;
                break;
            }
        }
        if (0.0f < o->x18) {
            o->x18 -= D_002BBDFC;
            if (o->x18 <= 0.0f || (D_00531B68 && e->x0[1] > D_00531B68[2])) {
                o->x10.s.x16 = 3;
                o->x18 = 12.0f;
            }
        }
        break;
    case 2:
        r = o->x18 / 40.0f;
        s = o->x20[3] * r;
        a = 30.0f / s;
        func_00267810(m, D_002C58D0, (a < 0.59341193735599518f) ? a : 0.59341193735599518f);
        func_002672f8(u, m, o->x20);
        func_00267e40(o->x20, u);
        func_00267e90(u, o->x20, s);
        func_001315c0(o->x1c, 0x8003, 0.0f, t);
        func_00267518(e->x0, t, u);
        e->x10 = r;
        o->x18 -= D_002BBDFC;
        if (o->x18 <= 0.0f) {
            e->x18 &= ~0x100;
            return 4;
        }
        break;
    case 3:
        r = o->x18 / 12.0f;
        e->x10 = r;
        o->x18 -= D_002BBDFC;
        if (o->x18 <= 0.0f) {
            e->x18 &= ~0x100;
            return 4;
        }
        break;
    case 4:
        if (o->x18 < 0.0f) {
            e->x18 |= 0x200;
        } else {
            r = o->x18 / D_00306840;
            e->x10 = r;
        }
        o->x18 = o->x18 - 1.0f;
        break;
    case 5:
        e->x18 &= ~0x200;
        if (o->x18 < 0.0f) {
            e->x10 = 1.0f;
            o->x18 = 900.0f;
            o->x10.s.x16 = 0;
        } else {
            r = o->x18 / D_00306840;
            e->x10 = 1.0f - r;
            o->x18 = o->x18 - 1.0f;
        }
        break;
    }
    return 0;
}

#include "data/types/nostrict_text_00130000_b03_p.h"
typedef struct {
    union { u64 x; struct { s32 lo; s32 x4; } s; } x0;
    u16 x8;
    u8 pada[2];
    B3Ob *xc;
} B3Se;
extern B3SeRow D_00306850[];
extern s32 D_002BC128;
extern s32 D_002C5C4C;
s32 func_001063c8(void);
s32 func_0012bd30(B3Ob *);
s32 func_00137450(s32);
s32 func_00105bc0(s32, s32);
void func_001473a8(s32, s32, f32 *);
s32 func_00147240(s32, s32);
B3Se *func_00146bd0(s32, s32);
void func_0011d1e0(s32, s32, f32 *, s32);

static inline u8 b3next(B3Ob *o) { u8 c = o->x39c; o->x39c = (c + 1) & 3; return c; }
void func_00146c98(B3Ob *o, u32 k) {
    B3SeRow *tb;
    u32 id;
    s32 t, n, m, b;
    u8 c;
    B3Se *p;

    if ((D_002C5958 >> 10) & 1) return;
    if (o->x9c & 1) return;
    if (func_001063c8()) return;
    if (((s32)(o->x370 >> 37) & 3) != 2 && !(o->x0 & 1)) return;
    t = o->x130->x4c;
    if (t >= 21) return;
    if (t >= 3) switch (t) {
    case 4:
        t = 1;
        break;
    case 17:
        t = 2;
        break;
    default:
        t = 3;
        break;
    }
    tb = &D_00306850[D_002BC128 * 4 + t];
    id = 15;
    if (!D_002C5C4C) {
        id = o->x39e;
        switch (k) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            if (!func_0012bd30(o)) return;
            if ((k & 1) != (o->x39c & 1)) b3next(o);
            k = (k & ~3) + b3next(o);
            break;
        case 14: case 15: case 16:
            if (o->x2de != 0xffff) {
                id = func_00105bc0(-1, o->x2de);
            } else if (o->x30c != 0xffff) {
                id = func_00105bc0(-1, o->x30c);
            } else {
                return;
            }
            break;
        case 17:
            id = func_00105bc0(func_00137450(o->x148->x94), o->x148->x90);
            break;
        case 18: case 19: case 20: case 21: case 22: case 23:
            id = func_00105bc0(-1, o->x148->x5c);
            break;
        case 26: case 27: case 28: case 29:
            n = tb->x[13];
            if (!n) return;
            k = k * 2 + (o->x39c & 1) - 52;
            b3next(o);
            func_001473a8(n + k, o->x4 + 1, o->x10);
            return;
        }
    }
    if (!id) return;
    n = (tb->x - 1)[id];
    if (!n) return;
    id = o->x4 + 1;
    if (k - 21 < 2 || k == 24) {
        k += n;
        if (func_00147240(k, id)) return;
        p = func_00146bd0(k, id);
    } else if (D_002C5C4C && k - 14 < 2) {
        p = func_00146bd0(k + n, id);
    } else {
        goto call;
    }
    if (p) {
        func_0011d1e0(p->x8, p->x0.s.x4, o->x10, 0);
        p->x0.x |= 4;
        p->xc = o;
    }
    goto end;
call:
    func_001473a8(n + k, id, o->x10);
end:;
}

#include "data/bss_0053_mixed.h"
#include "data/bss_0053_typed.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5BB0.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002C5970.h"
#include "data/pieces/D_00306850.h"
