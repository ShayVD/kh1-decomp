/* The model renderer's draw side, default flags (docs/modules.md
 * "Session 52"): the small entry points (func_00162058 relocates a model
 * through func_00161a08, func_00162070, func_00162110 ...).  The rest is in
 * mdldraw.nostrict.c and mdldraw.nostrict_nofill.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "common.h"
#include "data/bss_0055.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BBDF8.h"

/* func_00161f80 (from auto/text_00160000_2.c). */
M2C_UNK func_00121eb0(s32);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_0056A0F0;
void func_00161f80(void) {
    s8 *var_s0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 var_s1;

    var_s0 = &D_0056A0F0;
    var_s1 = 0x5F;
    do {
        if (M2C_FIELD(var_s0, s32 *, 0) != 0) {
            func_00121eb0(M2C_FIELD(var_s0, s32 *, 0x154));
            func_00121eb0(M2C_FIELD(var_s0, s32 *, 0x158));
            func_00121eb0(M2C_FIELD(var_s0, s32 *, 0x150));
            temp_a0 = M2C_FIELD(var_s0, s32 *, 0x15C);
            if (temp_a0 != 0) {
                func_00121eb0(temp_a0);
            }
            temp_a0_2 = M2C_FIELD(var_s0, s32 *, 0x160);
            if (temp_a0_2 != 0) {
                func_00121eb0(temp_a0_2);
            }
            temp_a0_3 = M2C_FIELD(var_s0, s32 *, 0x164);
            if (temp_a0_3 != 0) {
                func_00121eb0(temp_a0_3);
            }
            temp_a0_4 = M2C_FIELD(var_s0, s32 *, 0x168);
            if (temp_a0_4 != 0) {
                func_00121eb0(temp_a0_4);
            }
            temp_a0_5 = M2C_FIELD(var_s0, s32 *, 0x16C);
            if (temp_a0_5 != 0) {
                func_00121eb0(temp_a0_5);
            }
            memset(var_s0, 0, 0x190);
        }
        var_s1 -= 1;
        var_s0 += 0x190;
    } while (var_s1 >= 0);
}

/* func_00162058 (from auto/text_00160000.c). */
M2C_UNK func_00161a08();
void func_00162058(void *h) {
    func_00161a08(h);
}

/* func_00162070 (from auto/text_00160000_2.c). */
M2C_UNK func_00167f68(s32, void *);
s32 func_001617c0();
void func_00162070(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    if (M2C_FIELD(arg0, s32 *, 0) == 0x4A424F4D) {
        *arg3 = func_001617c0(arg0);
        *arg1 = M2C_FIELD(arg0, s32 *, 0x20);
        *arg2 = M2C_FIELD(arg0, s32 *, 0x30);
        func_00167f68(*arg3, arg0);
        return;
    }
    *arg1 = M2C_FIELD(arg0, s32 *, 0x20);
}

/* func_00162110 (from auto/text_00160000_3.c). */
#define memset ((M2C_UNK (*)(void *, M2C_UNK, M2C_UNK)) memset)
void func_00162110(s32 *arg0, void **arg1) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    void *temp_s0;

    if (*arg0 == 0x4A424F4D) {
        temp_s0 = *arg1;
        func_00121eb0(M2C_FIELD(temp_s0, s32 *, 0x154));
        func_00121eb0(M2C_FIELD(temp_s0, s32 *, 0x158));
        func_00121eb0(M2C_FIELD(temp_s0, s32 *, 0x150));
        temp_a0 = M2C_FIELD(temp_s0, s32 *, 0x15C);
        if (temp_a0 != 0) {
            func_00121eb0(temp_a0);
        }
        temp_a0_2 = M2C_FIELD(temp_s0, s32 *, 0x160);
        if (temp_a0_2 != 0) {
            func_00121eb0(temp_a0_2);
        }
        temp_a0_3 = M2C_FIELD(temp_s0, s32 *, 0x164);
        if (temp_a0_3 != 0) {
            func_00121eb0(temp_a0_3);
        }
        temp_a0_4 = M2C_FIELD(temp_s0, s32 *, 0x168);
        if (temp_a0_4 != 0) {
            func_00121eb0(temp_a0_4);
        }
        temp_a0_5 = M2C_FIELD(temp_s0, s32 *, 0x16C);
        if (temp_a0_5 != 0) {
            func_00121eb0(temp_a0_5);
        }
        memset(temp_s0, 0, 0x190);
    }
}
#undef memset

/* func_001621e0 (from auto/text_00160000_5.c). */
M2C_UNK func_001606d0();
void func_001621e0(void *o, s32 m, void *p, void *arg) {
    func_001606d0(o, m, p, arg);
}

/* func_001621f8 (from auto/text_00160000_5.c). */
void func_001621f8(void *arg0) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s64 *, 0x48) = (s64) (M2C_FIELD(arg0, s64 *, 0x48) | 0x20000);
    }
}

/* func_00162338 (from auto/text_00160000.c). */
s16 func_00162338(s16 ***arg0) {
    return ***arg0;
}

/* func_00162348 (from auto/text_00160000.c). */
s32 func_00162348(void ***arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + M2C_FIELD(**arg0, s32 *, 8)), s32 *, 0x10);
}

/* func_00162368 (from auto/text_00160000_1.c). */
s32 func_00162368(void ***arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x30) + M2C_FIELD(**arg0, s32 *, 4)), s32 *, 0x2C) & 0x3FF;
}

/* func_00162390 (from auto/text_00160000_4.c). */
s32 func_00162390(void *arg0) {
    s32 *var_v1;
    s32 var_a0;
    s32 var_v0;

    var_v1 = M2C_FIELD(arg0, s32 **, 0x30);
    var_v0 = 0;
    if (var_v1 != NULL) {
        var_a0 = 0;
        if (*var_v1 != 0) {
            do {
                var_v1 += 1;
                var_a0 += 1;
            } while (*var_v1 != 0);
        }
        var_v0 = var_a0;
    }
    return var_v0;
}

/* func_001623d0 (from auto/text_00160000.c). */
void func_001623d0(void *arg0, s32 *arg1) {
    *arg1 = M2C_FIELD(arg0, s32 *, 0x30);
}

/* func_001623e0 (from auto/text_00160000.c). */
s32 func_001623e0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x154);
}

/* func_001623e8 (from auto/text_00160000.c). */
u32 func_001623e8(void *arg0) {
    return (u32) M2C_FIELD(arg0, u32 *, 0xC) >> 4;
}

/* func_001623f8 (from hand/text_00150000_h10.c). */
typedef struct { s32 a, b, c, d; } V16;
typedef struct { u8 pad[8]; V16 *tbl; } Obj623;
void func_001623f8(Obj623 *o, s32 i, V16 *out) {
    *out = o->tbl[i];
}

/* func_001624f8 (from auto/text_00160000_5.c). */
void func_001624f8(void) {

}

