/* The first handlers of object classes 9 and 0xA (func_0013fd10,
 * func_0013fd20, func_0013fd38, func_0013fd60, registered by func_00141138
 * in class0a.c) and the helpers the class 9 / 0xA / 0xB handlers in class0a
 * call (func_0013fd88, func_0013fe10, func_0013fe28, func_0013fe80,
 * func_0013ff00). Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0052.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "common.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"

/* func_0013fd10 (from auto/text_00130000_2.c). */
void func_0013fd10(s32 *arg0) {
    *arg0 |= 0x30;
}

/* func_0013fd20 (from auto/text_00130000_2.c). */
void func_0013fd20(s32 *arg0) {
    *arg0 &= ~0x30;
}

/* func_0013fd38 (from auto/text_00130000_2.c). */
void func_0013fd38(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) | 0x200000);
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) & ~1);
}

/* func_0013fd60 (from auto/text_00130000_4.c). */
void func_0013fd60(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) | 1);
}

/* func_0013fd88 (from hand/text_00130000_h7.c). */
f32 fmodf(f32, f32);
f32 func_0013fd88(f32 a) {
    f32 r = fmodf(a, 66.66666412353516f);
    while (r < 0.0f) {
        r += 66.66666412353516f;
    }
    return r / 66.66666412353516f;
}

/* func_0013fe10 (from auto/text_00130000.c). */
#define func_0013fd88 ((M2C_UNK (*)(f32)) func_0013fd88)
void func_0013fe10(Actor *arg0) {
    func_0013fd88(arg0->unk014);
}
#undef func_0013fd88

/* func_0013fe80 (from auto/text_00130000_4.c). */
f32 func_0026b9c0(f32, f32);
f32 func_0013fe80(f32 fparg0) {
    f32 temp_f0;
    f32 var_f20;

    temp_f0 = func_0026b9c0(fparg0, 66.666664124f);
    var_f20 = fparg0 - temp_f0;
    if (temp_f0 < -33.3333321f) {
        var_f20 -= 66.666664124f;
    } else if (temp_f0 > 33.3333321f) {
        var_f20 += 66.666664124f;
    }
    return var_f20;
}

