/* Object class 0x1A, without strict aliasing (docs/modules.md "Session 52"):
 * the handlers func_00150cd8 registers in the class table D_00350D88
 * (func_0014f830(0x1A, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class1a.c. Read from
 * the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0054.h"
#include "data/types/nostrict_text_00140000_h57.h"
#include "data/types/nostrict_text_00140000_h57_p.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"

/* func_001502e8 (from hand/nostrict/text_00150000_s11_w40.c). */
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
        { s32 m = a->x130->x48; S144e *q = a->x144; q->x4 = m; if ((f32)(s32)q < q->x8) t = 0; } /* FLAGGED dead FP test (s11w40) */
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

/* func_00150678 (from hand/nostrict/text_00140000_h57.c). */
typedef struct { u8 pad0[0x130]; f32 v130[4]; } Sub57_0678;
typedef struct {
    s32 flags;
    u8 pad4[0x30-4];
    f32 v30[4];
    u8 pad40[0x148-0x40];
    Sub57_0678 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x3c0-0x154];
    f32 v3c0[4];
} Obj57_0678;
typedef struct { u8 pad0[0x34]; f32 f34; } Arg57_0678;
f32 func_00120c18(f32 *);
f32 sinf(f32);
f32 cosf(f32);
void func_00137688(Obj57_0678 *, f32);
void func_00137308(Obj57_0678 *, Arg57_0678 *);
s32 func_0014f658(void *, s32);
extern s32 D_0054F738_00150678 __asm__("D_0054F738");
#define D_0054F738 D_0054F738_00150678
void func_00150678(Obj57_0678 *o, Arg57_0678 *p) {
    f32 v[4];
    f32 a;
    f32 d;

    a = p->f34;
    v[1] = 0.0f;
    v[0] = sinf(a);
    v[1] = 0.0f;
    v[2] = cosf(a);
    v[3] = 1.0f;
    if (func_00120c18(o->v3c0) < 1.0f) d = PlatVu0InnerProduct(v, o->v30);
    else d = PlatVu0InnerProduct(v, o->v3c0);
    if (d > 0.0f) {
        o->flags |= 0x800000;
        a = p->f34;
    } else {
        o->flags &= ~0x800000;
        a = func_00120c88(p->f34 + 3.1415928f);
    }
    o->f150 = a;
    func_00137688(o, a);
    PlatVu0ScaleVector(o->o148->v130, o->v3c0, D_002BBDFC * 0.5f);
    func_00137308(o, p);
    func_0014f658(o, 26);
    D_0054F738 = 0;
}
#undef D_0054F738

