/* Hand-matched functions near 0x153000-0x15a000 (worker 35). Built without
 * strict aliasing. */
#include "common.h"
#include "data/bss_0055.h"

/* ---- func_00153418 ---- */
typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8_153418;
typedef struct { u8 pad[8]; F8_153418 f8; } Msg153418;
typedef struct { u8 pad[4]; s32 w4; s32 w8; s32 wC; } S144_153418;
typedef struct { u8 pad[0x144]; S144_153418 *p144; } Obj153418;
void func_00147138(Obj153418 *, s32);
s32 func_00153300(Obj153418 *, Msg153418 *);
void func_00153360(Obj153418 *, Msg153418 *);
void func_001533d0(Obj153418 *, Msg153418 *);
void func_00145008(Obj153418 *, s32);

void func_00153418(Obj153418 *a, Msg153418 *m) {
    s32 n;
    if (m->f8.b.kind == 1) func_00147138(a, 4);
    if (func_00153300(a, m)) {
        func_00153360(a, m);
    } else {
        n = m->f8.w;
        if (n > 0) {
            a->p144->w8 += n;
            if (a->p144->w8 >= a->p144->wC) {
                func_00145008(a, 0);
                a->p144->w4 = 6;
            } else {
                func_001533d0(a, m);
            }
        }
    }
}

/* ---- func_001538d8 ---- */
typedef struct { u8 pad[0x44]; f32 f44; f32 f48; } S144_1538d8;
typedef struct { u8 pad[0xA4]; f32 fA4; f32 fA8; u8 padac[0x98]; S144_1538d8 *p144; } Obj1538d8;
extern f32 D_002BBDFC;
f32 cosf(f32);
f32 func_00120c88(f32);
void func_00152770(Obj1538d8 *);

s32 func_001538d8(Obj1538d8 *a) {
    f32 s, c;
    a->p144->f44 -= D_002BBDFC;
    if (a->p144->f44 <= 0.0f) {
        func_00152770(a);
        return 1;
    }
    s = a->p144->f44 / 300.0f;
    s = s * -0.18849556148052216f + 0.20943952f;
    a->p144->f48 = func_00120c88(a->p144->f48 + s * D_002BBDFC);
    c = (cosf(a->p144->f48) + 1.0f) * 0.5f;
    a->fA8 = c;
    a->fA4 = c;
    return 0;
}

/* ---- func_00153c50 ---- */
typedef struct { u64 d0; u8 pad[0x28]; u8 x30[0x10]; s32 w40; } S144_153c50;
typedef struct { u8 pad[0x74]; s32 w74; u8 pad78[0xCC]; S144_153c50 *p144; } S98_153c50;
typedef struct { u8 pad[0x98]; S98_153c50 *p98; } Obj153c50;
s32 func_00130340(void *, s32, f32);
s32 func_00130578(void *, s32, f32);
void func_00152dc8(S98_153c50 *, s32);
void func_001315c0(s32, s32, void *, f32);

void func_00153c50(Obj153c50 *a, s32 b) {
    func_00130340(a, 0x010000BA, 8.0f);
    func_00130578(a, 0x40000000, 0.0f);
    a->p98->w74 = b;
    func_00152dc8(a->p98, 0);
    if (b) {
        a->p98->p144->d0 |= 2;
        func_001315c0(b, 0x8003, a->p98->p144->x30, 0.0f);
    }
    a->p98->p144->w40 = 0;
}

/* ---- func_001541a8 ---- */
typedef struct { u8 pad[0x20]; f32 f20; f32 f24; } S308CDC;
extern S308CDC *D_00308CDC;
typedef struct { u8 pad[0xC4]; f32 fC4; } S6C_1541a8;
typedef struct { u8 pad[0x6C]; S6C_1541a8 *p6C; } Obj1541a8;
typedef struct { u8 pad[0xC]; f32 fC; } Out1541a8;
f32 func_001348e0(void *, void *);
void func_002675a8(void *, void *);

void func_001541a8(Obj1541a8 *a, u8 *b, Out1541a8 *o) {
    f32 s;
    f32 v;
    func_002675a8(o, b + 16);
    s = a->p6C->fC4;
    if (func_001348e0(a, b) * D_00308CDC->f20 < D_00308CDC->f24) {
        v = func_001348e0(a, b) * D_00308CDC->f20 * s;
    } else {
        v = D_00308CDC->f24 * s;
    }
    o->fC = v;
}

/* ---- func_001542f8 ---- */
typedef struct { u8 pad[0x10]; u8 x10[0x10]; s32 w20; } Arg1542f8;
typedef struct { u8 pad[0x30]; u8 x30[0x390]; u8 x3C0[4]; } Obj1542f8;
typedef struct { s32 w[4]; } Out1542f8;
extern u8 D_002C58B0[];
f32 func_00267390(void *, void *);
void func_001373f8(void *, f32);
void func_00156260(void *, void *);

void func_001542f8(Obj1542f8 *a, Arg1542f8 *b) {
    Out1542f8 o;
    f32 d = func_00267390(a->x30, b->x10);
    s32 n;
    switch (b->w20) {
    case 1:
        if (d < 0.0f) n = 0x01000049; else n = 0x0100004B;
        func_00130340(a, n, 0.0f);
        break;
    case 0:
    default:
        func_00130340(a, d < 0.0f ? 0x01000048 : 0x0100004A, 0.0f);
        break;
    }
    func_001373f8(a, 30.0f);
    func_00130578(a, 0x40000000, 8.0f);
    func_002675a8(a->x3C0, D_002C58B0);
    func_001541a8((Obj1541a8 *)a, (u8 *)b, (Out1541a8 *)&o);
    func_00156260(a, &o);
}

/* ---- func_001543f8 / func_001544a0 ---- */
typedef struct { u8 pad[0x10]; u8 x10[0x10]; } Arg1543f8;
typedef struct { u8 pad[0x30]; u8 x30[0x390]; u8 x3C0[4]; } Obj1543f8;
void func_0014cce0(void *, f32);
void func_00154258(Obj1543f8 *, Arg1543f8 *, void *);

void func_001543f8(Obj1543f8 *a, Arg1543f8 *b) {
    func_00130340(a, func_00267390(a->x30, b->x10) < 0.0f ? 0x0100004E : 0x0100004F, 0.0f);
    func_00130578(a, 0x40000006, 8.0f);
    func_001373f8(a, 30.0f);
    func_0014cce0(a, 20.0f);
    func_00154258(a, b, a->x3C0);
}

void func_001544a0(Obj1543f8 *a, Arg1543f8 *b) {
    Out1542f8 o;
    func_00130340(a, func_00267390(a->x30, b->x10) < 0.0f ? 0x0100004E : 0x0100004F, 0.0f);
    func_00130578(a, 0x40000075, 16.0f);
    func_001373f8(a, 30.0f);
    func_001541a8((Obj1541a8 *)a, (u8 *)b, (Out1541a8 *)&o);
    func_00156260(a, &o);
}

/* ---- func_001545f0 / func_001546b8 ---- */
typedef struct { u8 pad[0x160]; u8 x160[4]; } S148_1545f0;
typedef struct { u8 pad[0x30]; u8 x30[0x118]; S148_1545f0 *p148; u8 pad14c[0x274]; u8 x3C0[4]; } Obj1545f0;
void func_0014f658(void *, s32);
void func_00267560(void *, void *, f32);

void func_001545f0(Obj1545f0 *a, Arg1543f8 *b) {
    func_00130340(a, func_00267390(a->x30, b->x10) < 0.0f ? 0x0100004E : 0x0100004F, 0.0f);
    func_00130578(a, 0x40000006, 8.0f);
    func_001373f8(a, 30.0f);
    func_0014cce0(a, 20.0f);
    func_0014f658(a, 31);
    func_00154258((Obj1543f8 *)a, b, a->x3C0);
    func_002675a8(a->p148->x160, D_002C58B0);
}

void func_001546b8(Obj1545f0 *a, Arg1543f8 *b) {
    if (func_00267390(a->x30, b->x10) < 0.0f) {
        func_00130340(a, 0x0100004C, 0.0f);
    } else {
        func_00130340(a, 0x0100004D, 0.0f);
    }
    func_00130578(a, 0x40000000, 8.0f);
    func_001373f8(a, 30.0f);
    func_002675a8(a->x3C0, D_002C58B0);
    func_00267560(a->p148->x160, a->p148->x160, 0.1f);
}

/* ---- func_00154768 / func_00154880 ---- */
typedef struct { f32 x, y, z, w; } Vec154768;
typedef struct { u8 pad[0x10]; Vec154768 v; } Arg154768;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x110]; f32 f150; u8 pad154[0x26C]; u8 x3C0[4]; } Obj154768;
f32 atan2f(f32, f32);
void func_00137688(void *, f32);
void func_00138a20(void *, void *, f32);
typedef struct { u8 pad[0x3C]; f32 f3C; } S308CDC_b;

void func_00154768(Obj154768 *a, Arg154768 *b, Vec154768 *o) {
    f32 r;
    if (func_00267390(&a->v30, &b->v) < 0.0f) {
        func_00130340(a, 0x0100004C, 0.0f);
        r = atan2f(-b->v.x, -b->v.z);
    } else {
        func_00130340(a, 0x0100004D, 0.0f);
        r = atan2f(b->v.x, b->v.z);
    }
    func_00130578(a, 0x40000000, 8.0f);
    func_001373f8(a, 30.0f);
    func_00137688(a, r);
    a->f150 = r;
    func_002675a8(o, &a->v30);
    o->w = 0.0f;
    func_002675a8(a->x3C0, D_002C58B0);
}

void func_00154880(Obj154768 *a, Arg154768 *b, Vec154768 *o) {
    Vec154768 t;
    f32 r;
    s32 n;
    if (func_00267390(&a->v30, &b->v) < 0.0f) {
        n = 0x50;
        r = atan2f(-b->v.x, -b->v.z);
    } else {
        n = 0x51;
        r = atan2f(b->v.x, b->v.z);
    }
    func_00130340(a, n | 0x01000000, 0.0f);
    func_00130578(a, 0x40000006, 8.0f);
    func_001373f8(a, 30.0f);
    a->f150 = r;
    func_00137688(a, r);
    func_002675a8(o, &a->v30);
    o->w = 0.0f;
    func_002675a8(&t, &b->v);
    t.w = ((S308CDC_b *)D_00308CDC)->f3C;
    func_00138a20(a, &t, 20.0f);
}

/* ---- func_001549b8 / func_00154af8 ---- */
typedef struct { u8 pad[0x1C]; f32 f1C; f32 f20; f32 f24; } S308CDC_c;
typedef struct { u8 pad[0x6C]; S6C_1541a8 *p6C; } Obj6C_1549b8;
typedef struct { u8 pad[0x29]; u8 b29; } S14C_154af8;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x10C]; S14C_154af8 *p14C; } Obj154af8;
typedef struct { u8 pad[8]; s32 w8; } Arg154af8;
extern f32 D_002C58A0[];
void func_00267530(void *, void *, void *);

void func_001549b8(Obj154768 *a, Arg154768 *b, Vec154768 *o) {
    Vec154768 t;
    f32 r;
    s32 n;
    if (func_00267390(&a->v30, &b->v) < 0.0f) {
        n = 0x50;
        r = atan2f(-b->v.x, -b->v.z);
    } else {
        n = 0x51;
        r = atan2f(b->v.x, b->v.z);
    }
    func_00130340(a, n | 0x01000000, 0.0f);
    func_00130578(a, 0x40000075, 16.0f);
    func_001373f8(a, 30.0f);
    a->f150 = r;
    func_00137688(a, r);
    func_002675a8(o, &a->v30);
    o->w = 0.0f;
    func_002675a8(&t, &b->v);
    t.w = ((S308CDC_c *)D_00308CDC)->f24 * ((Obj6C_1549b8 *)a)->p6C->fC4;
    func_00156260(a, &t);
}

void func_00154af8(Obj154af8 *a, Arg154af8 *b, Vec154768 *o) {
    Vec154768 t;
    func_00130340(a, 0x0100006E, 0.0f);
    func_00130578(a, 0x40000000, 0.0f);
    func_001373f8(a, 8.0f);
    a->p14C->b29--;
    if (b->w8 < 0) {
        func_00267530(&t, D_002C58A0, &a->v30);
        t.w = (f32)-b->w8 * ((S308CDC_c *)D_00308CDC)->f1C * ((Obj6C_1549b8 *)a)->p6C->fC4;
        func_00156260(a, &t);
    }
    o->w = 0.0f;
}

/* ---- func_00154c60 / func_00154d60 ---- */
typedef struct { u8 pad[0x1C]; f32 f1C; u8 pad20[0x10]; f32 f30; f32 f34; } S308CDC_d;
typedef struct { u8 pad[0x30]; Vec154768 v30; u8 pad40[0x2C]; S6C_1541a8 *p6C; u8 pad70[0x350]; u8 x3C0[4]; } Obj154c60;

void func_00154c60(Obj154c60 *a, Arg154af8 *b) {
    f32 f, m, s;
    func_00130340(a, 0x01000070, 0.0f);
    func_00130578(a, 0x40000006, 0.0f);
    func_001373f8(a, 8.0f);
    func_0014cce0(a, 20.0f);
    if (b->w8 < 0) {
        f = (f32)b->w8 / 100.0f * ((S308CDC_d *)D_00308CDC)->f30;
        m = -((S308CDC_d *)D_00308CDC)->f34;
        s = a->p6C->fC4;
        if (m < f) {
            m = f * s;
        } else {
            m = m * s;
        }
        func_00267560(a->x3C0, &a->v30, m);
    } else {
        func_002675a8(a->x3C0, D_002C58A0);
    }
}

void func_00154d60(Obj154c60 *a, Arg154af8 *b) {
    Vec154768 t;
    func_00130340(a, 0x01000070, 0.0f);
    func_00130578(a, 0x40000075, 16.0f);
    func_001373f8(a, 8.0f);
    func_00267530(&t, D_002C58A0, &a->v30);
    if (b->w8 < 0) {
        t.w = (f32)-b->w8 * ((S308CDC_d *)D_00308CDC)->f1C * a->p6C->fC4;
    } else {
        t.w = 0.0f;
    }
    func_00156260(a, &t);
}

/* ---- func_001557d0 / func_00155878 ---- */
typedef struct { u8 pad[0x130]; void *p130; } Pl1557d0;
extern Pl1557d0 *D_002E26A0[];
extern u32 D_002C5958;
typedef struct { u32 lo:18; u32 b18:1; u32 hi:13; } F2C5958_1557d0;
typedef union { s32 w; struct { s8 id; u8 n; } b; } E550400W;
typedef struct { E550400W h; char name[0x40]; s32 w44; } E550400;
extern E550400 D_00550400[];
void func_00146928(s32);
void func_00155760(void *);

void func_001557d0(void) {
    s32 i;
    D_002C5958 &= ~0x40000;
    func_00146928(-6);
    for (i = 0; i < 64; i++) {
        D_00550400[i].h.w &= ~0x10000;
    }
    for (i = 0; i < 3; i++) {
        if (D_002E26A0[i]) func_00155760(D_002E26A0[i]->p130);
    }
}

/* ---- func_00155d70 ---- */
typedef struct { u8 pad[0x1C]; s32 w1C; s32 w20; u8 rest[0x40000 - 0x24]; } EFE0000;
extern EFE0000 D_00FE0000[];
s32 strcmp(const char *, const char *);

s32 func_00155d70(s32 i, const char *name) {
    E550400 *e = &D_00550400[i];
    s32 j, n;
    if (e->h.b.id != i || strcmp(e->name, name) != 0) return 0;
    n = (e->w44 - (s32)&D_00FE0000[i] + 0x3FFFF) / 0x40000;
    for (j = 0; j < n; j++) {
        if (e[j].h.b.id != i) return 0;
    }
    return 1;
}

/* ---- func_001562d0 ---- */
typedef struct {
    u8 pad[0x2A0];
    u8 x2A0[0x10];
    u8 x2B0[4];
    s32 w2B4;
    u8 pad2b8[4];
    f32 f2BC;
    f32 f2C0;
    u8 pad2c4[4];
    s32 w2C8;
    u8 pad2cc[4];
    s32 w2D0;
    u8 pad2d4[0xC];
    u8 x2E0[0x10];
} Obj1562d0;
f32 func_001427d0(void *, void *);
void func_001166e8(void *);

s32 func_001562d0(Obj1562d0 *a, Vec154768 *b) {
    f32 lim = func_001427d0(a, a->x2A0);
    f32 r = b->w + a->f2C0;
    while (r > 0.0f) {
        func_00267560(a->x2B0, b, r < lim ? r : lim);
        a->w2B4 = 0;
        a->f2BC = 1.0f;
        a->w2C8 &= ~1;
        func_001166e8(a->x2A0);
        if (a->w2D0 & 1) return 1;
        r -= lim;
        func_002675a8(a->x2A0, a->x2E0);
    }
    return 0;
}

s32 func_001563e0(Obj1562d0 *a, Vec154768 *b) {
    f32 lim = func_001427d0(a, a->x2A0);
    f32 r = b->w + a->f2C0;
    while (r > 0.0f) {
        func_00267560(a->x2B0, b, r < lim ? r : lim);
        a->w2B4 = 0;
        a->f2BC = 1.0f;
        a->w2C8 |= 1;
        func_001166e8(a->x2A0);
        if (!(a->w2D0 & 1)) return 1;
        r -= lim;
        func_002675a8(a->x2A0, a->x2E0);
    }
    return 0;
}

/* ---- func_00156c68 ---- */
typedef struct { u32 b0:1; u32 b1:1; u32 b23:2; u32 b4:1; u32 hi:27; } F144_156c68;
typedef struct { u8 pad[0x144]; F144_156c68 *p144; } Obj156c68;
typedef struct { u8 pad[0x3C]; s32 w3C; s32 w40; s32 w44; s32 w48; u8 pad4c[0x72]; u16 hBE; } S6C_156c68;
typedef struct { u8 pad[0x6C]; S6C_156c68 *p6C; } Pl156c68;
void func_00141468(Pl156c68 *, s32);
s32 func_00141540(Pl156c68 *, s32);
void func_00141608(Pl156c68 *, s32);

void func_00156c68(Obj156c68 *a) {
    s32 i;
    Pl156c68 *p;
    if (!a->p144->b4) {
        a->p144->b0 = 1;
        a->p144->b4 = 1;
    }
    for (i = 0; i < 3; i++) {
        p = (Pl156c68 *)D_002E26A0[i];
        if (p) {
            if (p->p6C->w3C < p->p6C->w40) {
                func_00141468(p, 2);
                a->p144->b0 = 1;
            }
            if (p->p6C->w44 < p->p6C->w48 && !a->p144->b23) {
                a->p144->b0 = 1;
                func_00141540(p, 1);
                func_00141608(p, -p->p6C->hBE);
            }
        }
    }
}

/* ---- func_00156d88 ---- */
typedef struct { u8 pad[4]; s32 w4; s32 w8; } S144_156d88;
typedef struct { u8 pad[0x4A]; s16 h4A; } S130_156d88;
typedef struct { u8 pad[0x130]; S130_156d88 *p130; u8 pad134[0x10]; S144_156d88 *p144; } Obj156d88;
typedef struct { u8 pad[0x70]; s32 w70; } Arg156d88;
void func_0012cc38(s32, s32);
void func_0012ccb0(s32, s32);
void func_00176310(s32);
s32 func_001ebfc8(void);
void func_00124920(void);
void func_0011c768(s32);

s32 func_00156d88(Obj156d88 *a, Arg156d88 *b, s32 c) {
    s32 n;
    switch (c) {
    case -1:
        func_0012cc38(3, 54);
        if (b->w70 != 0 && b->w70 != 24) {
            func_0012ccb0(3, b->w70);
        } else {
            func_00156c68((Obj156c68 *)a);
        }
        break;
    case -2:
        func_00176310(a->p144->w4);
        if (a->p144->w8) func_00176310(a->p144->w8);
        break;
    case 54:
        n = a->p130->h4A ? (func_001ebfc8() ? 3 : 2) : 1;
        func_00124920();
        func_0011c768(n);
        break;
    }
    return 0;
}

/* ---- func_001576a8 ---- */
typedef struct { u8 pad[0x74]; s32 w74; } S6C_1576a8;
typedef struct { u8 pad[0x6C]; S6C_1576a8 *p6C; } Act1576a8;
typedef struct { s8 b0, b1, b2, b3; Act1576a8 *w4; s32 w8; s32 wC; s32 w10; } E551670;
s32 func_00122ff8(Act1576a8 *);
void func_0011dcf0(void *, s32 *, s32 *);
void func_001ed7d8(s32, s32, s32, s32);
void func_001ed6f0(s32, s32, s32);

void func_001576a8(E551670 *e) {
    f32 v[4];
    s32 x, y;
    f32 b, d;
    if (func_00122ff8(e->w4)) {
        func_001315c0((s32)e->w4, e->w4->p6C->w74, v, 0.0f);
        func_0011dcf0(v, &x, &y);
        b = (f32)e->w10;
        d = 16383.0f - b;
        x = b + d * ((f32)x / 16383.0f);
        y = b + d * ((f32)y / 16383.0f);
        if (e->b1 == 0) {
            func_001ed7d8(e->b2, e->b3, x, y);
        } else {
            func_001ed6f0(e->wC, x, y);
        }
    }
}

/* ---- func_00157818 ---- */
typedef struct { u8 pad[0x4C]; u16 h4C; } S130_157818;
typedef struct { u8 pad[0x6C]; s32 w6C; u8 pad70[0x4D]; s8 idx; } S6C_157818;
typedef struct { u8 pad[0x6C]; S6C_157818 *p6C; u8 pad70[0xC0]; S130_157818 *p130; u8 pad134[0x374]; s32 *tbl; } Obj157818;
extern E551670 D_00551670[];
extern s8 D_005516C0[];
void func_00157648(void);

E551670 *func_00157818(Obj157818 *a, s32 k) {
    E551670 *e;
    u32 h;
    s8 v;
    func_00157648();
    if ((D_002C5958 >> 20) & 1) return 0;
    e = &D_00551670[a->p6C->idx];
    h = a->p130->h4C;
    if (h < 10) {
        v = D_005516C0[h];
        if (v < 0) return 0;
        e->b2 = v;
        e->b1 = 0;
    } else {
        if (a->tbl == 0 || k >= *a->tbl) return 0;
        e->b1 = 1;
        e->wC = (s32)a->tbl + a->tbl[k + 1];
    }
    e->b3 = k;
    e->w4 = (Act1576a8 *)a;
    e->b0 = 2;
    e->w10 = a->p6C->w6C;
    return e;
}

/* ---- func_00157dc8 ---- */
typedef struct { s8 b0; u8 f0:1; u8 f1:7; u8 pad[32]; } E551608;
extern E551608 D_00551608[];
s32 func_0011ef38(void *);
void func_0011ef10(s32, void *);
void func_00157c60(void);

void func_00157dc8(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        D_00551608[i].b0 = -1;
        D_00551608[i].f0 = 0;
    }
    for (i = 0; i < 10; i++) {
        D_005516C0[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        D_00551670[i].b0 = 0;
    }
    if (func_0011ef38(func_00157c60) == 0) {
        func_0011ef10(0x23669, func_00157c60);
    }
}

/* ---- func_00157ea8 ---- */
typedef struct {
    s32 w0;
    u8 pad4[0xC];
    Vec154768 v10;
    u8 pad20[0x1C];
    f32 f3C;
    u8 pad40[0x124];
    s32 w164;
    u8 pad168[4];
    f32 f16C;
    u8 pad170[0x1E0];
    s32 w350[4];
    u8 pad360[0x10];
    u64 d370;
} Obj157ea8;
typedef struct { u8 pad[4]; f32 f4; } Ret157ea8;

void func_00157ea8(Obj157ea8 *a) {
    Obj157ea8 *p;
    s32 i;
    a->w0 |= 0x02000270;
    a->d370 &= ~(3ULL << 37);
    p = (Obj157ea8 *)D_002E26A0[0];
    if (func_00122ff8((Act1576a8 *)p)) {
        func_002675a8(&a->v10, &p->v10);
        func_00137688(a, p->f3C);
        for (i = 0; i < 4; i++) {
            a->w350[i] = p->w350[i];
        }
        ((Ret157ea8 *)func_00130340(a, p->w164, 0.0f))->f4 = p->f16C;
    }
}

/* ---- func_00157f70 ---- */
typedef struct { u8 pad[0x30]; f32 f30; f32 f34; } S5516E0;
S5516E0 *D_005516E0 ALIGNED(16);
typedef struct { f32 f0, f4, f8, fC; s32 w10, w14, w18; } S2BC0F0;
extern S2BC0F0 D_002BC0F0;
typedef struct { s32 w0, w4, w8; } S3519E0;
extern S3519E0 D_003519E0;
extern u8 D_00351A00[], D_00351A10[];
typedef struct { u8 pad[0xCC]; f32 fCC; } S6C_157f70;
typedef struct { u8 pad[0x6C]; S6C_157f70 *p6C; u8 pad70[0x350]; u8 x3C0[4]; } Obj157f70;
S5516E0 *func_00159ea8(void *, void *, void *);

void func_00157f70(Obj157f70 *a) {
    S5516E0 *r = func_00159ea8(a, D_00351A00, D_00351A10);
    S5516E0 **pp = &D_005516E0;
    *pp = r;
    r->f30 = 0.5f;
    (*pp)->f34 = 250.0f;
    a->p6C->fCC = 0.20943951606750488f;
    func_002675a8(a->x3C0, D_002C58A0);
    D_002BC0F0.f0 = 10000.0f;
    D_002BC0F0.f4 = 4000.0f;
    D_002BC0F0.f8 = 64.0f;
    D_002BC0F0.fC = 255.0f;
    D_002BC0F0.w10 = D_003519E0.w0;
    D_002BC0F0.w14 = D_003519E0.w4;
    D_002BC0F0.w18 = D_003519E0.w8;
}

/* ---- func_00158100 ---- */
typedef struct { u8 pad[0xC]; void *pC; } Task158100;
void func_001580e8(void);

s32 func_00158100(s32 *a, f32 *v) {
    if (*v > 0.7999999523162842f) {
        func_00130340(a, 0x010000D1, 0.0f);
        func_00130578(a, 0x40000000, 0.0f);
    } else if (*v < -0.7999999523162842f) {
        func_00130340(a, 0x010000D2, 0.0f);
        func_00130578(a, 0x40000000, 0.0f);
    } else {
        *a |= 0x20;
        func_00130340(a, 0x010000D0, 0.0f);
        ((Task158100 *)func_00130578(a, 0x40000000, 0.0f))->pC = func_001580e8;
    }
    return 0;
}

/* ---- func_00158c78 ---- */
extern u32 D_002E31A8;
extern u32 D_0037A378;
typedef struct { u8 pad[0x48E]; u8 b48E[3]; u8 pad491[0x3E3]; s32 w874; } S304BE8;
extern S304BE8 *D_00304BE8;
s32 func_001140a0(void);

s32 func_00158c78(void) {
    s32 m = func_001140a0();
    s32 r = 0;
    if (!(D_002C5958 & 0x92000)) {
        if (!((D_002E31A8 >> 1) & 1)) {
            if (!(D_00304BE8->w874 & 0x40)) {
                if (!((D_0037A378 >> 1) & 1)) {
                    if (m == 0 || m == 2 || (m == 3 && ((D_0037A378 >> 4) & 1))) r = 1;
                }
            }
        }
    }
    return r;
}

/* ---- func_00159178 ---- */
typedef struct { s32 w0; s32 w4; } Arg159178;
void func_0013dc10(void *, s32);
void func_0012ec60(s32, s32, void *);
void func_002673b8(void *, void *);
void func_00159148(void *, f32);

void func_00159178(Obj154c60 *a, s32 b, Arg159178 *s, Vec154768 *o) {
    Vec154768 t;
    func_0013dc10(a, b);
    func_00130578(a, 6, 8.0f);
    if (func_00122ff8((Act1576a8 *)s->w0)) {
        func_0012ec60(s->w0, s->w4, &t);
        func_00267530(&t, &t, (u8 *)a + 0x10);
        func_002673b8(o, &t);
    } else {
        func_002675a8(o, &a->v30);
    }
    func_00267560(a->x3C0, o, 8.0f);
    func_00267560(((Obj1545f0 *)a)->p148->x160, ((Obj1545f0 *)a)->p148->x160, 0.5f);
    func_00159148(a, 20.0f);
    o->w = 0.0f;
}

/* ---- func_00159258 / func_00159350 ---- */
extern S5516E0 *D_005516F0;
extern u8 D_002E2780[];
extern u8 D_00351A50[], D_00351A60[], D_00351A70[], D_00351A80[], D_00351A90[];
s32 func_0014efe0(void *, s32);
s32 func_00159258(void);
typedef struct { u8 pad[8]; f32 f8; } S6C_159350;
typedef struct { u8 pad[0x6C]; S6C_159350 *p6C; } Obj159350;

s32 func_00159258(void) {
    void *p = D_002E26A0[0];
    S5516E0 **pp;
    if (!func_00122ff8(p)) return 4;
    if (func_0014efe0(p, 1)) {
        pp = &D_005516F0;
        if ((*pp)->f30 > 0.0f) {
            (*pp)->f30 -= 0.003f;
            if ((*pp)->f30 < 0.0f) (*pp)->f30 = 0.0f;
        }
        func_002675a8(D_002E2780, D_00351A50);
    }
    if (func_0014efe0(p, 2)) func_002675a8(D_002E2780, D_00351A60);
    if (func_0014efe0(p, 3)) func_002675a8(D_002E2780, D_00351A70);
    return 0;
}

void func_00159350(Obj1545f0 *a) {
    S5516E0 *r;
    ((Obj159350 *)a)->p6C->f8 = 6.0f;
    func_00267560(a->p148->x160, a->p148->x160, 0.1f);
    if ((void *)a == D_002E26A0[0]) {
        r = func_00159ea8(a, D_00351A80, D_00351A90);
        D_005516F0 = r;
        r->f30 = 0.5f;
        func_0011ef10(0x18894, func_00159258);
    }
}

/* ---- func_00159740 ---- */
typedef struct { u16 a, b; } P159740;
typedef struct { u8 pad[0x54]; P159740 e[1]; } S308CDC_e;
typedef struct { u8 pad[0x100]; f32 f100; u8 pad104[0x5C]; u8 x160[4]; } S148_159740;
typedef struct { u8 pad[0x130]; S130_157818 *p130; u8 pad134[0x14]; S148_159740 *p148; u8 pad14c[0x264]; f32 f3B0; } Obj159740;
void func_00121fc4(void *, void *);

Ret157ea8 *func_00159740(Obj159740 *a, Vec154768 *o) {
    Ret157ea8 *r = (Ret157ea8 *)func_00130340(a, 0x10004, 0.0f);
    r->f4 = 4.0f;
    func_0014f658(a, 1);
    a->f3B0 = 0.0f;
    a->p148->f100 = 0.0f;
    func_00159148(a, ((S308CDC_e *)D_00308CDC)->e[a->p130->h4C].a);
    func_002675a8(o, a->p148->x160);
    o->y = 0.0f;
    func_00121fc4(o, o);
    return r;
}

/* ---- func_00159808 ---- */
typedef struct { u8 pad[0x160]; u8 x160[0xC]; f32 f16C; } S148_159808;
typedef struct { u8 pad[0x20]; Vec154768 v20; u8 pad30[0x118]; S148_159808 *p148; u8 pad14c[0x274]; u8 x3C0[4]; } Obj159808;
s32 func_00137618(void *);
void func_00267518(void *, void *, void *);
void func_001376e8(void *, void *);

void func_00159808(Obj159808 *a, Vec154768 *b) {
    Vec154768 t, u;
    if (b->w > 0.0f) b->w = 6.0f;
    func_002675a8(&a->v20, b);
    if (func_00137618(a)) {
        func_002675a8(&t, a->p148->x160);
        t.y = 0.0f;
        func_002673b8(&t, &t);
        func_00267560(&u, &t, a->p148->f16C);
        func_00267518(&u, &u, a->x3C0);
        func_001376e8(a, &u);
    }
}

/* ---- func_00159b48 ---- */
typedef struct { s32 w0; s32 idx; u8 pad8[8]; Vec154768 e[32]; } S551740;
extern S551740 D_00551740;
f32 D_00551734 ALIGNED(4);
f32 func_00120bf8(void *);

void func_00159b48(Vec154768 *p) {
    S551740 *s = &D_00551740;
    Vec154768 *e = s->e;
    Vec154768 t;
    func_00267530(&t, p, &e[s->idx]);
    t.w = func_00120bf8(&t);
    if (D_00551734 * 0.03125f <= t.w) {
        s->idx = (s->idx + 1) % 32;
        func_002675a8(&e[s->idx], p);
        s->e[s->idx].w = t.w;
    }
}

/* ---- func_00158df8 ---- */
extern s32 *D_005516E4;
extern s32 D_005516E8;
extern s32 D_00351A48;
extern char D_0048E718[];
s32 D_00F20000(); /* code at a fixed address (overlay) */
s32 func_00158d30(void);
void func_00155be0(s32);
void func_001763f0(void *);
s32 func_00120748(char *, void *, void (*)(void), s32);
void func_00158db0(void);

void func_00158df8(s32 a, s32 b, s32 *t) {
    s32 i;
    s32 *p;
    if (func_00158d30()) {
        D_005516E4 = t;
        D_005516E8 = (s32)t + t[1];
        func_00155be0(D_005516E8);
        for (i = 0, p = t + 1; i < 5; i++, p++) {
            if (p[2] - p[1] > 0) func_001763f0((u8 *)t + p[1]);
        }
        func_00120748(D_0048E718, (void *)D_00F20000, func_00158db0, 0);
    } else {
        D_00351A48 = 0;
    }
}

/* ---- func_00157400 ---- */
typedef struct { u8 pad[0x48]; void *p48; } Task157400;
s32 func_001571a8(s32, s32);
Task157400 *func_001208e0(void *);
void func_001573d8(s32);

void func_00157400(void (*cb)(s32)) {
    s32 i, n = 0;
    u8 *q;
    for (i = 0; i < 3; i++) {
        q = (u8 *)(i + (s32)D_00304BE8) + 0x48E;
        if (*q != 0xFF) {
            if (func_001571a8(*q, 0)) n++;
        }
    }
    if (n > 0) {
        func_001208e0(func_001573d8)->p48 = cb;
    } else {
        cb(-1);
    }
}

/* needs make: uses rodata */
/* ---- func_00158b88 (switch jump table) ---- */
s32 func_00158af0(s32, s32);

s32 func_00158b88(s32 a, u8 *b) {
    switch (*b) {
    case 0x4B:
        return func_00158af0(a, 0);
    case 0x4D:
    case 0x4E:
        return D_00F20000(7, 0);
    case 0x57:
        return func_00158af0(a, 1);
    case 0x58:
    case 0x59:
        return D_00F20000(8, 0);
    case 0x5E:
        return func_00158af0(a, 2);
    case 0x5F:
    case 0x60:
        return D_00F20000(9, 0);
    case 0x5A:
        return func_00158af0(a, 3);
    case 0x5B:
        return D_00F20000(11, 0);
    case 0x52:
        func_00158af0(a, 4);
        break;
    }
}
#include "data/bss_0055_mixed.h"
