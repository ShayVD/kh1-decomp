/* The scene lights: the light set D_002C5C80 (func_00122c70 / func_00122cb8
 * reset it, func_00122cf0 the per-frame update), func_001226f0 /
 * func_00122768 a light's colour and its release (the ppp light effects use
 * them), the light matrices for a model (func_00122770, func_001229c0),
 * func_00122588 the light vector for an object, func_00122ab0 the room's
 * light file. Flag mode: default (the other modes are in the sibling files).
 * Read from the code, not proved by a boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C5C48.h"
#include "common.h"
#include "data/pieces/D_002C5968.h"
#include "data/types/text_00110000_h53_p.h"
#include "data/types/text_00110000_h53_p2.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/text_00110000_h53.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/types/text_00110000_h4.h"
#include "data/pieces/D_002C5C60.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002BC0A8.h"
#include "actor.h"
#include "data/pieces/D_002C6440.h"

/* func_00122430 (from auto/text_00120000_8.c). */
M2C_UNK func_002674f0(s32, void *, void *, f32);
extern f32 D_002BBDFC;
s32 func_00122430(void *arg0) {
    M2C_UNK (*temp_v0)(s32);
    f32 temp_f0;
    f32 var_f20;
    s32 var_s1;

    var_s1 = 0;
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x44) - D_002BBDFC;
    var_f20 = temp_f0 / M2C_FIELD(arg0, f32 *, 0x40);
    M2C_FIELD(arg0, f32 *, 0x44) = temp_f0;
    if (var_f20 < 0.0f) {
        temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(s32), 0x48);
        var_f20 = 0.0f;
        if (temp_v0 != NULL) {
            temp_v0(M2C_FIELD(arg0, s32 *, 0x10));
        }
        var_s1 = 4;
    }
    func_002674f0(M2C_FIELD(arg0, s32 *, 0x10) + 0x30, arg0 + 0x20, arg0 + 0x30, var_f20);
    return var_s1;
}

/* func_001224c8 (from auto/text_00120000_5.c). */
extern M2C_UNK D_004F6EC0;
s32 func_0011f090(s32, s32, s32);
s32 func_002675a8(s32, s32);
void func_001224c8(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    void *temp_v0;

    if (fparg0 <= 0.0f) {
        func_002675a8(arg0 + 0x30, arg1);
        return;
    }
    temp_v0 = func_0011f090((s32) &D_004F6EC0, 0, (s32) &func_00122430);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
    M2C_FIELD(temp_v0, f32 *, 0x44) = fparg0;
    M2C_FIELD(temp_v0, f32 *, 0x40) = fparg0;
    M2C_FIELD(temp_v0, s32 *, 0x48) = arg2;
    func_002675a8((s32) (temp_v0 + 0x20), arg0 + 0x30);
    func_002675a8((s32) (temp_v0 + 0x30), arg1);
}

/* func_00122588 (from hand/text_00110000_h53.c). */
f32 func_00120bf8(void *);
void func_00267530(V53 *, V53 *, V53 *);
float cosf(float);
extern V53 D_002C5C70;
void func_00267548(V53 *, V53 *, V53 *);
#define func_002674f0 ((void (*)(V53 *, V53 *, V53 *, f32)) func_002674f0)
#define func_002675a8 ((void (*)(V53 *, V53 *)) func_002675a8)
void func_00122588(u8 *o) {
    V53 *acc = (V53 *)(o + 0x430);
    V53 d;
    Light53 *l;
    s32 i;
    u32 mask = 0;
    f32 dist, r;
    func_002675a8(acc, &D_002C5C70);
    l = &D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (l->flags & 0x11) continue;
        switch (l->kind) {
        case 1:
            func_00267548(acc, acc, &l->col);
            break;
        case 2:
            mask |= 1 << i;
            break;
        case 3:
            mask |= 1 << i;
            break;
        case 4:
            mask |= 1 << i;
            break;
        case 5:
            func_00267530(&d, (V53 *)(o + 0x10), &l->pos);
            dist = func_00120bf8(&d);
            r = l->radius;
            if (dist < r) {
                func_002674f0(&d, &l->col, &D_002C5C70, cosf(dist / r * 3.1415928f * 0.5f));
                func_00267548(acc, acc, &d);
            }
            break;
        }
    }
    *(u32 *)(o + 0x420) = mask;
}
#undef func_002674f0
#undef func_002675a8

/* func_001226f0 (from hand/text_00110000_h4.c). */
typedef Vec4_2c5c80 Vec4;
typedef Lt64_2c5c80 Ent40;
#define func_002675a8 ((void (*)(Vec4 *, Vec4 *)) func_002675a8)
Ent40 *func_001226f0(s32 a, s32 b, s32 c) {
    s32 i;
    Ent40 *e = &D_002C5C80;
    for (i = 0; i < 31; i++, e++) {
        if (e->kind == 0) {
            e->kind = a; e->flags = b; e->c = c;
            func_002675a8(&e->col, &D_002C5C60);
            return e;
        }
    }
    return 0;
}
#undef func_002675a8

/* func_00122768 (from auto/text_00120000.c). */
void func_00122768(s32 *arg0) {
    *arg0 = 0;
}

/* func_00122770 (from hand/text_00110000_h53.c). */
void func_00267560(void *, void *, f32);
void func_00121fc4(V53 *, V53 *);
void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
f32 func_00267390(f32 *, V53 *);
void func_00122770(u8 *o, V53 *pos, f32 m[4][4]) {
    V53 d;
    Light53 *l;
    s32 i, j, n;
    f32 dot, r;
    n = 0;
    sceVu0CopyMatrix(m, D_002C5910);
    l = &D_002C5C80;
    for (i = 0; i < 31; i++, l++) {
        if (!(*(u32 *)(o + 0x420) & (1 << i))) continue;
        switch (l->kind) {
        case 2:
            for (j = 0; j < 3; j++) m[j][n] = -(&l->dir.x)[j];
            n++;
            break;
        case 3:
            func_00267530(&d, &l->pos, pos);
            func_00121fc4(&d, &d);
            if (d.w < l->radius) {
                func_00267560(&d, &d, cosf(d.w / l->radius * 3.1415928f * 0.5f));
                for (j = 0; j < 3; j++) m[j][n] = ((f32 *)&d)[j];
            }
            n++;
            break;
        case 4:
            func_00267530(&d, &l->pos, pos);
            func_00121fc4(&d, &d);
            dot = -func_00267390(&l->dir.x, &d);
            r = l->radius;
            if (r < dot) {
                func_00267560(&d, &d, (dot - r) / (1.0f - r));
                for (j = 0; j < 3; j++) m[j][n] = ((f32 *)&d)[j];
            }
            n++;
            break;
        }
    }
    m[3][3] = 1.0f;
}

/* func_00122ab0 (from hand/text_00110000_h30.c). */
typedef Lt64_2c5c80 Ent5C80;
extern V4 D_002C6450;
void func_00107e10(Ent5C80 *);
void func_00110e68(f32 *);
#define D_004F6EC0 (*(TPool (*)) &D_004F6EC0)
#define func_00267548 ((void (*)(f32 *, f32 *, f32 *)) func_00267548)
s32 func_00122ab0(void) {
    s32 i;
    Ent5C80 *e;
    func_0011f130(&D_004F6EC0, 0);
    D_002C6450[0] = D_002C6450[1] = D_002C6450[2] = D_002C6450[3] = 1.0f;
    D_002BC0A8.u &= ~0x10;
    e = &D_002C5C80;
    for (i = 0; i < 31; i++, e++) {
        if (e->flags & 0x12) continue;
        if (e->kind != 1) {
            if (e->kind == 3) {
                func_00107e10(e);
                D_002BC0A8.u |= 0x10;
            }
        } else {
            func_00267548(D_002C6450, D_002C6450, &e->col.x);
        }
    }
    D_002C6450[3] = 1.0f;
    func_00110e68(D_002C6450);
    return 0;
}
#undef D_004F6EC0
#undef func_00267548

/* func_00122bd8 (from auto/text_00120000.c). */
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_004F6ED0[0xa0];
void func_00122bd8(void) {
    func_0011efa8(&D_004F6EC0, &D_004F6ED0, 0x50, 8);
}

/* func_00122c08 (from auto/text_00120000_9.c). */
#define func_00122768 ((M2C_UNK (*)(M2C_UNK *)) func_00122768)
#define func_00122bd8 ((M2C_UNK (*)()) func_00122bd8)
void func_00122c08(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_002C5C80;
    var_s1 = 0x1E;
    do {
        if ((M2C_FIELD(var_s0, s32 *, 0) != 0) && (M2C_FIELD(var_s0, s32 *, 4) & 8)) {
            func_00122768(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x40;
    } while (var_s1 >= 0);
    func_00122bd8();
}
#undef func_00122768
#undef func_00122bd8

/* func_00122c70 (from auto/text_00120000_8.c). */
void func_00122c70(void) {
    s8 *var_a0;
    s32 temp_v0;
    s32 var_a1;

    var_a1 = 0x1E;
    var_a0 = &D_002C5C80;
    do {
        if (M2C_FIELD(var_a0, s32 *, 0) != 0) {
            temp_v0 = M2C_FIELD(var_a0, s32 *, 4);
            if (temp_v0 & 8) {
                M2C_FIELD(var_a0, s32 *, 4) = (s32) (temp_v0 | 0x10);
            }
        }
        var_a1 -= 1;
        var_a0 += 0x40;
    } while (var_a1 >= 0);
}

/* func_00122cb8 (from auto/text_00120000_16.c). */
void func_00122cb8(void) {
  int new_var;
  s8 *var_v1;
  s32 var_a0;
  var_v1 = &D_002C5C80;
  new_var = ~0x10;
  var_a0 = 0x1E;
  do
  {
    var_a0 -= 1;
    *((s32 *) (((s8 *) var_v1) + 4)) = (s32) ((*((s32 *) (((s8 *) var_v1) + 4))) & new_var);
    var_v1 += 0x40;
  }
  while (var_a0 >= 0);
}

/* func_00122cf0 (from auto/text_00120000_3.c). */
s32 func_0011ef10(s32, s32);
s32 func_0011ef38(s32);
#define func_001226f0 ((s32 (*)(s32, s32, s32)) func_001226f0)
void func_00122cf0(void) {
    s8 *var_v0;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0x1E;
    var_v0 = &D_002C5C80;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s32 *, 0) = 0;
        M2C_FIELD(var_v0, s32 *, 4) = 0;
        var_v0 += 0x40;
    } while (var_v1 >= 0);
    temp_v0 = func_001226f0(2, 7, 0);
    D_002C6440 = temp_v0;
    M2C_FIELD(temp_v0, s32 *, 0x20) = 0;
    M2C_FIELD(D_002C6440, f32 *, 0x24) = 1.0f;
    M2C_FIELD(D_002C6440, s32 *, 0x28) = 0;
    M2C_FIELD(D_002C6440, f32 *, 0x2C) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x30) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x34) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x38) = 1.0f;
    M2C_FIELD(D_002C6440, f32 *, 0x3C) = 1.0f;
    func_00122bd8();
    if (func_0011ef38((s32) &func_00122ab0) != 0) {
        return;
    }
    func_0011ef10(0xEA60, (s32) &func_00122ab0);
}
#undef func_001226f0

