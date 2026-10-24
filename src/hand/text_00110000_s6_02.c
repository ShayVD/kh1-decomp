#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004D.h"
typedef W_2c5968 F5968;

/* ---- 00114880 ---- */
extern s32 D_003F6E28;
extern volatile s32 D_002BD114;
extern s32 D_004D9330, D_004D9320, D_002BD110;
s32 func_00102a48(s32, s32);
s32 func_00112d80(void);
s32 sceGsSyncPath(s32, s32);
void func_00121ee0(s32);
void func_00176388(s32);
CONTEXT_ONLY void func_00113a48(void) {}

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
    if ((*(volatile u8 *)((W_2c5968 *)&D_002C5968) >> 3) & 3) return;
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
        (*(W_2c5968 *)&D_002C5968).w = 0;
        return 0;
    }
    saved = D_002BD114;
    p = ((W_2c5968 *)&D_002C5968);
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

/* ---- 00113558 ---- */
#include "vm/script_vm.h"

/* ---- 00113af8 ---- */
extern s32 D_004D934C, D_004D9350, D_004D9354, D_004D9358, D_004D935C, D_004D9360;
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

/* ---- 00113fa8 ---- */
extern s32 D_003F6E28;
extern volatile s32 D_002BD114;
extern s32 D_004D9330, D_004D9320, D_002BD110;
s32 func_00102a48(s32, s32);
s32 func_00112d80(void);
s32 sceGsSyncPath(s32, s32);
void func_00121ee0(s32);
void func_00176388(s32);
void func_00113a48(void);

/* ---- 00114a38 ---- */
typedef struct { u8 *data; s32 *hdr; s32 pad8[2]; f32 m[4][4]; f32 pad50[3][4]; f32 v[8][4]; } Obj110;
Obj110 *D_004D9368 ALIGNED(8);

/* ---- 00115158 ---- */
typedef f32 V4_52[4] __attribute__((aligned(16)));

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

/* ---- 00116628 ---- */
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/pieces/D_003F6DF0.h"
#include "data/pieces/D_002BD110.h"
#include "data/pieces/D_002BD114.h"
