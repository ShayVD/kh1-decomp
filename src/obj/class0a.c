/* Object classes 9, 0xA and 0xB: the handlers func_00141138 registers in the
 * class table D_00350D88 (func_0014f830(9 / 0xA / 0xB, ...)) that lie in
 * 0x00140000-0x00141200, and their helpers (class 9's and 0xA's first two
 * handlers, 0x0013fd10-0x0013fd60, are in src/obj/class09.c
 * with the helpers these handlers call). Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_00304D64.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00130000_h7.h"

/* func_00140d50 (from auto/text_00140000_4.c). */
s32 func_00130398(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_00140d50(s32 arg0, s32 arg1) {
    func_00130398(arg0, 0x01000007, 8.0f);
    func_00130578(arg0, 0x40000000, 8.0f);
    PlatVu0CopyVector(arg1, arg0 + 0x30);
}

/* func_00140ee0 (from auto/text_00140000_10.c). */
extern f32 D_002BBDFC;
void func_00140ee0(s32 arg0, s32 arg1) {
    PlatVu0ScaleVector(arg1, arg0 + 0x20, D_002BBDFC);
}

/* func_00140f08 (from auto/text_00140000_15.c). */
s32 func_001375f0();
s32 func_00140f08(void *arg0, s32 arg1) {
    s32 var_v0;

    if (!((M2C_FIELD(arg0, u16 *, 0x30C) == 0xFFFF) || (func_001375f0() == 0) || (var_v0 = 0xB, !(M2C_FIELD(arg0, f32 *, 0x24) < 0.0f)))) {
        return var_v0;
    }
    var_v0 = 0xA;
    if (arg1 == 0) {
        var_v0 = 0;
        if (M2C_FIELD(arg0, f32 *, 0x24) <= 0.0f) {
            var_v0 = 0xA;
        }
    }
    return var_v0;
}

/* func_00140f88 (from auto/text_00140000.c). */
M2C_UNK func_00140db8();
s32 func_00140f88(void) {
    func_00140db8();
    return 0;
}

/* func_00140fa8 (from hand/text_00130000_h7.c). */
void func_0014cc88(W7Ob *o, f32 f);
extern f32 D_002C5970;
void func_00140fa8(W7Ob *o) {
    func_0014cc88(o, 0.0f);
    o->flags &= ~0x400;
    o->x3b0 = 6.0f;
    o->x3b4 -= 8.724489212036133f;
    PlatVu0ScaleVector(o->x3c0, o->x200, D_002C5970);
}

/* func_00141018 (from hand/text_00130000_h7.c). */
typedef struct {
    u8 pad[0xC];
    void (*fn)(W7Ob *);
} W7Ev;
#define func_00130398 ((W7Ev *(*)(W7Ob *o, s32 k, f32 f)) func_00130398)
#define func_00130578 ((W7Ev *(*)(W7Ob *o, s32 k, f32 f)) func_00130578)
void func_00141018(W7Ob *o) {
    func_00130398(o, 0x01000019, 0.0f);
    func_00130578(o, 0x40000006, 0.0f)->fn = func_00140fa8;
}
#undef func_00130398
#undef func_00130578

/* func_00141078 (from hand/text_00130000_h7.c). */
f32 func_001376e8(W7Ob *o, f32 *v);
void func_00137688(W7Ob *o, f32 f);
void func_00141078(W7Ob *o) {
    PlatVu0ScaleVector(o->x20, o->x148, -1.0f);
    o->x20[1] = o->x20[3] = 0.0f;
    func_00137688(o, func_001376e8(o, o->x20));
}

/* func_001410d8 (from hand/text_00130000_h7.c). */
#define func_00130398 ((W7Ev *(*)(W7Ob *o, s32 k, f32 f)) func_00130398)
#define func_00130578 ((W7Ev *(*)(W7Ob *o, s32 k, f32 f)) func_00130578)
void func_001410d8(W7Ob *o) {
    func_00130398(o, 0x01000019, 0.0f);
    func_00130578(o, 0x40000006, 0.0f)->fn = func_00140fa8;
}
#undef func_00130398
#undef func_00130578

/* func_00141138 (from auto/text_00140000_4.c). */
void func_0013fd10();
void func_0013fd20();
void func_0013fd38();
void func_0013fd60();
void func_001406d0();
void func_00140960();
void func_0014f778();
void func_0014f828();
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *);
void func_00141138(void) {
    func_0014f830(9, 0x101, &func_0013fd10, &func_0013fd20, &func_001406d0, NULL, NULL, 0, NULL);
    func_0014f830(0xA, 0x101, &func_0013fd38, &func_0013fd60, &func_00140960, &func_00140ee0, &func_00140f08, 0, &func_00140f88);
    func_0014f830(0xB, 0x101, &func_00141018, NULL, &func_00141078, &func_0014f778, &func_0014f828, 0, NULL);
}

