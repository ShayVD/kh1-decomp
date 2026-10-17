/* Hand-matched functions near 0x153000-0x15a000 (worker 35). Built without
 * strict aliasing. */
#include "common.h"

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
