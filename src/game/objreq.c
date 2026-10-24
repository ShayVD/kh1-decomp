/* Load and spawn requests: the 128 load records D_00531B70 and the load task
 * list D_00531F70 (func_00146a68 queues a file and calls back when it is
 * in), the busy flags D_00532B80 / D_00532B90, and the effect entries
 * spawned by id with their sound (func_00146bd0, func_001473a8,
 * func_00146ff0). Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "m2c.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002E27C8.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "data/bss_0053.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_00304C70.h"

/* func_001467e8 (from auto/text_00140000_16.c). */
extern volatile s32 D_00532B90;
void func_00146778(s32 *, M2C_UNK);
void func_001467e8(s32 arg0) {
  s32 *var_s0;
  u32 var_s1;
  s32 var_s1_2;
  var_s0 = &D_00532B90;
  if (arg0 != 0)
  {
    var_s1 = 0;
    do
    {
      if ((*var_s0) & 1)
      {
        func_00146778(var_s0, 1);
      }
      var_s1 += 1;
      var_s0 += 8;
    }
    while ((var_s1_2 = var_s1) < 0x80);
    return;
  }
  var_s1_2 = 0x7F;
  do
  {
    if ((*var_s0) & 1)
    {
      func_00146778(var_s0, 0);
    }
    var_s1_2 -= 1;
    var_s0 += 8;
  }
  while (var_s1_2 >= 0);
}

/* func_00146878 (from auto/text_00140000.c). */
extern s32 D_00532B80;
s32 func_001ecfd8(M2C_UNK);
s32 func_00146878(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_00532B80 == 0) {
        var_a0 = func_001ecfd8(0) == 0;
    }
    return var_a0;
}

/* func_001468b0 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[0x38]; void (*x38)(void); } W8X38;
#define func_001ecfd8 ((s32 (*)(void *)) func_001ecfd8)
s32 func_001468b0(W8X38 *a) {
    if (!func_001ecfd8(a)) {
        if (a->x38) a->x38();
        return 4;
    }
    return 8;
}
#undef func_001ecfd8

/* func_001468f8 (from auto/text_00140000_10.c). */
void *func_001208e0(M2C_UNK *);
void func_001468f8(s32 arg0) {
    M2C_FIELD(func_001208e0(&func_001468b0), s32 *, 0x38) = arg0;
}

/* func_00146928 (from auto/text_00140000_4.c). */
M2C_UNK func_001ed128(M2C_UNK, s32);
extern M2C_UNK D_00531B70;
void func_00146928(s32 arg0) {
    s8 *var_v1;
    s32 var_a0;

    func_001ed128(0, arg0);
    func_001ed128(3, arg0);
    var_v1 = &D_00531B70;
    var_a0 = 0x7F;
    do {
        if (M2C_FIELD(var_v1, s32 *, 0) == arg0) {
            M2C_FIELD(var_v1, s32 *, 4) = 0;
        }
        var_a0 -= 1;
        var_v1 += 8;
    } while (var_a0 >= 0);
}

/* func_00146b90 (from hand/text_00140000_h8.c). */
extern u32 D_002C5958;
s32 func_00146a68(s32, s32, s32, s32);
s32 func_00146b90(s32 a, s32 b, s32 c, s32 d) {
    if ((D_002C5958 >> 18) & 1) return 0;
    return func_00146a68(a, b, c, d);
}

/* func_00146fb8 (from hand/text_00140000_h8.c). */
typedef struct {
    union { u64 x; struct { u64 b0:1; u64 b1:1; u64 b2:1; u64 b3:1; u64 f4:1; u64 r:59; } b; struct { u32 w0; s32 x4; } w; } f;
    u16 x8; u16 xa; s32 xc; u8 x10[16];
} W8S78;
W8S78 *func_001473a8(s32 a, s32 b, void *c);
typedef struct { u8 pad[0x34]; s32 x34; } W8Y2;
typedef struct { u8 pad[0x18]; W8Y2 *x18; } W8Y1;
typedef struct { u8 pad[0x14c]; W8Y1 *x14c; } W8Y;
W8S78 *func_00146fb8(W8Y *a, s32 b, s32 c) {
    W8S78 *r = 0;
    if (a->x14c) r = func_001473a8(c + a->x14c->x18->x34, b, (u8 *)a + 16);
    return r;
}

/* func_001471e8 (from hand/text_00140000_h8.c). */
extern W8S78 D_00532B90_001471e8[] __asm__("D_00532B90");
#define D_00532B90 D_00532B90_001471e8
W8S78 *func_001471e8(s32 a, s32 b) {
    s32 i;
    for (i = 0; i < 128; i++) {
        if ((D_00532B90[i].f.w.w0 & 1) && D_00532B90[i].x8 == a && D_00532B90[i].f.w.x4 == b) return &D_00532B90[i];
    }
    return 0;
}
#undef D_00532B90

/* func_00147240 (from auto/text_00140000_2.c). */
#define func_001471e8 ((s32 (*)()) func_001471e8)
s32 func_00147240(void) {
    return func_001471e8() != 0;
}
#undef func_001471e8

/* func_00147260 (from auto/text_00140000_2.c). */
void func_00147260(s64 *arg0) {
    *arg0 &= ~1;
}

/* func_00147278 (from auto/text_00140000_14.c). */
void func_0011d3c8(s32, s32, s32);
#define func_001471e8 ((s32 (*)(s32, s32)) func_001471e8)
#define func_00147260 ((s32 (*)(s32)) func_00147260)
void func_00147278(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_001471e8(arg0, arg1);
    if (temp_v0 != 0) {
        func_0011d3c8(arg0, arg1, arg2);
        func_00147260(temp_v0);
    }
}
#undef func_001471e8
#undef func_00147260

/* func_00147300 (from auto/text_00140000.c). */
#define func_0011d3c8 ((M2C_UNK (*)(u16, s32, M2C_UNK)) func_0011d3c8)
#define func_00147260 ((M2C_UNK (*)(void *)) func_00147260)
void func_00147300(void *arg0) {
    func_0011d3c8(M2C_FIELD(arg0, u16 *, 8), M2C_FIELD(arg0, s32 *, 4), 0x78);
    func_00147260(arg0);
}
#undef func_0011d3c8
#undef func_00147260

/* func_00147338 (from auto/text_00140000_3.c). */
M2C_UNK func_0011d350(s32, s32);
#define func_00147260 ((M2C_UNK (*)(s32)) func_00147260)
#define func_001471e8 ((s32 (*)()) func_001471e8)
void func_00147338(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_001471e8();
    if (temp_v0 != 0) {
        func_0011d350(arg0, arg1);
        func_00147260(temp_v0);
    }
}
#undef func_00147260
#undef func_001471e8

/* func_001473a8 (from hand/text_00140000_h8.c). */
W8S78 *func_00146bd0(s32, s32);
void func_002675a8(void *, void *);
void func_0011d1e0(s32, s32, void *, s32);
W8S78 *func_001473a8(s32 a, s32 b, void *c) {
    W8S78 *e = func_00146bd0(a, b);
    if (e) {
        func_002675a8(e->x10, c);
        func_0011d1e0(e->x8, e->f.w.x4, e->x10, 0);
    }
    return e;
}

/* func_00147410 (from hand/text_00140000_h8.c). */
#define func_00147240 ((s32 (*)(s32, s32)) func_00147240)
W8S78 *func_00147410(s32 a, s32 b, s32 c) {
    W8S78 *e;
    if (!func_00147240(a, b)) {
        e = func_00146bd0(a, b);
        if (e) {
            func_0011d1e0(e->x8, e->f.w.x4, (u8 *)c + 16, 0);
            e->f.b.b2 = 1;
            e->xc = c;
        }
        return e;
    }
    return 0;
}
#undef func_00147240

