/* The game's timers (a guess at the name), 0x00111b08-0x00112270:
 * func_00111b10 ... func_00111be8 split a frame count into hours, minutes,
 * seconds and hundredths, func_00111d90 / func_00111ef0 start a count up or
 * down (D_004D9250 ... D_004D925C) as a frame task (func_0011ef10), and
 * func_00112150 fills D_004D9288 for the timer display of
 * src/hud/timer.c. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "common.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002A6208.h"
#include "data/types/text_00110000_h29_p3.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBF60.h"
#include "data/pieces/D_002BBFA0.h"
#include "data/pieces/D_002BBFE0.h"
#include "data/pieces/D_002BC020.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002BCDA0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/bss_0049.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/types/text_00110000_h29.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002BCD60.h"

/* func_00111b08 (from auto/text_00110000.c). */
s32 func_00111b08(s32 arg0) {
    return arg0;
}

/* func_00111b10 (from auto/text_00110000_6.c). */
#define func_00111b08 ((u32 (*)()) func_00111b08)
u32 func_00111b10(void) {
    return func_00111b08() / 216000U;
}
#undef func_00111b08

/* func_00111b48 (from hand/text_00110000_s6_02.c). */
#define func_00111b08 ((u32 (*)(u32)) func_00111b08)
u32 func_00111b48(u32 a) {
    u32 t, h, m;
    t = func_00111b08(a);
    h = t / 216000;
    t = t % 216000;
    m = t / 3600;
    return m;
}
#undef func_00111b08

/* func_00111b90 (from hand/text_00110000_s6_02.c). */
#define func_00111b08 ((u32 (*)(u32)) func_00111b08)
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
#undef func_00111b08

/* func_00111be8 (from hand/text_00110000_h29.c). */
#define func_00111b08 ((u32 (*)(u32)) func_00111b08)
u32 func_00111be8(u32 a) {
    u32 t, h, m, s;
    t = func_00111b08(a);
    h = t / 216000;
    t = t % 216000;
    m = t / 3600;
    t = t % 3600;
    s = t / 60;
    t = t % 60;
    {
        f32 r = (f32)t;
        r *= 1.6666667f;
        return (u32)r;
    }
}
#undef func_00111b08

/* func_00111ca8 (from auto/text_00110000_3.c). */
extern s32 D_002BCC24;
void func_00111ca8(void) {
    D_002BCC24 = 0;
}

/* func_00111cb8 (from hand/text_00110000_h29.c). */
extern f32 D_002BBDEC;
extern s32 D_004D925C;
extern s32 D_002BCC1C;
extern u32 D_004D9250;
s32 func_00111cb8(void) {
    switch (D_004D925C) {
    case 2:
        return 4;
    case 0:
        if (D_002BCC1C < D_004D9254) {
            D_002BCC1C = (f32)(D_002BBDF0 - D_004D9250) * D_002BBDEC;
            return 0;
        }
        D_002BCC1C = D_004D9254;
        return 4;
    case 1:
        return 0;
    }
    return 0;
}

/* func_00111d90 (from hand/text_00100000_h2.c). */
s32 func_0011ef10(s32, s32 (*)(void));
extern s32 D_004D9250_00111d90 __asm__("D_004D9250");
#define D_004D9250 D_004D9250_00111d90
s32 func_00111d90(s32 a) {
    D_004D925C = 0;
    D_004D9250 = D_002BBDF0;
    D_002BCC1C = 0;
    if (!a) D_004D9254 = 0x34b84;
    else D_004D9254 = 0x14996c4;
    return func_0011ef10(0x2c04c, func_00111cb8);
}
#undef D_004D9250

/* func_00111e00 (from hand/text_00110000_h29.c). */
extern void (*D_004D9258)(void);
s32 func_00111e00(void) {
    switch (D_004D925C) {
    case 2:
        return 4;
    case 0:
        if (D_002BCC1C > 0) {
            D_002BCC1C = (f32)D_004D9254 - (f32)(D_002BBDF0 - D_004D9250) * D_002BBDEC;
            return 0;
        }
        D_002BCC1C = 0;
        D_004D9258();
        return 4;
    case 1:
        return 0;
    }
    return 0;
}

/* func_00111ef0 (from hand/text_00100000_h2.c). */
extern s32 D_004D9250_00111ef0 __asm__("D_004D9250");
#define D_004D9250 D_004D9250_00111ef0
extern s32 D_004D9258_00111ef0 __asm__("D_004D9258");
#define D_004D9258 D_004D9258_00111ef0
s32 func_00111ef0(s32 sec, s32 b) {
    D_004D9258 = b;
    D_004D925C = 0;
    D_004D9250 = D_002BBDF0;
    D_002BCC1C = D_004D9254 = sec * 60;
    return func_0011ef10(0x2c04c, func_00111e00);
}
#undef D_004D9250
#undef D_004D9258

/* func_00111f58 (from auto/text_00110000.c). */
void func_00111f58(void) {
    D_004D925C = 1;
    D_002BCC24 = 1;
}

/* func_00111f70 (from anon/session1_probes.c): stops the timer. */
void func_00111f70(void)
{
    D_004D925C = 0;
    D_002BCC24 = 0;
}

/* func_00111f88 (from auto/text_00110000.c). */
s32 func_00111f88(void) {
    D_004D925C = 2;
    return D_002BCC1C;
}

/* func_00111fa0 (from auto/text_00110000.c). */
void func_00111fa0(s32 arg0) {
    D_002BCC1C = arg0 * 0x3C;
}

/* func_00111fb8 (from auto/text_00110000.c). */
extern s32 D_002BCC20;
void func_00111fb8(s32 arg0) {
    D_004D9274 = arg0;
    D_002BCC20 = 0;
}

/* func_00111fd0 (from auto/text_00110000.c). */
void func_00111fd0(s32 arg0) {
    D_002BCC20 = arg0;
}

/* func_00111fe0 (from auto/text_00110000.c). */
s32 func_00111fe0(s32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = D_002BCC20 + arg0;
    D_002BCC20 = temp_v0;
    if ((D_004D9274 == 0) || (var_v0 = 1, ((temp_v0 < D_004D9274) != 0))) {
        var_v0 = 0;
    }
    return var_v0;
}

/* func_00112018 (from hand/text_00110000_h29.c). */
extern W29Clock D_004D9288;
#define func_00111b10 ((s32 (*)(s32)) func_00111b10)
#define func_00111b48 ((s32 (*)(s32)) func_00111b48)
#define func_00111b90 ((s32 (*)(s32)) func_00111b90)
void func_00112018(s32 which, s32 t) {
    s32 h, m, s, f;
    if (t < 0) t = 0;
    h = func_00111b10(t);
    m = func_00111b48(t);
    s = func_00111b90(t);
    f = func_00111be8(t);
    if (which == 0) {
        D_004D9288.t[0].f = f;
        D_004D9288.t[0].s = s;
        D_004D9288.t[0].m = m;
        D_004D9288.t[0].h = h;
    } else {
        D_004D9288.t[1].f = f;
        D_004D9288.t[1].s = s;
        D_004D9288.t[1].m = m;
        D_004D9288.t[1].h = h;
    }
}
#undef func_00111b10
#undef func_00111b48
#undef func_00111b90

/* func_001120c8 (from hand/text_00100000_h2.c). */
typedef struct {
    u8 pad[0x10];
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1c;
} Hud;
extern Hud D_004D9288_001120c8 __asm__("D_004D9288");
#define D_004D9288 D_004D9288_001120c8
s32 func_001120c8(void) {
    func_00112018(0, D_002BCC1C);
    func_00112018(1, D_004D9260);
    if (D_002BCC20 < 0) D_002BCC20 = 0;
    if (D_004D9274 < 0) D_004D9274 = 0;
    D_004D9288.w10 = D_002BCC20;
    D_004D9288.w14 = D_004D9274;
    D_004D9288.w1c = D_002BCC20;
    return D_004D9280 ? 4 : 0;
}
#undef D_004D9288

/* func_00112150 (from hand/text_00110000_h29.c). */
void func_002485b8(W29Clock *);
#define func_0011ef10 ((void (*)(s32, void (*)(void))) func_0011ef10)
void func_00112150(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 s0, s32 s8) {
    D_004D9288.x20 = a1;
    D_004D9288.x0 = a0;
    D_004D9260 = a4;
    D_004D9288.x30 = a2;
    D_004D9288.x4 = a3;
    D_004D9288.x18 = a5;
    D_004D9288.xc = a6;
    D_004D9288.x8 = s8;
    D_004D9288.x24 = s0;
    D_004D9288.x1c = D_002BCC20;
    D_004D9288.x28 = 0;
    func_00112018(0, D_002BCC1C);
    func_00112018(1, D_004D9260);
    D_004D9288.x2c = a7;
    D_004D9288.x10 = D_002BCC20;
    D_004D9288.x14 = D_004D9274;
    func_002485b8(&D_004D9288);
    D_004D9280 = 0;
    func_0011ef10(0x280A0, func_001120c8);
}
#undef func_0011ef10

/* func_00112230 (from auto/text_00110000_11.c). */
M2C_UNK func_002485d0();
M2C_UNK func_002485e0();
void func_00112230(void) {
    D_004D9280 = 1;
    func_002485d0();
    func_002485e0();
}

/* func_00112258 (from auto/text_00110000_11.c). */
void func_00112258(void) {

}

/* func_00112260 (from auto/text_00110000_3.c). */
void func_00112260(void) {

}

/* func_00112268 (from auto/text_00110000_3.c). */
void func_00112268(void) {

}

