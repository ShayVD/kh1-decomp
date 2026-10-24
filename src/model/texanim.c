/* Texture animation data ("TEXA" chunks), default flags
 * (docs/modules.md "Session 52"): func_001684e0 finds a TEXA chunk and the
 * small accessors.  The rest is in texanim.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BBDF8.h"

/* func_001675c0 (from auto/text_00160000_1.c). */
M2C_UNK func_00121eb0(s32);
M2C_UNK func_00164ba8(void *, s32);
void func_001675c0(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x15C);
    if (temp_a0 != 0) {
        func_00121eb0(temp_a0);
    }
    temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x160);
    if (temp_a0_2 != 0) {
        func_00121eb0(temp_a0_2);
    }
    temp_a0_3 = M2C_FIELD(arg0, s32 *, 0x164);
    if (temp_a0_3 != 0) {
        func_00121eb0(temp_a0_3);
    }
    temp_a0_4 = M2C_FIELD(arg0, s32 *, 0x168);
    if (temp_a0_4 != 0) {
        func_00121eb0(temp_a0_4);
    }
    temp_a0_5 = M2C_FIELD(arg0, s32 *, 0x16C);
    if (temp_a0_5 != 0) {
        func_00121eb0(temp_a0_5);
    }
    temp_a1 = M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x15C) = 0;
    M2C_FIELD(arg0, s32 *, 0x160) = 0;
    M2C_FIELD(arg0, s32 *, 0x164) = 0;
    M2C_FIELD(arg0, s32 *, 0x168) = 0;
    M2C_FIELD(arg0, s32 *, 0x16C) = 0;
    if (temp_a1 != 0) {
        func_00164ba8(arg0, temp_a1);
    }
}

/* func_00167678 (from auto/text_00160000_1.c). */
s32 func_00167678(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

/* func_00167680 (from auto/text_00160000.c). */
s32 func_00167680(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

/* func_00167688 (from auto/text_00160000_2.c). */
void func_00167688(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x88) = arg2;
}

/* func_00167698 (from auto/text_00160000.c). */
s32 func_00167698(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (arg0 != NULL) {
        var_v0 = M2C_FIELD(arg0, s32 *, 4);
    }
    return var_v0;
}

/* func_001676b0 (from auto/text_00160000.c). */
void func_001676b0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x90);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 0x94);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(arg0, f32 *, 0x98);
    M2C_FIELD(arg1, f32 *, 0xC) = (f32) M2C_FIELD(arg0, f32 *, 0x9C);
}

/* func_001676d8 (from auto/text_00160000_5.c). */
M2C_UNK func_002675a8(s32, s32);
void func_001676d8(s32 arg0, s32 arg1) {
    func_002675a8(arg1, arg0 + 0xC0);
}

/* func_001677e0 (from hand/text_00150000_h10.c). */
typedef union { s32 w; struct { u16 lo, hi; } h; } Key677;
typedef struct { Key677 k; u8 pad[8]; } Ent677;
typedef struct { u8 pad[0x3C]; Ent677 *tbl; } Obj677;
Ent677 *func_001677e0(Obj677 *o, u32 key) {
    Ent677 *e = o->tbl;
    u32 hi = key >> 16;
    key &= 0xFFFF;
    for (; e->k.w != -1; e++) {
        if (e->k.h.hi == hi && (key == 0xFFFF || e->k.h.lo == key)) return e;
    }
    return 0;
}

/* func_00167f68 (from hand/text_00150000_h10.c). */
s32 func_001684e0(s32);
typedef struct { u8 b0; u8 b1; u8 pad[2]; s32 w4; u8 pad8[8]; s32 w10; } Ent67F;
typedef struct { u8 pad[0x10]; s32 w10; u8 pad14[4]; Ent67F e[4]; } Obj67F;
void func_00167f68(Obj67F *o, s32 a) {
    s32 i;
    o->w10 = func_001684e0(a);
    for (i = 0; i < 4; i++) {
        o->e[i].b1 = 0;
        o->e[i].w4 = 0;
        o->e[i].w10 = 0;
    }
}

/* func_00168318 (from hand/text_00150000_h10.c). */
s32 func_00168318(u32 *p) {
    switch (*p) {
    case 0x4A424F4D:
    case 0x41584554:
    case 0x454E4F42:
    case 0x4E544D4D:
    case 0x4C535255:
    case 0x564E454D:
        return 1;
    }
    return 0;
}

/* func_001684e0 (from auto/text_00160000_2.c). */
s32 func_001681b8(s32, s32);
s32 func_001684e0(s32 arg0) {
    return func_001681b8(arg0, 0x41584554);
}

