/* The frame's end and the field's set-up files (a guess at the name),
 * 0x0010f580-0x0010fe80: func_0010f658 flips the display (the GS PMODE at
 * 0x12000000), func_0010f918 the soft reset / pause check, func_0010fc38 /
 * func_0010fc98 load allset.set and allarea.nam, and func_0010fd40 reads
 * the pads with the demo playback (D_004D9240, D_002BCA00). Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "common.h"
#include "platform/gs.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_0048CC30.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C60.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h29_p.h"

/* func_0010f580 (from auto/text_00100000_9.c). */
M2C_UNK func_00106b18(M2C_UNK *);
extern M2C_UNK D_002BBC20;
void func_0010f580(void) {
    func_00106b18(&D_002BBC20);
    PlatGsSyncPath(0, 0);
}

/* func_0010f5a8 (from auto/text_00100000_9.c). */
extern M2C_UNK D_002BBCF0;
void func_0010f5a8(void) {
    func_00106b18(&D_002BBCF0);
    PlatGsSyncPath(0, 0);
}

/* func_0010f5d0 (from auto/text_00100000_9.c). */
extern M2C_UNK D_002BBD30;
void func_0010f5d0(void) {
    func_00106b18(&D_002BBD30);
    PlatGsSyncPath(0, 0);
}

/* func_0010f5f8 (from hand/text_00100000_h2.c). */
void func_0010f5f8(void) {
    PlatGsSyncPath(0, 0);
    PlatGsPutPmode(0xff03);
    PlatGsPutDispfb1(0x11b0);
    PlatGsPutDisplay1(0x0007f9ff020d227cUL);
}

/* func_0010f658 (from hand/text_00110000_s6_02.c). */
extern u8 D_002BBCC0[];
s32 D_004D5B0C ALIGNED(4);
void func_001104e0(void);
void func_001fd100(s32, s32);
u8 *func_001efc10(s32);
void func_001f1ed8(s32, s32, s32, u8 *, s32);
void func_00207748(s32, s32, s32, s32);
#define func_00106b18 ((s32 (*)(void *)) func_00106b18)
void func_0010f658(s32 a) {
    if ((*(volatile u8 *)((W_2c5968 *)&D_002C5968) >> 3) & 3) return;
    if (a == 0) {
        PlatGsSyncPath(0, 0);
        func_001104e0();
        PlatGsPutPmode(0x22);
        return;
    }
    PlatGsSyncPath(0, 0);
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
#undef func_00106b18

/* func_0010f8a0 (from auto/text_00100000_3.c). */
extern s32 D_004D5B00;
void func_0010f8a0(void) {
    D_004D5B00 = D_002C5968;
}

/* func_0010f8b8 (from auto/text_00100000_3.c). */
extern s32 D_004D5B08;
void func_0010f8b8(void) {
    D_004D5B08 = D_002C5968;
}

/* func_0010f8d0 (from auto/text_00100000.c). */
M2C_UNK func_00111170(s32);
s32 func_00111090();
#define func_0010f658 ((M2C_UNK (*)()) func_0010f658)
void func_0010f8d0(s32 arg0) {
    func_0010f658();
    if (func_00111090() != 0) {
        func_00111170(arg0);
    }
}
#undef func_0010f658

/* func_0010f918 (from hand/text_00110000_s6_02.c). */
typedef W_2c5968 F5968;
extern s32 D_002BBD40;
extern s32 D_002B6484;
extern volatile s32 D_002BD114;
extern volatile s32 D_002C5AD0[3];
void func_00113e28(s32);
void func_0010fd40(void);
void func_001220d0(void);
void func_00111190(void);
void func_0011de90(void);
void func_0011d768(s32);
extern u32 D_004D5B00_0010f918 __asm__("D_004D5B00");
#define D_004D5B00 D_004D5B00_0010f918
extern u32 D_004D5B08_0010f918 __asm__("D_004D5B08");
#define D_004D5B08 D_004D5B08_0010f918
#define func_00111090 ((s32 (*)(void)) func_00111090)
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
#undef D_004D5B00
#undef D_004D5B08
#undef func_00111090

/* func_0010fbe0 (from auto/text_00100000_9.c). */
void func_0010fbe0(s32 arg0) {
    s32 *temp_a0;
    s32 *temp_v1_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a3;
    void *var_a2;

    var_a2 = arg0 + 0x10;
    var_a3 = 0;
    do {
        temp_v1 = var_a3 * 4;
        temp_a0 = temp_v1 + (s8 *)&D_002BBD48;
        temp_v1_2 = temp_v1 + (s8 *)(M2C_UNK *)&D_002BBD90;
        var_a3 += 1;
        *temp_a0 = arg0 + M2C_FIELD(var_a2, s32 *, 0);
        temp_v0 = M2C_FIELD(var_a2, s32 *, 4);
        var_a2 += 8;
        *temp_v1_2 = temp_v0;
    } while (var_a3 < 0x11);
}

/* func_0010fc38 (from auto/text_00100000_10.c). */
M2C_UNK memcpy(M2C_UNK *, s32, s32);
extern M2C_UNK D_0048CF10;
M2C_UNK D_004D5B10[0x400] ALIGNED(16);
s32 func_001205f0(M2C_UNK *, s32);
s32 func_001559f0(M2C_UNK, M2C_UNK);
#define func_0010fbe0 ((M2C_UNK (*)(M2C_UNK *)) func_0010fbe0)
void func_0010fc38(void) {
    s32 temp_v0;

    temp_v0 = func_001559f0(0x34, 0xC);
    memcpy(&D_004D5B10, temp_v0, func_001205f0(&D_0048CF10, temp_v0));
    func_0010fbe0(&D_004D5B10);
}
#undef func_0010fbe0

/* func_0010fc98 (from hand/text_00100000_h2.c). */
extern u8 D_0048CF20[];
extern u8 D_004D6B10[];
#define func_001559f0 ((void *(*)(s32, s32)) func_001559f0)
#define func_001205f0 ((s32 (*)(void *, void *)) func_001205f0)
#define memcpy ((void *(*)(void *, const void *, u32)) memcpy)
void *func_0010fc98(void) {
    void *p = func_001559f0(52, 12);
    s32 n = func_001205f0(D_0048CF20, p);
    return memcpy(D_004D6B10, p, n);
}
#undef func_001559f0
#undef func_001205f0
#undef memcpy

/* func_0010fce8 (from auto/text_00100000_14.c). */
M2C_UNK D_004D6B20[0x8c8] ALIGNED(32);
#define D_004D6B10 (*(M2C_UNK (*)) &D_004D6B10)
void *func_0010fce8(s32 arg0, s32 arg1) {
  s8 *new_var;
  void *temp_v0;
  temp_v0 = ((s8 *) (&D_004D6B10)) + (*((M2C_UNK *) (((s8 *) ((s8 *) (&D_004D6B20))) + (arg0 * 8))));
  new_var = ((s8 *) (temp_v0 + (arg1 * 8))) + 0x10;
  return temp_v0 + (*((s32 *) new_var));
}
#undef D_004D6B10

/* func_0010fd18 (from auto/text_00100000.c). */
extern s32 D_002BC128;
extern s32 D_002BC130;
#define func_0010fce8 ((M2C_UNK (*)(s32, s32)) func_0010fce8)
void func_0010fd18(void) {
    func_0010fce8(D_002BC128, D_002BC130);
}
#undef func_0010fce8

/* func_0010fd40 (from hand/text_00110000_h29.c). */
extern W29S70 D_002BCA00[2];
void func_0011f668(void);
void func_001ba4a8(void);
extern W29S70 D_002C5AD0_0010fd40[2] __asm__("D_002C5AD0");
#define D_002C5AD0 D_002C5AD0_0010fd40
#define func_0010f8a0 ((s32 (*)(void)) func_0010f8a0)
void func_0010fd40(void) {
    s32 i;
    func_0010f8a0();
    if (D_004D9240) {
        for (i = 0; i < 2; i++) D_002C5AD0[i] = D_002BCA00[i];
    }
    func_0011f668();
    for (i = 0; i < 2; i++) D_002BCA00[i] = D_002C5AD0[i];
    if (D_004D9240) func_001ba4a8();
}
#undef D_002C5AD0
#undef func_0010f8a0

