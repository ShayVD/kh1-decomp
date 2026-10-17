/* Hand-matched functions (batch b04). */
#include "common.h"

typedef struct {
    union {
        u64 x;
        struct { u64 b0:2; u64 b2:2; u64 b4:2; u64 b6:4; u64 b10:1; u64 f11:1; u64 b12:2; u64 b14:1; u64 b15:1; u64 b16:1; u64 b17:3; u64 b20:1; u64 r:43; } b;
        struct { u32 lo; u32 hi; } w;
    } f;
    s32 x8;
    f32 xc;
    u8 pad10[0x20 - 0x10];
    s32 x20;
    f32 x24;
    f32 x28;
    s32 x2c;
    union { u64 x; struct { u64 b0:5; u64 b5:1; u64 b6:4; u64 b10:1; u64 r:53; } b; struct { u32 lo; void *hi; } w; } x30;
    s32 x38_;
    f32 x3c;
    u8 pad40[0x50 - 0x40];
    f32 x50;
    u32 x54;
    s32 x58;
    void *x5c;
    s32 x60;
    s32 x64;
    u8 pad68[0x70 - 0x68];
    u8 x70[0x10];
    u8 x80[0x10];
    void *x90;
    f32 x94;
    s32 x98;
    s32 x9c;
    s32 xa0;
    f32 xa4;
    u8 pada8[4];
    f32 xac;
    s32 xb0;
    s32 xb4;
    s32 xb8;
    u8 xbc[4];
} B4P;

typedef struct {
    u32 x0; u32 x4; u32 x8; u8 padc[4]; s32 x10; u8 pad14[4]; s32 x18; s32 x1c;
    u8 pad20[0x34 - 0x20]; u32 x34; s32 x38; s32 x3c;
    u8 pad40[0x54 - 0x40]; f32 x54; f32 x58; f32 x5c; u8 pad60[8]; f32 x68;
} B4D;

typedef struct { u8 pad[0x48]; s32 x48; s32 x4c; u8 pad50[0x68 - 0x50]; s32 x68; u8 pad6c[0xd4 - 0x6c]; f32 xd4; u8 padd8[4]; f32 xdc; } B4Prm;
typedef struct { u8 pad[0x4c]; u16 x4c; } B4C130;
typedef struct { u8 pad[0x170]; union { u64 x; struct { u32 lo; u32 b0:5; u32 b5:1; u32 r:26; } b; } x170; } B4C148;
typedef struct {
    u8 pad[0x40]; f32 x40; u8 pad44[0x68 - 0x44]; s32 x68; B4Prm *x6c;
    u8 pad70[0x130 - 0x70]; B4C130 *x130; u8 pad134[0x148 - 0x134]; B4C148 *x148;
    u8 pad14c[0x370 - 0x14c];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b7:6; u32 b13:1; u32 hi:18; } b; } x370;
} B4Ent;

typedef struct { u8 pad[0xfe]; u8 xfe; } B4G;
extern B4G *D_00308CDC;
extern B4Ent *D_002E26A0;
extern u32 D_0054F440;
B4P *func_0014a450(void);
s32 func_0013c318(s32);
s32 func_002408d8(s32);
void func_001315c0(B4Ent *, s32, f32, void *);
void func_002675a8(void *, void *);

/* needs make: uses rodata (jump table jtbl_0048E420) */
B4P *func_0014a4a8(B4Ent *e, u32 m, B4D *d) {
    B4P *p = func_0014a450();
    s32 t;
    p->f.w.hi = 0;
    p->f.b.b4 = d->x34;
    p->f.b.b12 = (s32)(e->x370.x >> 37) & 3;
    p->f.b.b14 = 1;
    p->f.b.b10 = 0;
    p->f.b.b2 = 0;
    if (d->x38 & 0x10000) p->f.b.b20 = 1;
    p->f.b.b17 = d->x38 & 7;
    p->x64 = d->x3c;
    p->x54 = m;
    *(volatile u32 *)&D_0054F440 |= m;
    p->x90 = e;
    p->x30.w.hi = e;
    p->x8 = e->x68;
    p->x58 = 0xfff;
    switch (d->x0) {
    case 0:
        p->x2c = e->x6c->x4c;
        if (e->x148 && e->x148->x170.b.b5) {
            t = func_0013c318(e->x130->x4c);
            if (t >= 0 && func_002408d8(t)) p->x2c = p->x2c + D_00308CDC->xfe;
        }
        break;
    case 1: p->x2c = e->x6c->x48; break;
    case 2: p->x2c = 0; break;
    case 3: p->x2c = e->x6c->x48 * 2; break;
    case 4: p->x2c = e->x6c->x48 * 3; break;
    case 5: p->x2c = e->x6c->x48 * 5; break;
    case 6: p->x2c = D_002E26A0->x6c->x4c; break;
    }
    p->x30.b.b0 = d->x8;
    p->x30.b.b6 = d->x4;
    p->x30.b.b5 = 0;
    if (d->x10 >= 0) {
        p->f.b.b0 = 1;
        p->f.b.b2 = 2;
        p->x30.b.b10 = 0;
        p->x20 = d->x10;
        p->x24 = d->x54;
        p->x28 = d->x58;
        if (e->x370.b.b13) p->xc = d->x5c * e->x40;
        else p->xc = d->x5c;
    } else {
        p->f.b.b0 = 0;
        p->f.b.b2 = 0;
        p->x30.b.b10 = 1;
        p->xc = p->x3c = d->x5c;
    }
    p->x5c = d;
    p->x60 = 0;
    p->xa0 = 0;
    p->x38_ = 0;
    func_001315c0(e, 0x8003, 0.0f, p->x70);
    func_002675a8(p->x80, p->x70);
    p->f.b.b16 = 1;
    p->x94 = (f32)d->x18 * 0.0500000007f * e->x6c->xd4;
    p->x98 = d->x1c;
    p->x9c = 0;
    p->x50 = 0.0f;
    p->xa4 = 0.0f;
    p->xac = e->x6c->xdc;
    if (0.0f < d->x68) {
        s32 n = (s32)((f32)e->x6c->x68 * d->x68);
        p->xb0 = n < 1 ? 1 : n;
    } else {
        p->xb0 = 0;
    }
    p->xb8 = 0;
    p->xb4 = 0;
    return p;
}
