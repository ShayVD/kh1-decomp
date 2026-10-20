/* func_00180280 and func_00181738, which needs it defined above (moved from
 * text_00170000_h38.c; both match without strict aliasing). */
#include "common.h"
typedef int u128 __attribute__((mode(TI)));
typedef struct { f32 x, y, z, w; } V4;
typedef union { V4 v; u128 q; } V4A;
void func_00182870(void);
void func_00267370(V4A *, V4A *, V4A *);
void func_002673b8(V4A *, V4A *);
void sceVu0MulMatrix(V4A *, V4A *, V4A *);
extern V4A D_00615FC0[4];
extern V4A D_00615EB0[4]; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern V4A D_00615E70[4];
extern V4A D_00616010[3]; /* rows 1..3 of a matrix starting 16 bytes earlier */
extern V4A D_00616040[4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern V4A D_00616080[4]; /* src/data/bss_0061.c: u8 D_00616080[0x40] */
extern V4A D_006160C0[4]; /* src/data/bss_0061.c: f32 D_006160C0[4][4] */

void func_00180280(void *o) {
    V4A b, a, c;
    func_00182870();
    sceVu0MulMatrix(D_00615FC0, D_00615EB0, D_00615E70);
    sceVu0MulMatrix(D_00616080, D_00616040, D_00615FC0);
    a.v.x = D_00615FC0[1].v.x;
    a.v.y = D_00615FC0[1].v.y;
    a.v.z = D_00615FC0[1].v.z;
    a.v.w = 0.0f;
    func_002673b8(&a, &a);
    D_00616010[0].q = a.q;
    b.v.x = a.v.y;
    b.v.y = -a.v.x;
    b.v.z = 0.0f;
    b.v.w = 0.0f;
    func_002673b8(&b, &b);
    D_00616010[-1].q = b.q;
    func_00267370(&c, &b, &a);
    func_002673b8(&c, &c);
    D_00616010[1].q = c.q;
    D_00616010[2].q = D_00615FC0[3].q;
    sceVu0MulMatrix(D_006160C0, D_00616040, &D_00616010[-1]);
}


typedef struct {
    u8 pad[0x14];
    s32 flags;
} PLink;

typedef struct {
    u8 pad[0xf8];
    u8 xf8;
    u8 padf9[3];
    u16 xfc;
    u16 xfe;
} POwner;

typedef struct PObj {
    u8 pad0[0x58];
    s32 x58;
    u8 pad5c[4];
    s32 x60;
    u8 pad64[0x22];
    u16 flags;
    s32 key;
    POwner *own;
    u8 x90;
    u8 pad91[2];
    u8 x93;
    PLink *link;
    s32 x98;
    f32 x9c;
    u8 pada0[8];
    s32 xa8;
    f32 xac;
    u8 padb0;
    u8 xb1;
    u8 padb2;
    u8 xb3;
    u8 xb4;
    u8 xb5;
    u8 padb6[10];
} PObj;

typedef struct {
    s32 key;
    s32 bit;
} PCur;

extern PObj D_00364130[256];
extern PCur D_003701B0;
extern f32 D_002BBDEC;
extern f32 D_002BBDFC;

void func_0011d210(u16, s32, PObj *, u16);
void func_0011d1e0(u16, s32, PObj *, u16);
void func_0011d2d0(u16, s32, s32);
void func_0011d3c8(u16, s32, s32);
u8 func_001812d0(PObj *);
void func_00180a48(PObj *);
void func_00183840(PObj *);
s32 func_00183878(PObj *, s32);
void func_00182788(PObj *);
void func_001827f0(PObj *);

void func_00181738(void) {
    s32 i;

    D_003701B0.bit = -1;
    D_003701B0.key = 0;
    for (i = 0; i < 256; i++) {
        PObj *e = &D_00364130[i];
        f32 lim;
        s32 fl;
        s32 done;
        s32 same;

        if (!(e->flags & 1)) continue;
        if (e->flags & 4) continue;
        lim = 0.0f;
        fl = e->link->flags;
        if (fl & 0x20) lim -= D_002BBDEC + D_002BBDEC;
        if (lim < e->xac) {
            e->link->flags = fl | 0x10;
            if (e->xac <= D_002BBDFC) e->link->flags &= ~0x10;
            continue;
        }
        e->link->flags = fl & ~0x10;
        if (e->flags & 8) {
            POwner *o = e->own;
            if (o->xfc) {
                if (e->xb5 == 1) func_0011d210(o->xfc, e->xa8, e, o->xfe);
                else func_0011d1e0(o->xfc, e->xa8, e, o->xfe);
            }
            e->flags &= ~8;
        } else if (e->xb1) {
            if (!(e->flags & 0x40) && e->own->xfc) {
                func_0011d2d0(e->own->xfc, e->xa8, 1);
                e->flags |= 0x40;
            }
        } else if ((e->flags & 0x40) && e->own->xfc) {
            func_0011d2d0(e->own->xfc, e->xa8, 0);
            e->flags &= ~0x40;
        }
        func_00180280(e);
        if (e->x58 && !e->xb3) e->x90 = func_001812d0(e);
        else e->x90 = 0;
        if (e->x90 && e->own->xf8) continue;
        if (e->flags & 0x20) continue;
        same = 0;
        if (D_003701B0.key == e->key) same = D_003701B0.bit == e->x93;
        if (!same) func_00180a48(e);
        e->x9c += D_002BBDFC;
        if (e->x9c >= 2.0f) {
            done = 0;
            e->xb4 = 0;
            if (e->x60 > 0) {
                for (; e->x60 > 0; e->x60--) {
                    func_00183840(e);
                    if (func_00183878(e, 0)) {
                        if (e->own->xfc) func_0011d3c8(e->own->xfc, e->xa8, 60);
                        func_00182788(e);
                        done = 1;
                        func_001827f0(e);
                        e->flags |= 0x10;
                        break;
                    }
                }
            }
            if (!done) {
                for (e->x9c -= 2.0f; e->x9c >= 2.0f; e->x9c -= 2.0f) {
                    func_00183840(e);
                    if (func_00183878(e, 0)) {
                        if (e->own->xfc) func_0011d3c8(e->own->xfc, e->xa8, 60);
                        func_00182788(e);
                        done = 1;
                        func_001827f0(e);
                        e->flags |= 0x10;
                        break;
                    }
                }
                if (!done) func_00183840(e);
            }
        } else {
            e->xb4 = 1;
            func_00183840(e);
        }
        D_003701B0.key = e->key;
        D_003701B0.bit = e->x93;
    }
}
