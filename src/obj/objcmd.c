/* Object commands: the 32 command nodes D_00525A40 (func_00133868 queues
 * one), the 32 triples D_00526640 (func_001337e0), the per-frame task
 * func_00133a88 that runs them (func_00134718 resets both and installs the
 * tasks), and a node chain an object drags (func_001342c8). Flag mode:
 * default (the other modes are in the sibling files). Read from the code,
 * not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "data/types/text_00130000_h32.h"
#include "actor.h"
#include "vm/script_vm.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E26A0.h"

/* func_00133738 (from auto/text_00130000_8.c). */
extern M2C_UNK D_00526640;
s32 func_00133738(void) {
    s8 *var_s0;
    s32 temp_a1;
    s32 var_s1;

    var_s0 = &D_00526640;
    var_s1 = 0x1F;
    do {
        temp_a1 = M2C_FIELD(var_s0, s32 *, 0);
        switch (temp_a1) {                          /* irregular */
        case -1:
            break;
        case -2:
            func_001c4808(M2C_FIELD(M2C_FIELD(var_s0, void **, 4), s32 *, 4), M2C_FIELD(var_s0, s32 *, 8));
            break;
        default:
            func_001c48c8(M2C_FIELD(M2C_FIELD(var_s0, void **, 4), s32 *, 4), temp_a1, (s32 *) M2C_FIELD(var_s0, s32 *, 8));
            break;
        }
        var_s1 -= 1;
        M2C_FIELD(var_s0, s32 *, 0) = -1;
        var_s0 += 0xC;
    } while (var_s1 >= 0);
    return 0;
}

/* func_001337e0 (from hand/text_00130000_h6.c). */
typedef struct {
    s32 a;
    s32 b;
    s32 c;
} W6Trip;
extern W6Trip D_00526640_001337e0[] __asm__("D_00526640");
#define D_00526640 D_00526640_001337e0
void func_001337e0(s32 a, s32 b, s32 c) {
    W6Trip *e = D_00526640;
    s32 i;
    for (i = 0; i < 32; i++, e++) {
        if (e->a == -1) {
            e->a = a;
            e->b = b;
            e->c = c;
            break;
        }
    }
}
#undef D_00526640

/* func_00133830 (from auto/text_00130000_4.c). */
s32 func_00123488(s32);
void func_001315c0(s32, s32, s32, f32);
void func_00133830(s32 arg0, s32 arg1) {
    func_001315c0(func_00123488(arg0), 0x8006, arg1, 0.0f);
}

/* func_00133920 (from auto/text_00130000.c). */
void func_00133920(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg1, void **, 0x50);
    temp_v0 = M2C_FIELD(arg1, void **, 0x54);
    if (temp_v1 == NULL) {
        M2C_FIELD(arg0, void **, 0x440) = temp_v0;
    } else {
        M2C_FIELD(temp_v1, void **, 0x54) = temp_v0;
    }
    temp_v0_2 = M2C_FIELD(arg1, void **, 0x54);
    if (temp_v0_2 != NULL) {
        M2C_FIELD(temp_v0_2, s32 *, 0x50) = 0;
    }
    M2C_FIELD(arg1, s32 *, 0) = 0;
}

/* func_00133950 (from auto/text_00130000_4.c). */
#define func_00133920 ((M2C_UNK (*)()) func_00133920)
void func_00133950(s32 arg0, s32 arg1) {
    func_00133920();
    func_001c4788((void *) (arg1 + 0x10));
}
#undef func_00133920

/* func_00133978 (from hand/text_00130000_h6.c). */
typedef struct W6Link {
    u8 pad00[0x10];
    u8 id;
    u8 pad11[0x54 - 0x11];
    struct W6Link *next;
} W6Link;
typedef struct W6Pend {
    u8 pad00[8];
    union {
        u64 bits;
        struct {
            u64 lo : 44;
            u64 cnt : 4;
            u64 hi : 16;
        } f;
    } u;
    u8 pad10[0x30 - 0x10];
    struct W6Pend *next;
} W6Pend;
typedef struct {
    u8 pad000[0x3EC];
    struct W6Pend *pend;
    u8 pad3f0[0x440 - 0x3F0];
    W6Link *links;
} W6Mgr;
#define func_00133920 ((void (*)(W6Mgr *m, W6Link *l)) func_00133920)
void func_00133978(W6Mgr *m, s32 id) {
    W6Link *l;
    for (l = m->links; l != 0; l = l->next) {
        if (l->id == id) {
            func_00133920(m, l);
            break;
        }
    }
}
#undef func_00133920

/* func_001339c0 (from auto/text_00130000_4.c). */
#define func_00133978 ((void (*)(s32, s32)) func_00133978)
void func_001339c0(s32 arg0) {
    func_00133978(arg0, 4);
    func_00133978(arg0, 0x15);
    func_00133978(arg0, 0x16);
}
#undef func_00133978

/* func_00133a00 (from auto/text_00130000.c). */
void func_00133a00(void *arg0) {
    void *var_v0;

    var_v0 = M2C_FIELD(arg0, void **, 0x440);
    if (var_v0 != NULL) {
        do {
            M2C_FIELD(var_v0, s32 *, 0) = 0;
            var_v0 = M2C_FIELD(var_v0, void **, 0x54);
        } while (var_v0 != NULL);
    }
    M2C_FIELD(arg0, void **, 0x440) = NULL;
}

/* func_00133a38 (from auto/text_00130000_13.c). */
void func_00133a38(void *arg0, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = (s32) ((s64) (M2C_FIELD(arg0, s64 *, 0) << 0x18) >> 0x20) & 0xFFFFFF;
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
    if (temp_v0 > 0) {
        M2C_FIELD(arg0, f32 *, 0x14) = (f32) (-fparg0 / (f32) temp_v0);
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) -fparg0;
}

/* func_00134718 (from hand/text_00130000_h32.c). */
typedef struct {
    s32 used;
    u8 pad04[0x60 - 0x4];
} W32Slot;
extern W32Slot D_00525A40[32];
void func_00133a88(void);
s32 func_0011ef38(void (*f)(void));
void func_0011ef10(s32 a, void (*f)(void));
extern W32E12 D_00526640_00134718[32] __asm__("D_00526640");
#define D_00526640 D_00526640_00134718
void func_00134718(void) {
    s32 i;
    for (i = 0; i < 32; i++) D_00525A40[i].used = 0;
    if (func_0011ef38(func_00133a88) == 0) func_0011ef10(0x1387E, func_00133a88);
    for (i = 0; i < 32; i++) D_00526640[i].x0 = -1;
    if (func_0011ef38(func_00133738) == 0) func_0011ef10(0xB798, func_00133738);
}
#undef D_00526640

