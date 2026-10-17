/* Hand-matched functions (worker b03), built without strict aliasing. */
#include "common.h"

typedef struct { u8 pad[0xcc]; f32 xcc; } B3Mv;
typedef struct {
    u8 pad0[0x40];
    f32 x40[4];
    f32 x50;
    f32 x54;
    u8 pad58[0x90 - 0x58];
    s32 x90;
    u8 pad94[0x100 - 0x94];
    f32 x100;
    u8 pad104[0x170 - 0x104];
    f32 x170;
} B3Wk;
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
    u8 pad9c[0x144 - 0x9c];
    s32 x144;
    B3Wk *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[0x178 - 0x168];
    s32 x178;
    u8 pad17c[0x1cc - 0x17c];
    u32 x1cc;
    u8 pad1d0[0x280 - 0x1d0];
    f32 x280;
    u8 pad284[0x2c0 - 0x284];
    f32 x2c0;
    u8 pad2c4[0x2d0 - 0x2c4];
    u32 x2d0;
    u8 pad2d4[0x370 - 0x2d4];
    u64 x370;
    s32 x378;
    u8 pad37c[0x39e - 0x37c];
    u8 x39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 x3c0[4];
    s32 x3d0;
    u8 pad3d4[0x3e4 - 0x3d4];
    f32 x3e4;
    u16 x3e8;
    u8 pad3ea[0x440 - 0x3ea];
    u64 x440;
} B3Ob;
extern f32 D_002BBDFC;
extern u32 D_002C5958;
void func_00130340(B3Ob *o, s32 a, f32 f);
void func_00130398(B3Ob *o, s32 a, f32 f);
void *func_00130578(B3Ob *, s32, f32);
void func_002675a8(f32 *, f32 *);
typedef struct { u32 type:8; u32 id:16; u32 b24:1; u32 f25:1; u32 hi:6; void *x4; s32 x8; } B3Ev;
extern f32 D_002C58B0[4];

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

