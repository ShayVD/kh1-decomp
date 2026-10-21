#include "common.h"
void *func_0014a4a8();
void *func_00147138(void *, s32);
s32 func_00130010(void *);
void func_0014f658(void *, s32);
void func_001315c0(void *, s32, f32 *, f32);
void func_002675a8(f32 *, f32 *);
extern f32 D_002BBDFC;
#include "data/pieces/D_002C58A0.h"
typedef struct { u8 pad[0x20]; f32 x20; u8 pad24[8]; f32 x2c; u8 x30; u8 x31; s8 x32; u8 x33; } W34Prm;
typedef struct { u8 pad[0x14]; s32 x14; W34Prm *x18; u8 pad1c[0x14]; s32 x30; } W34Eff;
typedef struct { u8 pad[0x40]; f32 x40; u8 pad44[0x14c - 0x44]; W34Eff *x14c; } W34EObj;
typedef struct { u8 pad[8]; s32 x8; f32 xc; u8 pad10[0x10]; s32 x20; f32 x24; f32 x28; u8 pad2c[0x60 - 0x2c]; s32 *x60; s32 x64; u8 pad68[0x94 - 0x68]; f32 x94; s32 x98; } W34Prt;
W34Prt *func_0014a908(W34EObj *o) {
    W34Prt *r = func_0014a4a8(o);
    if (o->x14c) {
        if (r->x20 == 48) {
            W34Prm *p = o->x14c->x18;
            r->xc += p->x20 * o->x40;
            r->x24 *= p->x2c;
            r->x28 *= p->x2c;
            r->x64 += p->x33;
            if (r->x64 >= 100) r->x64 = 99;
            else if (r->x64 <= 0) r->x64 = 1;
            r->x94 *= p->x31 * 0.0499999970197677612304688f;
            r->x98 += p->x32;
        }
        r->x8 = o->x14c->x14;
        r->x60 = &o->x14c->x30;
        o->x14c->x30 = 0;
    }
    return r;
}
typedef struct { s32 x0; u8 pad4[0x1c]; f32 x20[4]; } W34Tgt;
typedef struct { s32 x0; W34Tgt *x4; u8 pad8[4]; f32 xc; f32 x10[4]; u8 pad20[0x20]; } W34Lk;
extern W34Lk D_0054F750[8]; /* src/data/bss_0054.c: Slot57_15d0 D_0054F750[8] */
extern f32 D_00306840;
void func_00150de0(s32 a) {
    W34Lk *e = D_0054F750;
    s32 i;
    if (a) {
        for (i = 0; i < 8; i++, e++) {
            if (e->x4 && !e->x0) {
                e->x4->x0 |= 0x30;
                e->x0 = 3;
                e->xc = D_00306840;
                func_002675a8(e->x10, e->x4->x20);
            }
        }
    } else {
        for (i = 0; i < 8; i++, e++) {
            if (e->x4 && e->x0 == 3) {
                e->x0 = 4;
                e->xc = D_00306840;
            }
        }
    }
}
typedef struct { u8 pad[0x24]; f32 x24; } W34Sc;
typedef struct { u32 x0; u8 pad4[0xc]; f32 x10[4]; f32 x20; f32 x24; f32 x28; u8 pad2c[0x144 - 0x2c]; W34Sc *x144; u8 pad148[0x2d0 - 0x148]; s32 x2d0; } W34Bnc;
void func_001473a8(s32, s32, f32 *);
void func_00151010(W34Bnc *o) {
    W34Sc *sc = o->x144;
    if (o->x24 > 0.0f) {
        o->x0 &= ~0x20;
        if (!(o->x2d0 & 1)) {
            if (o->x24 > 5.0f) {
                f32 t = o->x24 / 20.0f;
                if (t > 0.5f) sc->x24 = 1.0f - t * 0.199999988079071044921875f;
                o->x24 *= -0.7999999523162841796875f;
                func_001473a8(50, 0, o->x10);
            } else {
                func_002675a8(&o->x20, (*(f32 (*)[0x4])&D_002C58A0));
            }
        }
    }
    o->x24 += 3.0f;
    if (o->x24 > 20.0f) o->x24 = 20.0f;
    o->x20 *= 0.949999988079071044921875f;
    o->x28 *= 0.949999988079071044921875f;
}
typedef struct { u8 pad[4]; s32 x4; u16 x8; } W34Fx;
typedef struct { u8 pad[0x10]; W34Fx *x10; } W34Sx;
typedef struct { u8 pad[0x14]; f32 x14; u8 pad18[0x108]; f32 x120[4]; } W34Gnd;
typedef struct { u8 pad[0x14]; f32 x14; u8 pad18[0x58]; s32 x70; u8 pad74[0x24]; W34Gnd *x98; u8 pad9c[0x144 - 0x9c]; W34Sx *x144; } W34Pl7;
void func_00147278(s32, s32, s32);
void func_00267518(f32 *, f32 *, f32 *);
void func_00151b98(W34Pl7 *o, f32 *v) {
    W34Sx *s = o->x144;
    if (o->x70 == 0) {
        if (v[0] == 0.0f || v[2] == 0.0f) {
            if (o->x98 && fabsf(o->x14 + v[1] - o->x98->x14) >= 10.0f) goto zero;
        } else {
        zero:
            func_002675a8(v, (*(f32 (*)[0x4])&D_002C58A0));
        }
    }
    if (v[0] != 0.0f || v[2] != 0.0f) {
        if (o->x98) {
            if (!s->x10) s->x10 = func_00147138(o, 0);
            func_00267518(o->x98->x120, o->x98->x120, v);
        }
    } else if (s->x10) {
        func_00147278(s->x10->x8, s->x10->x4, 60);
        s->x10 = 0;
    }
}
typedef struct { u8 pad[8]; s32 x8; u8 padc[4]; f32 x10[4]; } W34Hit;
typedef struct { s32 x0; } W34Cnt;
typedef struct { u8 pad[0x144]; W34Cnt *x144; } W34Pl8;
W34Hit *func_00134928(W34Pl8 *);
void func_001350d0(W34Hit *);
void func_00145008(W34Pl8 *, s32);
typedef struct { u8 pad[0x68]; s32 x68; } W34P68;
void func_00147ed8(s32, s32, s32, f32 *);
void func_001247e8(void *);
void func_00151cd0(W34Pl8 *o) {
    f32 v[4] __attribute__((aligned(16)));
    func_001315c0(o, 0x8003, v, 0.0f);
    func_00147ed8(((W34P68 *)o)->x68, 0, 20000, v);
    func_001247e8(o);
}
void func_002673b8(f32 *, f32 *);
void func_00156260(W34Pl8 *, f32 *);
void func_00151d20(W34Pl8 *o) {
    W34Cnt *c = o->x144;
    W34Hit *e;
    while ((e = func_00134928(o))) {
        s32 n = e->x8;
        func_00147138(o, 4);
        if (n > 0) {
            c->x0 += n;
            if (c->x0 >= 7) {
                func_00145008(o, 0);
                func_00151cd0(o);
            } else {
                f32 d[4] __attribute__((aligned(16)));
                func_002675a8(d, e->x10);
                if (fabsf(d[0]) > fabsf(d[2])) d[2] = 0.0f;
                else d[0] = 0.0f;
                func_002673b8(d, d);
                d[3] = 15.0f;
                func_00156260(o, d);
            }
        }
        func_001350d0(e);
    }
}
typedef struct { s32 x0; s32 x4; f32 x8; s32 xc; s32 x10; } W34St20;
typedef struct { u32 x0; u8 pad4[0x6c]; s32 x70; u8 pad74[0x144 - 0x74]; W34St20 *x144; u8 pad148[0x4a0 - 0x148]; void (*x4a0)(); } W34Pl9;
W34St20 *func_00121e28(s32, W34St20 **);
void func_001520e0();
s32 func_00151fa0(W34Pl9 *);
void func_001520c0(W34Pl9 *);
s32 func_00152140(W34Pl9 *o) {
    W34St20 *s = o->x144;
    if (!s) {
        s = func_00121e28(20, &o->x144);
        s->x0 = 0; s->x4 = 0; s->x8 = 0.0f; s->xc = 0; s->x10 = 0;
        o->x4a0 = func_001520e0;
    }
    if (o->x0 & 0x400) {
        switch (o->x70) {
        case 0:
            if (s->x8 >= 60.0f) func_00151cd0((W34Pl8 *)o);
            else func_00147138((W34Pl8 *)o, 2);
            s->x4 = 0;
            break;
        case 2:
            s->x8 = 0.0f;
            break;
        }
    }
    func_00151d20((W34Pl8 *)o);
    switch (o->x70) {
    case 0:
        return func_00151fa0(o);
    case 2:
        func_001520c0(o);
        break;
    }
}
typedef struct { u8 pad[0x30]; f32 x30[4]; u8 pad40[0x58]; s32 x98; u8 pad9c[0x150 - 0x9c]; f32 x150; } W34Pl10;
f32 func_00267390(f32 *, f32 *);
s32 func_00122ff8(s32);
f32 atan2f(f32, f32);
s32 func_00130340(W34Pl10 *, s32, f32);
void func_00130578(W34Pl10 *, s32, f32);
void func_00152250(W34Pl10 *o, s32 b, f32 *v) {
    if (v[3] > 0.0f && func_00267390(o->x30, v) > 0.766f && func_00122ff8(o->x98)) {
        if (fabsf(v[0]) > fabsf(v[2])) v[2] = 0.0f;
        else v[0] = 0.0f;
        func_002673b8(v, v);
        v[3] = 3.0f;
        o->x150 = atan2f(v[0], v[2]);
    } else {
        func_00130340(o, 0x10000be, 6.0f);
        func_00130578(o, 0x40000000, 0.0f);
        func_0014f658(o, 0);
        func_002675a8(v, o->x30);
        v[3] = 0.0f;
    }
}
typedef struct { u64 x0; s32 x8; f32 xc; f32 x10[4]; } W34Eff2;
typedef struct { u8 pad[0x40]; W34Eff2 *x40; } W34S144;
typedef struct { u8 pad[0x68]; s32 x68; u8 pad6c[0x144 - 0x6c]; W34S144 *x144; } W34Pl11;
void func_00152648(W34Pl11 *);
s32 func_0014a408(void);
s32 func_001477e0(s32);
void func_00135640(W34Eff2 *, W34Pl11 *);
W34Eff2 *func_00152688(W34Pl11 *o, s32 a, s32 b) {
    W34Eff2 *e;
    s32 id;
    func_00152648(o);
    id = func_0014a408();
    e = func_0014a4a8(a, id, func_001477e0(b));
    o->x144->x40 = e;
    e->x0 = (e->x0 & ~0x3000LL) | 0x100;
    e->x8 = o->x68;
    func_00135640(e, o);
    return e;
}
typedef struct { s32 x0; f32 x4; f32 x8; f32 xc; f32 v[4]; } W34Qry;
void *func_001230a0(void *);
s32 func_0015bd78(W34Qry *, void *, s32);
void func_001354b8(W34Eff2 *, void *);
void func_00152730(W34Pl11 *);
void func_00152770(W34Pl11 *o) {
    f32 p[4] __attribute__((aligned(16)));
    W34Qry q __attribute__((aligned(16)));
    W34Eff2 *e;
    void *a;
    func_001315c0(o, 0x8003, p, 0.0f);
    func_00147ed8(o->x68, 4, -10000, p);
    e = func_0014a4a8(o, 0x80000000, func_001477e0(19));
    e->x0 = (e->x0 & ~0x3000LL) | 0x40;
    e->x8 = o->x68;
    func_002675a8(e->x10, p);
    q.x0 = 1;
    q.x4 = q.x8 = e->xc;
    func_002675a8(q.v, p);
    for (a = 0; (a = func_001230a0(a)); ) {
        if (a != o && func_0015bd78(&q, a, 0)) func_001354b8(e, a);
    }
    func_00152730(o);
}
#include "data/types/nostrict_text_00140000_h34.h"
extern W34Tbl D_0035193C[];
typedef struct { u64 x0; u8 pad8[0x14]; f32 x1c; s32 x20; u8 pad24[0xc]; f32 x30[4]; } W34S144b;
typedef struct { u8 pad[0x30]; f32 x30[4]; u8 pad40[0x120]; s32 x160; } W34Tg2;
typedef struct { u8 pad[0x10]; f32 x10[4]; u8 pad20[0x78]; W34Tg2 *x98; u8 pad9c[0x84]; f32 x120[4]; u8 pad130[0x14]; W34S144b *x144; } W34Pl13;
void func_00267530(f32 *, f32 *, f32 *);
void func_00152c28(W34Pl13 *, f32 *, f32);
void func_00152d50(W34Pl13 *, s32, f32 *);
void func_001586a8(s32);
void func_00152e10(W34Pl13 *o) {
    W34S144b *s;
    f32 v[4] __attribute__((aligned(16)));
    if (o->x98->x160 & 1) return;
    if (func_00130010(o->x98)) return;
    o->x144->x1c -= D_002BBDFC;
    if (o->x144->x1c > 0.0f) {
        func_001315c0(o->x98, 0x30, v, 0.0f);
        func_00267530(o->x120, v, o->x10);
        return;
    }
    func_0014f658(o->x98, 0);
    s = o->x144;
    {
        s32 i = s->x20;
        f32 f = D_0035193C[i].x0;
        if ((s32)(s->x0 >> 1) & 1) func_00152c28(o, s->x30, f);
        else func_00152d50(o, i, o->x98->x30);
    }
    func_001586a8(18);
}
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0xc]; f32 x14; u8 pad18[4]; f32 x1c; u8 pad20[0x10]; f32 x30[4]; } W34S144c;
typedef struct { u8 pad[0x3c]; f32 x3c; u8 pad40[0x120]; s32 x160; } W34Tg3;
typedef struct { u32 x0; u8 pad4[0xc]; f32 x10[4]; u8 pad20[0x1c]; f32 x3c; u8 pad40[0x58]; W34Tg3 *x98; u8 pad9c[0xa8]; W34S144c *x144; } W34Pl14;
f32 func_00120c88(f32);
void func_00152f10(W34Pl14 *o) {
    f32 v[4] __attribute__((aligned(16)));
    o->x0 |= 0x20;
    if (o->x98->x160 & 1) return;
    if (func_00130010(o->x98)) return;
    o->x144->x1c -= D_002BBDFC;
    if (o->x144->x1c <= 0.0f) {
        o->x144->x4 = 2;
        o->x144->x14 = func_00120c88(o->x3c - o->x98->x3c);
        func_001315c0(o->x98, 0x30, v, 0.0f);
        func_00267530(o->x144->x30, o->x10, v);
        o->x144->x1c = 12.0f;
    }
}
#include "data/data_0030.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_0035193C.h"
