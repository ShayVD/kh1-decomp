#include "common.h"
#include "data/bss_004D.h"
typedef union { u32 w; struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 r:29; } f; u8 c[4]; } F5968;
extern F5968 D_002C5968;

/* ---- 00114880 ---- */
extern s32 D_003F6E28;
extern volatile s32 D_002BD114;
extern s32 D_004D9330, D_002B6778, D_004D9320, D_002BD110;
extern volatile s32 D_002BBDE0;
s32 func_00102a48(s32, s32);
s32 func_00112d80(void);
s32 sceGsSyncPath(s32, s32);
void func_00121ee0(s32);
void func_00176388(s32);
CONTEXT_ONLY void func_00113a48(void) {}

void func_00114880(void) {
    if (D_002BBDE0 == 3) { if (D_002BD110) do { func_00113a48(); } while (0); }
}

/* ---- 0010f658 ---- */
extern u8 D_002BBCC0[];
s32 D_004D5B0C ALIGNED(4);
s32 sceGsSyncPath(s32, s32);
s32 func_00106b18(void *);
void func_001104e0(void);
extern u8 D_002BBC20[];
CONTEXT_ONLY void func_0010f580(void) {
    func_00106b18(D_002BBC20);
    sceGsSyncPath(0, 0);
}
void func_0010f5a8(void);
void func_0010f5d0(void);
void func_0010f5f8(void);
void func_001fd100(s32, s32);
u8 *func_001efc10(s32);
void func_001f1ed8(s32, s32, s32, u8 *, s32);
void func_00207748(s32, s32, s32, s32);

void func_0010f658(s32 a) {
    if ((*(volatile u8 *)&D_002C5968 >> 3) & 3) return;
    if (a == 0) {
        sceGsSyncPath(0, 0);
        func_001104e0();
        *(volatile u64 *)0x12000000 = 0x22;
        return;
    }
    sceGsSyncPath(0, 0);
    func_001104e0();
    if (a & 4) {
        func_0010f580();
        func_00106b18(D_002BBCC0);
        if (D_004D5B0C == 0) {
            func_001fd100(76, 11);
            func_001f1ed8(0x64ffffff, 118, 16, func_001efc10(3), 15);
            func_00207748(1, 351, 92, 90);
        } else {
            func_001fd100(84, 30);
            func_001f1ed8(0x64ffffff, 126, 39, func_001efc10(4), 15);
            func_00207748(1, 351, 70, 90);
        }
        func_0010f5a8();
        func_00106b18(D_002BBCC0);
        func_0010f5d0();
        func_0010f5f8();
        return;
    } else if (a & 2) {
        func_0010f580();
        func_00106b18(D_002BBCC0);
        func_001fd100(96, 30);
        func_001f1ed8(0x64ffffff, 138, 39, func_001efc10(2), 15);
        func_0010f5a8();
        func_00106b18(D_002BBCC0);
        func_0010f5d0();
        func_0010f5f8();
        return;
    } else if (a & 1) {
        func_0010f580();
        func_00106b18(D_002BBCC0);
        func_001fd100(84, 30);
        func_001f1ed8(0x64ffffff, 126, 39, func_001efc10(1), 15);
        func_0010f5a8();
        func_00106b18(D_002BBCC0);
        func_0010f5d0();
        func_0010f5f8();
        return;
    }
}

/* ---- 0010f918 ---- */
extern s32 D_002BBD40;
extern s32 D_002B6484;
extern volatile s32 D_002BD114;
extern s32 D_004D5B0C;
extern u32 D_004D5B00;
extern u32 D_004D5B08;
extern volatile s32 D_002C5AD0[3];
CONTEXT_ONLY void func_0010f8d0(s32 a) {}
void func_00113e28(s32);
void func_0010fd40(void);
void func_001220d0(void);
void func_0010f8b8(void);
s32 func_00111090(void);
void func_00111190(void);
void func_0011de90(void);
void func_001104e0(void);
void func_0011d768(s32);

s32 func_0010f918(void) {
    volatile s32 run;
    s32 saved;
    u32 cur; F5968 on, off, on2, off2;
    s32 fl;
    s32 changed;
    s32 started;
    volatile F5968 *p;

    if (D_002BBD40 == 0 && D_002B6484 == 1) {
        D_002C5968.w = 0;
        return 0;
    }
    saved = D_002BD114;
    p = &D_002C5968;
    D_004D5B0C = 0;
    run = 1;
    started = 0;
    changed = 0;
    fl = 0;
    do {
        cur = p->w;
        on.w = (D_004D5B00 ^ cur) & cur;
        off.w = (D_004D5B00 ^ cur) & ~cur;
        on2.w = (D_004D5B08 ^ cur) & cur;
        off2.w = (D_004D5B08 ^ cur) & ~cur;
        if (on.f.b0 == 1) { fl |= 1; changed = 1; func_0010f8d0(fl); }
        if (off.f.b0 == 1) { fl &= ~1; func_0010f8d0(fl); }
        if (on.f.b1 == 1) { fl |= 2; changed = 1; func_0010f8d0(fl); }
        if (off.f.b1 == 1) { fl &= ~2; func_0010f8d0(fl); }
        if (on2.f.b2 == 1) { fl |= 4; changed = 1; func_0010f8d0(fl); }
        if (off2.f.b2 == 1) { fl &= ~4; func_0010f8d0(fl); }
        if (started == 0 && fl != 0) {
            started = 1;
            func_00113e28(fl);
        }
        if (started == 1 && fl == 0) {
            func_00113e28(0);
        }
        if (fl != 0) {
            D_002BD114 = 1;
            func_0010fd40();
            func_001220d0();
            func_0010f8b8();
            if (func_00111090()) func_00111190();
            func_0011de90();
            func_001104e0();
            if ((fl & 4) && (D_002C5AD0[2] & 0x2000)) {
                func_0011d768(2);
                if (D_004D5B0C == 0) {
                    D_004D5B0C = 1;
                    func_0010f8d0(fl);
                } else {
                    p->c[0] &= ~4;
                }
            }
        } else {
            D_002BD114 = 0;
            run = 0;
        }
    } while (run);
    D_002BD114 = saved;
    return changed;
}

/* ---- 00111b48 ---- */
u32 func_00111b08(u32);
u32 func_00111b48(u32 a) {
    u32 t, h, m;
    t = func_00111b08(a);
    h = t / 216000;
    t = t % 216000;
    m = t / 3600;
    return m;
}
u32 func_00111b90(u32 a) {
    u32 t, h, m, s;
    t = func_00111b08(a);
    h = t / 216000;
    t = t % 216000;
    m = t / 3600;
    t = t % 3600;
    s = t / 60;
    return s;
}

/* ---- 00113558 ---- */
extern s32 D_002BBE0C;
extern s32 D_002B6774, D_002BCDEC, D_0029B410, D_0029B414, D_002BC130;
typedef struct { u32 b0:2; u32 b2:1; u32 b3:24; u32 b27:1; u32 r:4; } F58;
extern volatile u32 D_002C5958;
extern s32 D_002BCC90, D_002BCDBC, D_002BCDC0, D_002BCDD8, D_002C1388, D_002BBE1C, D_002B6474, D_002BCDC4;
s32 func_00105860(void);
void func_0017f678(void);
void func_00132550(void);
void func_00175f58(s32, s32, s32, s32);
void func_00100ab0(void);
void func_001c3770(s32, s32);
void func_00114830(void);
void func_001115e0(void);
void func_00111380(void);
void func_001118c0(void);
void func_001ec7c0(s32);

s32 func_00113558(void) {
    if (D_002B6774) return 0;
    D_002BBE0C = 1;
    func_00105860();
    func_0017f678();
    func_00132550();
    D_002BCDEC = 1;
    if (D_0029B410 && D_0029B414) func_00175f58(D_0029B410, D_0029B414, D_002BC130 + 1, 100000);
    func_00100ab0();
    { F58 *p = (F58 *)&D_002C5958; p->b2 = 0; p->b27 = 0; }
    func_001c3770(D_002BCC90, 0);
    D_002BCDBC = 0;
    D_002BCDC0 = 0;
    D_002BCDD8 = 0;
    func_00114830();
    D_002C1388 = 0;
    if (D_002BBE1C == 1 || D_002B6474 == 1) func_001115e0();
    D_002BBE1C = 0;
    func_00111380();
    func_001118c0();
    func_001ec7c0(0);
    D_002BCDC4 = 0;
    return 4;
}

/* ---- 00113af8 ---- */
extern s32 D_004D9340, D_004D9344, D_004D9348, D_004D9364;
extern s32 D_004D934C, D_004D9350, D_004D9354, D_004D9358, D_004D935C, D_004D9360;
extern s32 D_002BD118;
void func_00113a00(void);
void func_00113ab0(s32);
void func_00113df8(s32);
void func_00113e28(s32);
CONTEXT_ONLY void func_001137f8(void) {}

static inline void add6(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    D_004D934C += a;
    D_004D9350 += b;
    D_004D9354 += c;
    D_004D9358 += d;
    D_004D935C += e;
    D_004D9360 += f;
}
void func_00113af8(void) {
    switch (D_004D9340) {
    case 1:
        switch (D_004D9344) {
        case 0:
            if (D_004D9348 < 2) {
                add6(0, 0, 0, 50, 15, 25);
                break;
            }
            D_004D9344 = 1;
        case 1:
            if (D_004D9348 < 5) {
                add6(25, 2, -68, 9, 15, 25);
                break;
            }
            D_004D9344 = 2;
        case 2:
            D_004D9364 = 0;
            func_00113a00();
            break;
        }
        break;
    case 2:
        switch (D_004D9344) {
        case 0:
            if (D_004D9348 < 2) {
                add6(0, 0, 0, -14, -15, -25);
                break;
            }
            D_004D9344 = 1;
        case 1:
            if (D_004D9348 < 5) {
                add6(-25, -2, 68, -33, -15, -25);
                break;
            }
            D_004D9344 = 2;
        case 2:
            func_00113ab0(0);
            if (D_002BD118 == 2) func_00113df8(0);
            else func_00113e28(0);
            D_004D9340 = 0;
            return;

        }
        break;
    case 0:
    default:
        return;
    }
    func_001137f8();
    D_004D9348++;
}

/* ---- 00113fa8 ---- */
extern s32 D_003F6E28;
extern volatile s32 D_002BD114;
extern s32 D_004D9330, D_002B6778, D_004D9320, D_002BD110;
extern volatile s32 D_002BBDE0;
s32 func_00102a48(s32, s32);
s32 func_00112d80(void);
s32 sceGsSyncPath(s32, s32);
void func_00121ee0(s32);
void func_00176388(s32);
void func_00113a48(void);

s32 func_00113fa8(void) {
    func_00102a48(128, 0);
    if (D_003F6E28) {
        D_003F6E28 = 0;
        func_00112d80();
    }
    D_004D9330 = 0;
    D_002BD114 = 0;
    sceGsSyncPath(0, 0);
    func_00121ee0(D_002B6778);
    func_00176388(0);
    D_004D9320 = 0;
    return 4;
}

/* ---- 00114a38 ---- */
typedef struct { u8 *data; s32 *hdr; s32 pad8[2]; f32 m[4][4]; f32 pad50[3][4]; f32 v[8][4]; } Obj110;
typedef struct { u8 pad[0x18]; s32 ofs; } Hdr;
Obj110 *D_004D9368 ALIGNED(8);
extern s32 D_004D936C;
extern f32 D_002BBFA0[4][4];
extern f32 D_0029B280[4][4];
extern u8 D_002BD140[];
Obj110 *func_00122048(s32, s32);
void func_002672f8(f32 *, s32, u8 *);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
s32 func_0024edf0(f32 (*)[4], f32 (*)[4]);
void func_00106bd8(void *, s32);
void func_00108df8(s32, s32, s32, u8 *, s32);
void func_001220b8(Obj110 *);

s32 func_00114a38(s32 a, Hdr *h, s32 id, s32 d) {
    s32 r;
    Obj110 *o;
    o = func_00122048(272, 128);
    D_004D9368 = o;
    o->hdr = &h->ofs;
    o->data = (u8 *)h + h->ofs;
    r = 0;
    func_002672f8(o->v[0], a, o->data);
    func_002672f8(D_004D9368->v[1], a, D_004D9368->data + 16);
    func_002672f8(D_004D9368->v[2], a, D_004D9368->data + 32);
    func_002672f8(D_004D9368->v[3], a, D_004D9368->data + 48);
    func_002672f8(D_004D9368->v[4], a, D_004D9368->data + 64);
    func_002672f8(D_004D9368->v[5], a, D_004D9368->data + 80);
    func_002672f8(D_004D9368->v[6], a, D_004D9368->data + 96);
    func_002672f8(D_004D9368->v[7], a, D_004D9368->data + 112);
    sceVu0MulMatrix(D_004D9368->m, D_002BBFA0, D_0029B280);
    if (func_0024edf0(D_004D9368->m, (f32 (*)[4])D_004D9368->v) == 0) {
        if (id == 40000) func_00106bd8(D_002BD140, 40000);
        func_00108df8(D_004D936C++, id, a, D_004D9368->data, d);
        r = 1;
    }
    func_001220b8(D_004D9368);
    return r;
}

/* ---- 00115158 ---- */
typedef f32 V4_52[4] __attribute__((aligned(16)));
void func_00104f10(s32, V4_52);

static inline void v52_sub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline f32 v52_dot(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

s32 func_00115158(f32 *a, f32 *b, f32 *n) {
    V4_52 v;
    v52_sub(v, b, a);
    if (v52_dot(v, n) >= 0.0f) return 0;
    return 1;
}

s32 func_001151a8(s32 id, f32 *n) {
    V4_52 v;
    func_00104f10(id, v);
    if (v52_dot(v, n) >= 0.0f) return 0;
    return 1;
}

/* ---- 00116628 ---- */
typedef struct { u8 pad[0x2c]; s32 x2c; s32 x30; u8 pad34[4]; s16 x38; s16 x3a; u8 pad3c[2]; s16 x3e; u8 pad40[0x20]; s32 x60; u8 pad64[8]; s16 x6c; s16 x6e; s16 x70; u8 pad72[2]; s16 x74; s16 x76; } Ent628;

void func_00116628(Ent628 *e) {
    e->x30 = 0;
    e->x38 = 0;
    e->x2c = -1;
    e->x60 = 0;
    e->x76 = -1;
    e->x74 = -1;
    e->x70 = -1;
    e->x6e = -1;
    e->x6c = -1;
    e->x3e = -1;
    e->x3a = -1;
}
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/pieces/D_003F6DF0.h"
