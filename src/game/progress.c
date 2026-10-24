/* The story progress (a guess at the name), 0x00111288-0x00111b08:
 * D_002BCB60 points at a record of 234 flag bytes and the saved world /
 * room (D_002BC128 / D_002BC130), func_001112b8 clears it, func_00111380 /
 * func_00111510 store the party's positions, func_001119d0 starts a world's
 * event (func_0013c7d8) when its flag is set, func_001117e0 resets the
 * game's systems for a new game. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"
#include "common.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E26A0.h"
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
#include "data/pieces/D_002A6308.h"
#include "data/pieces/D_002A6318.h"
#include "data/pieces/D_002A6324.h"
#include "data/types/text_00100000_s6_na.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/types/text_00110000_h29_p.h"
#include "data/pieces/D_002A6208.h"
#include "data/types/text_00110000_h29_p3.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BBD48.h"
#include "data/types/text_00110000_h29.h"
#include "data/pieces/D_002BCCA0.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/types/text_00110000_h29_p2.h"

/* func_00111288 (from auto/text_00110000_6.c). */
u32 func_00232cc0(M2C_UNK);
void func_00111288(void) {
    D_002BCB60 = (Ctx_2bcb60 *)(func_00232cc0(3));
}

/* func_001112b8 (from hand/text_00100000_h2.c). */
void func_001112b8(void) {
    s32 i;
    func_00111288();
    for (i = 0; i < 234; i++) D_002BCB60->flags[i] = 0;
    D_002BCB60->w40 = 0;
    D_002BCB60->w44 = 0;
    D_002BCB60->w10[0] = 0;
    D_002BCB60->w10[1] = 0;
    D_002BCB60->w10[2] = 0;
    D_002BCB60->w10[3] = 0;
    D_002BCB60->w10[4] = 0;
    D_002BCB60->w10[5] = 0;
    D_002BCB60->w10[6] = 0;
    D_002BCB60->w10[7] = 0;
    D_002BCB60->w10[8] = 0;
    D_002BCB60->w10[9] = 0;
    D_002BCB60->w10[10] = 0;
    D_002BCB60->w10[11] = 0;
    D_002BCB60->w158 = 0;
}

/* func_00111340 (from hand/text_00100000_h2.c). */
typedef struct Actor_11340 { u8 pad[0x10]; f32 x, y, z; u8 pad2[0x20]; f32 w; } Src;
void func_00111340(Src *s, s32 i) {
    (D_002BCB60)->m[i][4] = s->x;
    (D_002BCB60)->m[i][5] = s->y;
    (D_002BCB60)->m[i][6] = s->z;
    (D_002BCB60)->m[i][7] = s->w;
}

/* func_00111380 (from hand/text_00100000_h2.c). */
typedef struct Actor_11380 { u8 pad[0x10]; f32 x, y, z; u8 pad2[0x20]; f32 w; } Src_11380;
void func_00111480(void);
void func_00111380(void) {
    Src_11380 *p;
    func_00111480();
    p = D_002E26A0[0];
    if (p) func_00111340(p, 0);
    p = D_002E26A0[1];
    if (p) func_00111340(p, 1);
    p = D_002E26A0[2];
    if (p) func_00111340(p, 2);
}

/* func_001113f8 (from auto/text_00110000_3.c). */
#define func_00111340 ((M2C_UNK (*)(s32, M2C_UNK)) func_00111340)
void func_001113f8(s32 arg0) {
    f32 temp_f0;
    s32 var_a0;
    void *var_v0;
    void *var_v1;

    if ((*(s32 *)&D_002E26A0) != 0) {
        func_00111340((*(s32 *)&D_002E26A0), 0);
    }
    var_a0 = 1;
    var_v1 = ((s32)D_002BCB60) + 0x2C;
    var_v0 = (arg0 << 6) + ((s32)D_002BCDA0) + 0x2C;
    do {
        var_a0 -= 1;
        M2C_FIELD(var_v1, f32 *, -0xC) = (f32) M2C_FIELD(var_v0, f32 *, -0xC);
        M2C_FIELD(var_v1, f32 *, -8) = (f32) M2C_FIELD(var_v0, f32 *, -8);
        M2C_FIELD(var_v1, f32 *, -4) = (f32) M2C_FIELD(var_v0, f32 *, -4);
        temp_f0 = M2C_FIELD(var_v0, f32 *, 0);
        var_v0 += 0x10;
        M2C_FIELD(var_v1, f32 *, 0) = temp_f0;
        var_v1 += 0x10;
    } while (var_a0 >= 0);
}
#undef func_00111340

/* func_00111480 (from hand/text_00100000_h2.c). */
typedef V32_2bcb60 V32;
typedef Ctx_2bcb60 Ctx;
extern s32 D_002BCDA8;
extern s32 D_002BC130;
extern s32 D_002BC128;
V32 *func_0017f1c8(void);
void func_00111480(void) {
    Ctx *c = D_002BCB60;
    c->w40 = D_002BC128;
    c->w44 = D_002BC130;
    c->w48 = D_002BCDA8;
    c->blk = *func_0017f1c8();
}

/* func_00111510 (from hand/text_00100000_s6_na.c). */
extern E4 D_002BCB80[];
void func_00111510(void) {
    s32 i;
    E4 *e;
    func_00111480();
    for (i = 0; i < 39; i++) {
        e = &D_002BCB80[i];
        if (D_002BC128 == e->a && D_002BC130 == e->b) {
            func_001113f8(e->c);
            return;
        }
    }
    func_00111380();
}

/* func_00111590 (from auto/text_00110000_3.c). */
void func_00111590(s32 arg0, void *arg1) {
    s32 temp_a0;

    temp_a0 = arg0 * 0x10;
    M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x10);
    M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x14);
    M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x18);
    M2C_FIELD(arg1, f32 *, 0xC) = (f32) M2C_FIELD((temp_a0 + ((s32)D_002BCB60)), f32 *, 0x1C);
}

/* func_001115e0 (from auto/text_00110000.c). */
M2C_UNK func_0017f290(s32);
void func_001115e0(void) {
    func_0017f290(((s32)D_002BCB60) + 0x4C);
}

/* func_00111600 (from auto/text_00110000_6.c). */
extern s8 D_002BCB68;
void func_00111600(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a3;
    s32 var_a5;
    s8 *temp_v0;

    if (arg0 != 0x14) {
        var_a3 = 0;
        var_a5 = 0;
        if (arg0 > 0) {
            do {
                temp_v0 = var_a3 + &D_002BCB68;
                var_a3 += 1;
                var_a5 += *temp_v0;
            } while (var_a3 < arg0);
        }
        M2C_FIELD((var_a5 + arg1 + ((s32)D_002BCB60)), s8 *, 0x6C) = (s8) arg2;
    }
}

/* func_00111660 (from auto/text_00110000_6.c). */
s8 func_00111660(s32 arg0, s32 arg1) {
    s32 var_a2;
    s32 var_a4;
    s8 *temp_v0;

    var_a2 = 0;
    var_a4 = 0;
    if (arg0 > 0) {
        do {
            temp_v0 = var_a2 + &D_002BCB68;
            var_a2 += 1;
            var_a4 += *temp_v0;
        } while (var_a2 < arg0);
    }
    return M2C_FIELD((var_a4 + arg1 + ((s32)D_002BCB60)), s8 *, 0x6C);
}

/* func_001116b0 (from hand/text_00110000_h29.c). */
#define func_00111600 ((void (*)(s32, s32, u8)) func_00111600)
void func_001116b0(s32 id, s32 row) {
    W29Map *m;
    u8 *hdr, *r;
    s32 i;
    if (D_002BBD90[id] == 0) return;
    m = D_002BBD48[id];
    hdr = m->d;
    r = hdr + m->w * (row + 1);
    for (i = 0; i < m->w; i++) {
        if (r[i] != '#') func_00111600(id, hdr[i] - 1, r[i] - 'a');
    }
}
#undef func_00111600

/* func_00111778 (from auto/text_00110000.c). */
#define func_001116b0 ((M2C_UNK (*)(s32, s32)) func_001116b0)
void func_00111778(s32 arg0) {
    func_001116b0(D_002BC128, arg0);
}
#undef func_001116b0

/* func_00111798 (from hand/text_00100000_h2.c). */
s32 func_00111798(void) {
    if (D_002BCB60) return D_002BCB60->w15c;
    return 0;
}

/* func_001117b8 (from auto/text_00110000_1.c). */
void func_001117b8(void) {
    if (D_002BCB60 != NULL) {
        M2C_FIELD(D_002BCB60, s32 *, 0x15C) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x15C) + 1);
    }
}

/* func_001117e0 (from auto/text_00110000.c). */
M2C_UNK func_0013cb98();
M2C_UNK func_0015f108();
M2C_UNK func_001b9ec0();
M2C_UNK func_001eacd0();
M2C_UNK func_001ee4e8();
M2C_UNK func_00232ad0(M2C_UNK);
extern s32 D_002BBE1C;
#define func_001112b8 ((M2C_UNK (*)()) func_001112b8)
void func_001117e0(void) {
    D_002BBE1C = 0;
    func_00232ad0(-1);
    func_001ee4e8();
    func_0015f108();
    func_0013cb98();
    func_001eacd0();
    func_001b9ec0();
    func_001112b8();
}
#undef func_001112b8

/* func_00111830 (from auto/text_00110000_7.c). */
extern s32 D_002BC134;
#define func_00111660 ((s32 (*)(s32, s32)) func_00111660)
void func_00111830(void) {
    s32 temp_a0;
    s32 temp_v0;

    D_002BBE1C = 1;
    temp_a0 = M2C_FIELD(D_002BCB60, s32 *, 0x40);
    D_002BC128 = temp_a0;
    temp_v0 = M2C_FIELD(D_002BCB60, s32 *, 0x44);
    D_002BC130 = temp_v0;
    D_002BC134 = func_00111660(temp_a0, temp_v0);
    D_002BCDA8 = M2C_FIELD(D_002BCB60, s32 *, 0x48);
}
#undef func_00111660

/* func_001118a0 (from auto/text_00110000.c). */
s32 D_004D9248 ALIGNED(8);
void func_001118a0(void) {
    D_004D9248 = 0;
}

/* func_001118b0 (from auto/text_00110000.c). */
void func_001118b0(void) {
    D_004D9248 = 1;
}

/* func_001118c0 (from auto/text_00110000.c). */
M2C_UNK func_00232d60();
void func_001118c0(void) {
    if (D_004D9248 == 0) {
        func_00232d60();
    }
}

/* func_001118f0 (from auto/text_00110000_4.c). */
s32 func_0013c318(M2C_UNK);
void func_001118f0(void) {
    if (func_0013c318(3) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 8);
    }
    if (func_0013c318(5) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x20);
    }
    if (func_0013c318(6) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x40);
    }
    if (func_0013c318(7) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x80);
    }
    if (func_0013c318(8) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x100);
    }
    if (func_0013c318(9) != -1) {
        M2C_FIELD(D_002BCB60, s32 *, 0x158) = (s32) (M2C_FIELD(D_002BCB60, s32 *, 0x158) | 0x200);
    }
}

/* func_001119d0 (from hand/text_00110000_h29.c). */
void func_0013c7d8(s32);
void func_001119d0(void) {
    switch (D_002BC128) {
    case 5:
        if (D_002BCB60->w158 & 0x8) func_0013c7d8(3);
        break;
    case 8:
        if (D_002BCB60->w158 & 0x20) func_0013c7d8(5);
        break;
    case 9:
        if (D_002BCB60->w158 & 0x40) func_0013c7d8(6);
        break;
    case 10:
        if (D_002BCB60->w158 & 0x80) func_0013c7d8(7);
        break;
    case 13:
        if (D_002BCB60->w158 & 0x100) func_0013c7d8(8);
        break;
    case 15:
        if (D_002BCB60->w158 & 0x200) func_0013c7d8(9);
        break;
    }
}

