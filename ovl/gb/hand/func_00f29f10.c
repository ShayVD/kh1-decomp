/* gb.x func_00f29f10: matched by hand. */
#include "ovl.h"

typedef struct { u16 h0; u16 h2; u16 h4; u16 h6; u8 b8; u8 b9; u16 h10; } T12;
typedef struct { T12 t; u16 h12; } T14;
typedef struct { u8 pad0[6]; u16 w; u16 d; u16 h; } GbDims;
typedef struct {
    u8 pad0[0x58];
    u64 lo : 32;
    u16 px : 4;
    u16 py : 4;
    u16 pz : 4;
    u16 pr : 4;
    u16 pad5e;
    u16 h60;
    u16 h62;
    u8 pad64[0x74 - 0x64];
    u16 flags;
    u8 pad76[0xA0 - 0x76];
    GbDims dims;
    u8 padac[0x10D8 - 0xAC];
    s32 ang;
} GbWorld;
typedef struct { s32 x0, x4, x8; } Pad;
extern GbWorld *D_00F56DC0;
extern s32 D_00F56DC4;
extern s8 D_00F56DA8[];
extern s32 D_00F61370;
extern s32 D_00F61374;
extern u8 D_00379F28[];
extern u8 D_0037A028[];
void func_0011d768(s32);
T14 *func_00f24160(u16, s32);
void func_00f246e0(s32, s32, s32);
void func_00f2bfd8(void *, void *, void *, s32);
Pad *func_001ba488(s32);
void func_00f2a5e8(s32);
s32 func_00f25418(Pad *);
void func_00f2a470(s32 *, s32 *);
void func_001bbf88(void *, s32, s32);
u16 func_001bbdf0(void *);
void func_00f24240(s32, void *);
void func_001bfac8(void);
void func_00f24570(s32, s32);
void func_00f24680(T12 *);
void func_00f23e30(s32);
void func_00f24780(s32);

s32 func_00f29f10(void) {
    T14 loc;
    T12 t;
    T12 t2;
    s32 dx, dz;
    GbDims *d;
    T14 *c;
    Pad *p;
    u16 cur;
    s32 b8;
    s32 btn, dy, q, k, moved, x, y, z, ox, oy, oz, ret;
    func_0011d768(1);
    d = &D_00F56DC0->dims;
    c = func_00f24160(*(u16 *)((u8 *)D_00F56DC0 + 0x5C), D_00F56DC4);
    if (c == NULL)
        return 0;
    D_00F61370 = 1;
    loc.t = c->t;
    loc.h12 = c->h12;
    t = loc.t;
    cur = D_00F56DC0->h60;
    t.h0 = cur;
    func_00f246e0(0, cur, D_00F56DC4);
    D_00F61374 = loc.t.h4 - 1;
    func_00f2bfd8(&loc, &D_00379F28[loc.t.b8 * 4], &D_0037A028[loc.t.b8 * 4], 1);
    if (func_001ba488(0)->x4 & 0x2000) {
        do {
            func_00f2a5e8(0);
            p = func_001ba488(0);
            btn = func_00f25418(p);
            if (btn == 0) {
                dz = 0;
                moved = 0;
                dx = 0;
                func_00f2a470(&dx, &dz);
                b8 = p->x8;
                dy = 0;
                if (b8 & 0x400)
                    dy = 1;
                if (b8 & 0x100)
                    dy = -1;
                if (dx | dz | dy) {
                    x = D_00F56DC0->px;
                    y = D_00F56DC0->py;
                    z = D_00F56DC0->pz;
                    ox = x;
                    x += dx;
                    oy = y;
                    oz = z;
                    y += dy;
                    z += dz;
                    if (x < 0)
                        x = 0;
                    if (y < 0)
                        y = 0;
                    if (z < 0)
                        z = 0;
                    if (x > d->w - 1)
                        x = d->w - 1;
                    if (y > d->d - 1)
                        y = d->d - 1;
                    if (z > d->h - 1)
                        z = d->h - 1;
                    if (ox != x || oy != y || oz != z)
                        func_0011d768(20);
                    D_00F56DC0->px = x;
                    D_00F56DC0->py = y;
                    D_00F56DC0->pz = z;
                }
            } else {
                dz = 0;
                q = D_00F56DC0->ang / 1024;
                dx = 0;
                k = q * 4 + 8;
                if (btn & 0x10) {
                    dx = D_00F56DA8[k];
                    dz = D_00F56DA8[q * 4 + 10];
                }
                if (btn & 0x40) {
                    dx = -D_00F56DA8[k];
                    dz = -D_00F56DA8[q * 4 + 10];
                }
                moved = 0;
                if (dx != 0) {
                    func_001bbf88(&loc, 0, dx);
                    moved = 1;
                }
                if (dz != 0) {
                    func_001bbf88(&loc, 2, dz);
                    moved = 1;
                }
                if (btn & 0x20) {
                    func_001bbf88(&loc, 1, 1);
                    moved = 1;
                }
                if (btn & 0x80) {
                    func_001bbf88(&loc, 1, -1);
                    moved = 1;
                }
            }
            D_00F56DC0->h62 = func_001bbdf0(&loc);
            func_00f24240(D_00F56DC4, &loc);
            if (moved) {
                func_001bfac8();
                func_001bfac8();
                func_001bfac8();
                func_001bfac8();
            }
            func_001bfac8();
        } while (p->x4 & 0x2000);
    }
    if ((u16)(D_00F56DC0->flags & 4) == 0) {
        func_00f24570(t.h0, D_00F56DC4);
        ret = 1;
        t2 = loc.t;
        t2.h0 = D_00F56DC0->h60;
        func_00f24680(&t2);
        func_00f23e30(t2.h4 - 1);
        func_0011d768(2);
    } else {
        func_00f246e0(1, t.h0, D_00F56DC4);
        ret = 0;
        func_0011d768(3);
    }
    func_00f24780(D_00F56DC4);
    func_00f24240(D_00F56DC4, 0);
    func_00f2bfd8(0, 0, 0, 0);
    func_001bfac8();
    D_00F61370 = 0;
    return ret;
}
