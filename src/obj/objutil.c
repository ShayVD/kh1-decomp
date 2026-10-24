/* Small object helpers every class uses: func_001375f0 (the object can act),
 * func_00137618, func_00137688 (turn to an angle), func_001376e8,
 * func_001373f8, the collision entry of an object (func_00137450,
 * D_003044D8), and the id lists D_0052ABF0 / D_0052ACF0 (func_001374a8).
 * Flag mode: default (the other modes are in the sibling files). Read from
 * the code, not proved by a boot (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_0052.h"
#include "vm/script_vm.h"
#include "common.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00304B6C.h"

/* func_00137308 (from auto/text_00130000.c). */
void func_00137308(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x98) = arg1;
    M2C_FIELD(arg1, void **, 0x98) = arg0;
}

/* func_00137318 (from auto/text_00130000.c). */
void func_00137318(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x98);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x98) = 0;
    }
    M2C_FIELD(arg0, void **, 0x98) = NULL;
}

/* func_001373f8 (from auto/text_00130000_4.c). */
void func_001373f8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0xC) = fparg0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) | 0x80) & 0xFFEFFFFF);
}

/* func_00137418 (from anon/session1_probes.c). */
typedef struct {
    int flags;
    char pad0[1184];
    float inv;
} S137418;

void func_00137418(S137418 *s, float x)
{
    s->flags |= 0x18;
    s->inv = 1.0f / x;
}

/* func_00137440 (from auto/text_00130000.c). */
void func_00137440(Actor *arg0, s32 arg1) {
    arg0->unk398 = arg1;
}

/* func_00137448 (from auto/text_00130000.c). */
void func_00137448(Actor *arg0) {
    arg0->unk398 = 0;
}

/* func_00137450 (from hand/text_00130000_h6.c). */
extern s32 D_003044D0;
s32 func_00137450(struct Actor *id) {
    s32 i;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].x8 == id) {
            return i;
        }
    }
    return -1;
}

/* func_001374a8 (from hand/text_00130000_h32.c). */
s32 D_0052ABF0[2][32] ALIGNED(16);  /* moved from hand/text_00130000_h32.c (session 53) */
extern s32 D_0052ACF0[2];
void func_001337e0(s32 a, s32 b, s32 c);
void func_001374a8(s32 id) {
    s32 i;
    s32 o;
    for (i = 0; i < D_0052ACF0[D_0052ACF8]; i++) {
        if (D_0052ABF0[D_0052ACF8][i] == id) return;
    }
    D_0052ABF0[D_0052ACF8][D_0052ACF0[D_0052ACF8]++] = id;
    o = D_0052ACF8 ^ 1;
    for (i = 0; i < D_0052ACF0[o]; i++) {
        if (D_0052ABF0[o][i] == id) return;
    }
    func_001337e0(1, id, 0);
}

/* func_001375d8 (from auto/text_00130000_17.c). */
s32 func_001375d8(void *arg0) {
  u32 new_var2;
  long new_var3;
  s8 *new_var;
  new_var = (s8 *) arg0;
  new_var2 = (new_var3 = *((u32 *) (new_var + 0x444)));
  return ((new_var2 << 0x20) >> 0x20) & 1;
}

/* func_001375f0 (from hand/text_00130000_h6.c). */
typedef struct {
    u32 flags;
    u8 pad04[0x2C - 0x4];
    f32 f2c;
    u8 pad30[0x88 - 0x30];
    u32 x88;
} W6Flg;
s32 func_001375f0(W6Flg *f) {
    return !(f->flags & 4) && !(f->x88 & 0x20);
}

/* func_00137618 (from auto/text_00130000.c). */
#define func_001375d8 ((s32 (*)(s32)) func_001375d8)
#define func_001375f0 ((s32 (*)()) func_001375f0)
s32 func_00137618(s32 arg0) {
    s32 var_s1;

    var_s1 = 0;
    if (func_001375f0() != 0) {
        var_s1 = func_001375d8(arg0) == 0;
    }
    return var_s1;
}
#undef func_001375d8
#undef func_001375f0

/* func_00137660 (from auto/text_00130000_17.c). */
s32 func_00137660(void *arg0) {
  int new_var;
  int new_var2;
  s32 var_v1;
  var_v1 = 0;
  if (!((*((s32 *) (((s8 *) arg0) + 0))) & 4))
  {
    new_var2 = 1;
    new_var = (((u64) (*((u64 *) (((s8 *) arg0) + 0x440)))) >> 0x21) & new_var2;
    var_v1 = new_var == 0;
  }
  return var_v1;
}

/* func_00137688 (from auto/text_00130000.c). */
f32 func_0026b6f8(f32);
f32 func_0026b7d0();
void func_00137688(void *arg0, f32 fparg0) {
    f32 temp_f0;

    if (!(((u64) M2C_FIELD(arg0, u64 *, 0x370) >> 0x2C) & 1)) {
        M2C_FIELD(arg0, f32 *, 0x30) = func_0026b7d0();
        M2C_FIELD(arg0, s32 *, 0x34) = 0;
        temp_f0 = func_0026b6f8(fparg0);
        M2C_FIELD(arg0, f32 *, 0x3C) = fparg0;
        M2C_FIELD(arg0, f32 *, 0x38) = temp_f0;
    }
}

/* func_001376e8 (from auto/text_00130000_2.c). */
f32 func_0026b9a8(f32, f32);
f32 func_001376e8(void *arg0, void *arg1) {
    return M2C_FIELD(arg0, f32 *, 0x150) = func_0026b9a8(M2C_FIELD(arg1, f32 *, 0), M2C_FIELD(arg1, f32 *, 8));
}

