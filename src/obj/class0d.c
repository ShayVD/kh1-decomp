/* Object classes 0xD and 0xE: the handlers func_0013fc80 registers in the
 * class table D_00350D88 (func_0014f830(0xD / 0xE, ...)) and their helpers.
 * Flag mode: default (the other modes are in the sibling files). Read from
 * the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0052.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"

/* func_0013f450 (from auto/text_00130000_4.c). */
void func_0013f450(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) | 1);
}

/* func_0013f478 (from hand/text_00130000_h7.c). */
void func_00121fc4(f32 *d, f32 *s);
s32 func_0013f478(W7Ob *o, f32 *v) {
    f32 t[4];
    if (o->x300 == 0.0f || v[3] == 0.0f) {
        return 0;
    }
    PlatVu0SubVector(t, o->x2f0, o->x10);
    t[1] = 0.0f;
    func_00121fc4(t, t);
    if (PlatVu0InnerProduct(t, v) < 0.7f) {
        return 0;
    }
    return 1;
}

/* func_0013f618 (from auto/text_00130000_13.c). */
s32 func_001375f0(s32);
s32 func_0013f330(s32, s32);
void func_00130398(s32, s32, f32);
void func_00130578(s32, s32, f32);
void func_0014f658(s32, s32);
#define func_0013f478 ((s32 (*)(s32, s32)) func_0013f478)
s32 func_0013f618(s32 arg0, s32 arg1) {
    if ((func_001375f0(arg0) != 0) && (func_0013f478(arg0, arg1) != 0)) {
        func_0014f658(arg0, 0xD);
        func_00130398(arg0, func_0013f330(arg0, 0x1D) | 0x01000000, 0.0f);
        func_00130578(arg0, func_0013f330(arg0, 0x1B) | 0x40000000, 0.0f);
        M2C_FIELD(arg0, f32 *, 0x2C) = 0.0f;
        return 1;
    }
    return 0;
}
#undef func_0013f478

/* func_0013f6d0 (from auto/text_00130000_13.c). */
f32 atan2f(f32, f32);
void func_0013f6d0(s32 arg0, s32 arg1) {
    func_00130398(arg0, func_0013f330(arg0, 0x23) | 0x01000000, 8.0f);
    func_00130578(arg0, 0x40000000, 0.0f);
    PlatVu0CopyVector(arg1, arg0 + 0x30);
    M2C_FIELD(arg1, f32 *, 0xC) = 0.0f;
    M2C_FIELD(arg0, f32 *, 0x150) = atan2f(M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg1, f32 *, 8));
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
}

/* func_0013f8a8 (from auto/text_00130000_13.c). */
void func_0013f8a8(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f1;

    temp_f1 = M2C_FIELD(arg2, f32 *, 0xC);
    if (temp_f1 > 0.0f) {
        if ((M2C_FIELD(arg2, f32 *, 4) > 0.0f) && (temp_f1 > 0.8f)) {
            M2C_FIELD(arg2, f32 *, 0xC) = 12.0f;
            return;
        }
        M2C_FIELD(arg2, f32 *, 0xC) = 2.0f;
    }
}

/* func_0013fba0 (from auto/text_00130000_10.c). */
M2C_UNK func_00137688(void *, f32);
f32 func_001376e8(void *, void *);
s32 func_0013fba0(void *arg0, s32 arg1) {
    s32 sp[4];
    s32 var_v0;

    if ((arg1 != 0) || (var_v0 = 0, (M2C_FIELD(arg0, f32 *, 0x24) <= 0.0f))) {
        PlatVu0SubVector(sp, M2C_FIELD(arg0, s32 *, 0x148) + 0x40, arg0 + 0x10);
        func_00137688(arg0, func_001376e8(arg0, sp));
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

/* func_0013fc08 (from auto/text_00130000.c). */
M2C_UNK func_0013f770();
s32 func_0013fc08(void *o, void *v) {
    func_0013f770(o, v);
    return 0;
}

/* func_0013fc28 (from auto/text_00130000_4.c). */
#define func_0014f658 ((s32 (*)(s32, s32)) func_0014f658)
void func_0013fc28(s32 arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x164);
    if ((temp_v1 != 0x23) && (temp_v1 != 0x2C)) {
        func_0014f658(arg0, 0);
    }
}
#undef func_0014f658

/* func_0013fc68 (from auto/text_00130000_2.c). */
s32 func_0013fc68(void *arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (arg1 != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x70);
    }
    return var_v0;
}

/* func_0013fc80 (from auto/text_00130000_5.c). */
void func_0013f358();
void func_0013f910();
void func_0014f748();
void func_0014f778();
void func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *);
void func_0013fc80(void) {
    func_0014f830(0xD, 1, &func_0013f358, &func_0013f450, &func_0013f910, &func_0014f748, &func_0013fba0, &func_0013f8a8, &func_0013fc08);
    func_0014f830(0xE, 1, NULL, NULL, &func_0013fc28, &func_0014f778, &func_0013fc68, NULL, NULL);
}

