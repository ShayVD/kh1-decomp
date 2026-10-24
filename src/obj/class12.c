/* Object class 0x12, default flags (docs/modules.md "Session 52"): the
 * handlers func_0015dbf8 registers in the class table D_00350D88
 * (func_0014f830(0x12, ...): one 32-byte record of a parameter and seven
 * handlers per class) and their helpers. The rest is in class12.nostrict.c.
 * Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002E26A0.h"
#include "actor.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58A0.h"

/* func_0015d5c0 (from auto/text_00150000_2.c). */
void func_0015d5c0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) | 2);
}

/* func_0015d5d0 (from auto/text_00150000_2.c). */
void func_0015d5d0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1CC) = (s32) (M2C_FIELD(arg0, s32 *, 0x1CC) & ~2);
}

/* func_0015d5e8 (from auto/text_00150000_21.c). */
extern f32 D_002BBDFC;
f32 atan2f(f32, f32);
void func_00105a30(M2C_UNK, u16, s32);
void func_0014f658(void *, M2C_UNK);
void func_00267518(void *, void *, void *);
void func_00267560(void *, s32, f32);
void func_0015d5e8(void *arg0) {
    s32 sp[4];
    void *temp_a0;
    void *temp_v0;

    func_00105a30(-1, M2C_FIELD(arg0, u16 *, 0x30E), M2C_FIELD(arg0, void **, 0x148) + 0xC0);
    if (M2C_FIELD(arg0, s32 *, 0x70) != 0x13) {
        func_00267560(sp, M2C_FIELD(arg0, void **, 0x148) + 0xC0, (25.0f - M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), void **, 0x10), f32 *, 0xC)) - 1.5f);
        temp_a0 = arg0 + 0x10;
        func_00267518(temp_a0, temp_a0, sp);
    }
    func_00267560(arg0 + 0x20, M2C_FIELD(arg0, void **, 0x148) + 0xC0, -1.5f / D_002BBDFC);
    temp_v0 = M2C_FIELD(arg0, void **, 0x148);
    M2C_FIELD(arg0, f32 *, 0x150) = atan2f(M2C_FIELD(temp_v0, f32 *, 0xC0), M2C_FIELD(temp_v0, f32 *, 0xC8));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), s32 *, 0xE4) = (s32) M2C_FIELD(arg0, u16 *, 0x30E);
    func_0014f658(arg0, 0x12);
}

/* func_0015d770 (from auto/text_00150000_3.c). */
s32 func_00130398(s32, s32, f32);
s32 func_0015d6c8(s32, s32);
s32 func_0015d770(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = func_0015d6c8(arg0, arg1);
    if (var_v0 != 0) {
        func_00130398(arg0, 0x40000032, 8.0f);
        var_v0 = 1;
    }
    return var_v0;
}

/* func_0015d7b8 (from auto/text_00150000_22.c). */
void func_002675a8(s32, s32);
#define func_0014f658 ((void (*)(s32, s32)) func_0014f658)
void func_0015d7b8(s32 arg0, s32 arg1) {
    func_0014f658(arg0, 0);
    func_002675a8(arg0 + 0x20, M2C_FIELD(arg0, s32 *, 0x148) + 0xC0);
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) (((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), void **, 0x10), f32 *, 0xC) - 25.0f) + 5.0f) / D_002BBDFC);
    func_002675a8(arg1, M2C_FIELD(arg0, s32 *, 0x148) + 0xC0);
}
#undef func_0014f658

/* func_0015da70 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x10]; f32 f10; } Sub6C;
typedef struct { u8 pad[0x6C]; Sub6C *p6C; u8 pad70[0xD8]; u8 *p148; } ObjDA;
typedef struct { u8 pad[4]; union { f32 f; void *p; } f4; } RetDA;
void func_0014cce0(void *, f32);
RetDA *func_0014cb90(void *);
RetDA *func_0015da70(ObjDA *a) {
    RetDA *r = func_0014cb90(a);
    r->f4.f = 4.0f;
    func_0014cce0(a, a->p6C->f10);
    return r;
}

/* func_0015db80 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0xC]; void *cb; } Task;
Task *func_00130578(void *, s32, f32);
void func_0015dac0(void);
#define func_00130398 ((void (*)(void *, s32, f32)) func_00130398)
#define func_0014f658 ((void (*)(void *, s32)) func_0014f658)
void func_0015db80(u32 *a) {
    f32 z = 0.0f;
    *a &= ~0x200010;
    func_00130398(a, 0x1000010, z);
    func_00130578(a, 0x40000032, z)->cb = func_0015dac0;
    func_0014f658(a, 19);
}
#undef func_00130398
#undef func_0014f658

/* func_0015dbf8 (from auto/text_00150000_10.c). */
void func_0014f828();
void func_0015d848();
f32 func_0014f830(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *);
void func_0015dbf8(void) {
    func_0014f830(0x12, 0, &func_0015d5c0, &func_0015d5d0, &func_0015d848, 0, &func_0014f828, 0, &func_0015da70);
}

