/* The party members' stats: HP / MP changes clamped to the member's maximum
 * (func_00141468, func_00141540; the empty record D_00304C70), and a
 * member's stats rebuilt from the save data D_00304BE8 with its equipment
 * and abilities (func_00141b10). Flag mode: default (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_00304D64.h"

/* func_00141200 (from auto/text_00140000.c). */
s32 func_00141200(void *arg0, s32 arg1) {
    return ((s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x70) >> arg1) & 1;
}

/* func_00141288 (from hand/text_00130000_h7.c). */
typedef St6C_304c70 W7Lv;
typedef struct {
    u8 pad00[0x6C];
    union {
        W7Lv *p;
        s16 h;
    } x6c;
} W7Pl;
s32 func_00141288(W7Pl *o, s32 n) {
    W7Lv *p;
    s32 t;
    if (n >= 100) {
        return o->x6c.p->x44 >= n / 100;
    }
    p = o->x6c.p;
    t = p->x44;
    return p->xbe + (t * t + t) / 2 * 30 >= n;
}

/* func_001412f8 (from hand/text_00130000_h7.c). */
void func_00141540(W7Pl *o, s32 v);
void func_00141608(W7Pl *o, s32 v);
void func_001412f8(W7Pl *o, s32 n) {
    if (n >= 100) {
        func_00141540(o, -n / 100);
    } else {
        func_00141608(o, -n);
    }
}

/* func_00141720 (from hand/text_00130000_h7.c). */
void func_00141720(W7Pl *o) {
    W7Lv *p = o->x6c.p;
    s32 x, t;
    if (p == 0 || p == &D_00304C70) return;
    x = p->xbe;
    t = p->x44 * 30 + 30;
    if (x >= t) {
        func_00141540(o, 1);
        x -= t;
    }
    p->xbe = x;
    if (p->pc8) {
        p->pc8->x38 = x;
    }
}

/* func_00141858 (from auto/text_00140000_10.c). */
void func_001315c0(s32, s32, s32, f32);
void func_001417a0(s32, s32);
void func_00141858(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_001315c0(arg0, 0x8004, (s32) sp, 0.0f);
    func_001417a0((s32) sp, arg1);
}

/* func_00141898 (from auto/text_00140000.c). */
M2C_UNK func_0013c458(u16);
void func_00141898(void *arg0) {
    func_0013c458(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C));
}

/* func_00141a40 (from hand/text_00130000_h7.c). */
typedef struct {
    u8 pad[0xE4];
} W7Fx;
extern W7Fx D_0052AE98[32];
extern u32 D_0052CB18;
void func_001418b8(W7Fx *p);
W7Fx *func_00141a40(void) {
    W7Fx *p = D_0052AE98;
    s32 i;
    for (i = 0; i < 32; i++, p++) {
        if (!(D_0052CB18 & (1 << i))) {
            D_0052CB18 |= 1 << i;
            func_001418b8(p);
            return p;
        }
    }
    return 0;
}

/* func_00141ab8 (from hand/text_00130000_h7.c). */
void func_00141ab8(W7Fx *p) {
    if (p >= D_0052AE98 && p < D_0052AE98 + 32) {
        D_0052CB18 &= ~(1 << (p - D_0052AE98));
    }
}

/* func_00141e68 (from auto/text_00140000.c). */
M2C_UNK func_00141b10(u16, void *);
void func_00141e68(void *arg0) {
    void *temp_v1;
    void *temp_v1_2;

    func_00141b10(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C), M2C_FIELD(arg0, void **, 0x6C));
    temp_v1 = M2C_FIELD(arg0, void **, 0x6C);
    M2C_FIELD(M2C_FIELD(temp_v1, void **, 0xC8), u8 *, 1) = (u8) M2C_FIELD(temp_v1, u8 *, 0x3C);
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x6C);
    M2C_FIELD(M2C_FIELD(temp_v1_2, void **, 0xC8), u8 *, 3) = (u8) M2C_FIELD(temp_v1_2, u8 *, 0x44);
}

/* func_00141eb8 (from auto/text_00140000_8.c). */
#define func_00141e68 ((M2C_UNK (*)(s32)) func_00141e68)
void func_00141eb8(void) {
    s32 *var_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s0 = ((s32 *)&D_002E26A0);
    var_s1 = 2;
    do {
        temp_v0 = *var_s0;
        var_s0 += 1;
        if (temp_v0 != 0) {
            func_00141e68(temp_v0);
        }
        var_s1 -= 1;
    } while (var_s1 >= 0);
}
#undef func_00141e68

/* func_00142000 (from auto/text_00140000.c). */
M2C_UNK func_001252f8();
M2C_UNK func_001586f0();
M2C_UNK func_0016f7b8();
#define func_00141eb8 ((M2C_UNK (*)()) func_00141eb8)
void func_00142000(void) {
    func_001586f0();
    func_001252f8();
    func_0016f7b8();
    func_00141eb8();
}
#undef func_00141eb8

