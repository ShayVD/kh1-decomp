/* Object sounds and voices, default flags (docs/modules.md "Session 52"):
 * the four play slots D_00551670 (func_001575b0 plays a slot through
 * src/sound/snd_rpc.c, func_00157560 / func_00157648 / func_00157668 ...),
 * func_00157090, func_001570d0.  The rest is in objse.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "data/pieces/D_002C5C48.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/bss_0054.h"
#include "data/types/text_00140000_h9_p.h"
#include "data/pieces/D_00350D88.h"
#include "data/types/text_00140000_h9.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_002C58A0.h"

/* func_00157090 (from auto/text_00150000_21.c). */
extern s8 D_00551670;
s32 func_00157090(void) {
    s32 var_a1;
    s32 var_v0;
    s8 *var_a0;
    s8 temp_v1;

    var_a1 = 0;
    var_a0 = &D_00551670;
loop_1:
    temp_v1 = *var_a0;
    var_a0 += 0x14;
    var_v0 = 1;
    if (temp_v1 != 0) {
        return var_v0;
    }
    var_a1 += 1;
    if (var_a1 >= 4) {
        var_v0 = 0;
    } else {
        goto loop_1;
    }
    return var_v0;
}

/* func_001570d0 (from auto/text_00150000_20.c). */
s32 func_0011e248(s32);
s32 func_00146878(void);
s32 func_001ecfd8(void);
void func_00121eb0(s32);
void func_001ed780(s32, s32, s32);
s32 func_001570d0(s32 arg0) {
    M2C_UNK (*temp_v0)();
    s32 temp_a0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x48);
    temp_a0 = M2C_FIELD(temp_s0, s32 *, 0);
    switch (temp_a0) {                              /* irregular */
    case 0:
        if (D_002C5C48 > 0) {
            if ((func_0011e248(0) == 0) && (func_00146878() != 0)) {
                func_001ed780(M2C_FIELD(temp_s0, s32 *, 4), M2C_FIELD(temp_s0, s32 *, 8), D_002C5C48);
                goto block_7;
            }
        } else {
block_7:
            M2C_FIELD(temp_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_s0, s32 *, 0) + 1);
        }
        return 8;
    case 1:
        if (func_001ecfd8() == 0) {
            temp_v0 = M2C_FIELD(temp_s0, M2C_UNK (**)(), 0x10);
            if (temp_v0 != NULL) {
                temp_v0();
            }
            func_00121eb0((s32) temp_s0);
            return 4;
        }
        /* Duplicate return node #15. Try simplifying control flow for better match */
        return 8;
    default:
        return 8;
    }
}

/* func_001573d8 (from auto/text_00150000.c). */
s32 func_001573d8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(M2C_UNK), 0x48)(-1);
    return 4;
}

/* func_001574b0 (from auto/text_00150000_3.c). */
extern M2C_UNK D_00551608;
void func_001574b0(s32 arg0) {
    s8 *var_v1;
    s32 var_a1;

    var_a1 = 2;
    var_v1 = &D_00551608;
    do {
        var_a1 -= 1;
        if (M2C_FIELD(var_v1, s8 *, 0) == arg0) {
            M2C_FIELD(var_v1, u8 *, 1) = (u8) (M2C_FIELD(var_v1, u8 *, 1) & 0xFE);
        }
        var_v1 += 0x22;
    } while (var_a1 >= 0);
}

/* func_001574f0 (from auto/text_00150000_3.c). */
void func_001574f0(void) {
    s8 *var_v1;
    s32 var_a0;

    var_a0 = 2;
    var_v1 = &D_00551608;
    do {
        var_a0 -= 1;
        M2C_FIELD(var_v1, u8 *, 1) = (u8) (M2C_FIELD(var_v1, u8 *, 1) & 0xFE);
        var_v1 += 0x22;
    } while (var_a0 >= 0);
}

/* func_00157528 (from hand/text_00140000_h9.c). */
typedef struct {
    u8 pad0[0x10];
    f32 x10;
    u8 pad14[0xBD - 0x14];
    s8 xbd;
    u8 padbe[0xC4 - 0xBE];
    f32 xc4;
    u8 padc8[0xCC - 0xC8];
    union { f32 f; s32 i; u8 c; } xcc;
} W9Obj6c;
typedef struct {
    u8 pad0[0x100];
    u64 x100;
    u8 pad108[0x130 - 0x108];
    f32 x130[4];
    s32 x140;
} W9Obj148;
typedef struct {
    u8 pad0[0x1C];
    u8 *x1c;
} W9Obj134;
typedef struct {
    u8 pad0[0x120];
    f32 x120[4];
    u8 pad130[0x134 - 0x130];
    W9Obj134 *x134;
} W9Obj98;
typedef union { f32 f; s32 i; void *p; u8 c; } W9U;
typedef union {
    W9U w[0x20];
    u64 d[0x10];
} W9Obj144;
typedef struct Actor_57528 {
    s32 flags;
    s32 x4;
    u8 pad8[0x10 - 8];
    f32 x10[4];
    f32 x20[4];
    f32 x30[4];
    u8 pad40[0x6C - 0x40];
    W9Obj6c *x6c;
    s32 x70;
    u8 pad74[0x8C - 0x74];
    s32 x8c;
    u8 pad90[0x98 - 0x90];
    W9Obj98 *x98;
    u8 pad9c[0xA4 - 0x9C];
    f32 xa4;
    f32 xa8;
    u8 padac[0x120 - 0xAC];
    f32 x120[4];
    u8 pad130[0x144 - 0x130];
    W9Obj144 *x144;
    W9Obj148 *x148;
    u8 pad14c[0x164 - 0x14C];
    W9U x164;
    u8 pad168[0x1CC - 0x168];
    s32 x1cc;
    u8 pad1d0[0x1F0 - 0x1D0];
    f32 x1f0[4];
    u8 pad200[0x370 - 0x200];
    union { u64 x; struct { u64 lo:44; u64 b44:1; u64 hi:19; } b; } x370;
    s32 x378;
    u8 pad37c[0x3B0 - 0x37C];
    f32 x3b0;
    f32 x3b4;
    f32 x3b8;
    f32 x3bc;
    f32 x3c0[4];
    u8 pad3d0[0x45C - 0x3D0];
    f32 x45c;
    u8 pad460[0x470 - 0x460];
    u64 x470;
    u8 pad478[0x490 - 0x478];
    f32 x490[4];
    void *x4a0;
} W9Ent;
typedef struct {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
    u8 pad4[0x10];
} W9Tab20;
extern W9Tab20 D_00551670_00157528[] __asm__("D_00551670");
#define D_00551670 D_00551670_00157528
s32 func_00157528(W9Ent *e) {
    W9Tab20 *q = &D_00551670[e->x6c->xbd];
    if (!q->b0) return -1;
    return q->b3;
}
#undef D_00551670

/* func_00157560 (from hand/text_00150000_h10.c). */
typedef struct { s8 b0, b1, b2, b3; s32 w4; s32 w8; s32 wC; s32 w10; } E551670;
typedef struct { u8 pad[0xBD]; s8 idx; } O6C;
typedef struct { u8 pad[0x6C]; O6C *p6C; } A157560;
extern E551670 D_00551670_00157560[] __asm__("D_00551670");
#define D_00551670 D_00551670_00157560
s32 func_00157560(A157560 *a) {
    E551670 *e = &D_00551670[a->p6C->idx];
    if (e->b0 == 0) return 0;
    return ((s32)e->w4 != (s32)a) ? 1 : 2;
}
#undef D_00551670

/* func_001575b0 (from hand/text_00150000_h10.c). */
void func_001ed828(s32, s32);
void func_001ed6b0(s32);
extern E551670 D_00551670_001575b0[] __asm__("D_00551670");
#define D_00551670 D_00551670_001575b0
void func_001575b0(s32 i) {
    E551670 *e = &D_00551670[i];
    s32 t = e->b0;
    if (t < 5) {
        if (t >= 2) {
            switch (e->b1) {
            case 0:
                func_001ed828(e->b2, e->b3);
                break;
            case 1:
                func_001ed6b0(e->wC);
                break;
            }
        }
    }
    e->b0 = 0;
}
#undef D_00551670

/* func_00157648 (from auto/text_00150000.c). */
#define func_001575b0 ((M2C_UNK (*)(s8)) func_001575b0)
void func_00157648(void *arg0) {
    func_001575b0(M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s8 *, 0xBD));
}
#undef func_001575b0

/* func_00157668 (from auto/text_00150000_21.c). */
void func_00157668(void) {
    s32 var_s0;

    for (var_s0 = 0; var_s0 < 4; var_s0 += 1) {
        func_001575b0(var_s0);
    }
}

/* func_001577a0 (from hand/text_00150000_h10.c). */
typedef struct { u8 pad[0x4A8]; s32 *tbl; } O4A8;
void func_001ece70(s32, s32, s32, s32);
void func_001ecc68(s32, s32, s32, s32);
void func_001576a8(E551670 *);
void func_001577a0(E551670 *e) {
    if (e->b1 == 0) {
        func_001ece70(e->b2, e->b3, 0, 0);
    } else {
        s32 *p = ((O4A8 *)e->w4)->tbl;
        func_001ecc68(e->wC, p[e->b3 + 2] - p[e->b3 + 1], 0, 0);
    }
    func_001576a8(e);
}

/* func_00157910 (from auto/text_00150000_2.c). */
M2C_UNK func_00157818(s32, s32);
#define func_00157560 ((s32 (*)()) func_00157560)
void func_00157910(s32 arg0, s32 arg1, s32 arg2) {
    if (func_00157560(arg0) < arg2) {
        func_00157818(arg0, arg1);
    }
}
#undef func_00157560

/* func_00157978 (from auto/text_00150000_15.c). */
extern u32 D_002C5958;
#define D_00551670 (*(M2C_UNK (*)) &D_00551670)
void func_00157978(s32 arg0, s32 arg1, f32 fparg0) {
    void *temp_v0;

    func_00157648((void *)arg0);
    if (!(((u32) D_002C5958 >> 0x14) & 1)) {
        temp_v0 = (s8 *)&D_00551670 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s8 *, 0xBD) * 0x14);
        M2C_FIELD(temp_v0, s8 *, 0) = 1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg0;
        M2C_FIELD(temp_v0, s8 *, 3) = (s8) arg1;
        M2C_FIELD(temp_v0, f32 *, 8) = fparg0;
    }
}
#undef D_00551670

