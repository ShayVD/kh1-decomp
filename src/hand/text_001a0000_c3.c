/* func_001a2248 with the VU0 random helper func_001a2178 (moved from vu0.c),
 * which must be defined above it. */
#include "common.h"

f32 func_001a2178(void) {
    f32 ret;

    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vrxor R, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=&r"(ret)
        :
        : "$8", "memory");
    return ret;
}
s8 func_001a21c0(u8 a);

typedef struct { u8 pad0[6]; s16 n; } P9Shape;
typedef struct { u8 pad0[0x14]; struct { P9Shape *s; s32 pad; } *shapes; } P9Res;
extern P9Res *D_00615E64;

typedef struct {
    u8 pad0[4];
    s32 shape;
    u8 pad8[0xc];
    u16 life;
    u8 x16;
    u8 pad17;
    f32 c[4];
    u8 pad28[0x10];
    u8 col[4];
    f32 x3c;
    f32 x40;
    u8 pad44[4];
    f32 x48;
    f32 x4c;
    u8 pad50[0x10];
    f32 x60;
    f32 x64;
    u8 pad68[4];
    f32 x6c;
    f32 x70;
    u8 pad74[4];
    f32 x78;
    u8 pad7c[0xc];
    f32 x88;
    u8 pad8c[4];
    f32 x90;
    u8 pad94[0x23];
    u8 fl2;
    u8 fl1;
} P9Key;

typedef struct {
    u8 pad0[0x22];
    u16 frame;
    u8 pad24[2];
    s16 life;
    s8 col[4];
    f32 x2c;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4c;
    f32 x50;
    s32 x54;
    union { u64 d; u8 b; } x58;
} P9Part;

typedef struct { u8 pad0[0x10]; f32 c[4]; } P9Out;

void func_001a2248(P9Key *a, P9Part *b, P9Out *c) {
    P9Shape *s;
    u8 v;
    f32 r;
    s32 l; u16 v16;

    b->col[0] = func_001a21c0(a->col[0]);
    b->col[1] = func_001a21c0(a->col[1]);
    b->col[2] = func_001a21c0(a->col[2]);
    b->col[3] = func_001a21c0(a->col[3]);
    { s32 o = a->shape * 8; s = *(P9Shape **)((u8 *)D_00615E64->shapes + o); }
    b->frame = s->n * func_001a2178();
    v = a->x16;
    if (v) {
        b->x58.b = v;
        b->x58.d |= 0x200;
    }
    b->x2c = a->x6c;
    b->x30 = a->x70;
    if (a->fl1) {
        b->x34 = func_001a2178() * a->x78;
        if (a->fl1 & 1) {
            if (a->fl1 & 2) {
                if (func_001a2178() > 0.5) b->x34 = -b->x34;
            }
        } else if (a->fl1 & 2) {
            b->x34 = -b->x34;
        }
    }
    if (a->fl1 & 4) b->x2c += b->x34;
    if (a->fl1 & 8) b->x30 += b->x34;
    while (b->x2c >= 180.0f) b->x2c -= 360.0f;
    while (b->x2c < -180.0f) b->x2c += 360.0f;
    b->x38 = a->x3c;
    b->x3c = a->x40;
    b->x40 = a->x48;
    b->x44 = a->x4c;
    if (a->fl2) {
        if (a->fl2 & 0x20) {
            b->x48 = b->x4c = func_001a2178() * a->x60;
            if (a->fl2 & 1) {
                if (a->fl2 & 2) {
                    if (func_001a2178() > 0.5) {
                        b->x48 = -b->x48;
                        b->x4c = -b->x4c;
                    }
                }
            } else if (a->fl2 & 2) {
                b->x48 = -b->x48;
                b->x4c = -b->x4c;
            }
        } else {
            b->x48 = func_001a2178() * a->x60;
            b->x4c = func_001a2178() * a->x64;
            if (a->fl2 & 1) {
                if (a->fl2 & 2) {
                    if (func_001a2178() > 0.5) b->x48 = -b->x48;
                    if (func_001a2178() > 0.5) b->x4c = -b->x4c;
                }
            } else if (a->fl2 & 2) {
                b->x48 = -b->x48;
                b->x4c = -b->x4c;
            }
        }
    }
    if (a->fl2 & 4) {
        b->x38 += b->x48;
        b->x3c += b->x4c;
    }
    if (a->fl2 & 8) {
        b->x40 += b->x48;
        b->x44 += b->x4c;
    }
    b->x50 = a->x88;
    if (a->x90 != 0.0f) {
        b->x50 += (a->x90 + a->x90) * func_001a2178() - a->x90;
    }
    if (a->life) b->life = a->life; else b->life = -1;
    if (c) {
        c->c[0] = a->c[0];
        c->c[1] = a->c[1];
        c->c[2] = a->c[2];
        c->c[3] = a->c[3];
    }
    b->x54 = 0;
}
