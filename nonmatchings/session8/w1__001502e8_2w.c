/* 2w, hand/nostrict (w34 draft, new finding): gcc 2.96 local-alloc sorts 3 qtys with a hard-coded 3-element exchange that compares qty NUMBERS 0/1, 1/2, 0/1 (not the current order), so with qtys C=x130 (0), Q=x144 reload (1), N=lh value (2) born in that order the result is C,N,Q (C v0). The original N v0, Q v1, C a0 needs pri(Q) > pri(C) and pri(N) > pri(Q) with N block-local (not tied: a MEM-operand input is never tied): e.g. Q with 3 refs (1.5) against C 1 and N 2. Block-local n0 gives C v0/N v1/Q a0 (4w). Merging P1 and Q into one block-local q set twice gives q v0/N v1/C a0. */
#include "common.h"

typedef struct { s32 st; s32 x4; f32 x8; f32 xc; } S144e;
typedef struct { u8 pad[4]; f32 x4; } R130e;
typedef struct { u8 pad[0x48]; s16 x48; s16 x4a; } C130e;
typedef struct {
    u32 w0;
    u8 pad4[0x24 - 4];
    f32 x24;
    u8 pad28[4];
    f32 x2c;
    u8 pad30[4];
    f32 x34;
    u8 pad38[0x98 - 0x38];
    u32 *x98;
    u8 pad9c[0x130 - 0x9c];
    C130e *x130;
    u8 pad134[0x144 - 0x134];
    S144e *x144;
    u8 pad148[0x16c - 0x148];
    f32 x16c;
    u8 pad170[0x280 - 0x170];
    f32 x280;
    u8 pad284[0x4a0 - 0x284];
    void *x4a0;
} Ae;

void *func_00121e28(s32, void *);
void func_00150208(void);
R130e *func_00130340(Ae *, s32, f32);
void func_00130578(Ae *, s32, f32);
f32 func_00176850(void);
f32 func_00131a68(Ae *, s32);
s32 func_00137618(void *);
f32 func_00120c88(f32);
void func_001501c0(Ae *);
void func_00249230(void);
void func_00135800(Ae *, f32, f32);
extern f32 D_002BBDFC;
extern f32 D_0054F738;

void func_001502e8(Ae *a) {
    S144e *p;
    R130e *r;
    f32 f;
    f32 z;
    f32 *t;
    s32 n;

    if (!a->x144) {
        a->x144 = func_00121e28(16, &a->x144);
        a->x144->st = 0;
        a->x144->xc = 0;
        a->x4a0 = func_00150208;
        if (a->x130->x4a == 0) {
            r = func_00130340(a, 1, 0.0f);
            f = func_00176850();
            f *= func_00131a68(a, 1);
            r->x4 = f;
        } else {
            r = func_00130340(a, 0, 0.0f);
            r->x4 = a->x130->x4a;
            a->x144->st = 2;
        }
    }
    { f32 g = a->x144->xc;
    z = 0.0f;
    if (z < g) a->x144->xc = g - D_002BBDFC; }
    if (!func_00137618(a)) return;
    switch (a->x144->st) {
    case 0:
        if (!a->x98) return;
        if (*a->x98 & 0x800000) {
            a->x34 = func_00120c88(a->x34 + 3.1415928f);
            *a->x98 &= ~0x800000;
        }
        func_00130340(a, 2, z);
        func_00130578(a, 0, z);
        p = a->x144; p->st = 2;
        n = a->x130->x48; a->x144->x4 = n;
        break;
    case 2:
        f = a->x16c + D_002BBDFC - a->x280;
        if (z <= f) {
            if (a->x98) {
                if (func_00137618(a->x98)) {
                    p = a->x144;
                    n = p->x4;
                    if (n > 0) {
                        p->x4 = --n;
                        if (n == 0) func_001501c0(a);
                    }
                }
            } else if (a->x130->x4a == 0) {
                r = func_00130340(a, 0x1000003, z);
                r->x4 = f;
                func_00130578(a, 0x40000001, z);
                p = a->x144; p->st = 0;
            }
        }
        if (!a->x98) return;
        if (a->x144->x4 >= 3) return;
        t = &D_0054F738;
        *t -= D_002BBDFC;
        if (*t <= 0.0f) {
            func_00249230();
            *t = 30.0f;
        }
        break;
    case 4:
        a->x144->x8 += D_002BBDFC;
        if (!(a->w0 & 8) && 20.0f < a->x144->x8) {
            func_00135800(a, z, 10.0f);
            a->w0 |= 8;
        }
        a->x24 += D_002BBDFC;
        if (10.0f < a->x24) a->x24 = 10.0f;
        a->x2c = 1.0f;
        break;
    }
}
