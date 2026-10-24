/* The player-controlled object's move: the velocity by state
 * (func_0013e1f8), the motion events of the leader (func_0013eab0,
 * func_0013ee40), the camera-relative move func_0013f198, and the ability
 * records D_0052AE70 (func_0013f2c0). Flag mode: default (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "m2c.h"
#include "data/pieces/D_002C58A0.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_0052.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"

/* func_0013e558 (from auto/text_00130000_9.c). */
M2C_UNK func_001452a0(void *);
extern M2C_UNK D_00350D94;
f32 func_001216d8(f32, f32, f32);
f32 func_00137688(void *, f32);
void func_0013e558(void *arg0) {
    M2C_UNK (*temp_v0)();

    temp_v0 = *(M2C_UNK *)((s8 *)(s8 *)&D_00350D94 + (M2C_FIELD(arg0, s32 *, 0x70) << 5));
    if (temp_v0 != NULL) {
        temp_v0();
    }
    if (M2C_FIELD(arg0, s32 *, 0x70) == 4) {
        PlatVu0CopyVector(arg0 + 0x3C0, ((M2C_UNK *)&D_002C58A0));
        PlatVu0CopyVector(arg0 + 0x20, ((M2C_UNK *)&D_002C58A0));
    }
    func_00137688(arg0, func_001216d8(M2C_FIELD(arg0, f32 *, 0x3C), M2C_FIELD(arg0, f32 *, 0x150), M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), f32 *, 0xCC)));
    if ((M2C_FIELD(arg0, s32 *, 0) & 0x400) && (M2C_FIELD(arg0, s32 *, 0x70) == 2)) {
        PlatVu0ScaleVector(arg0 + 0x3C0, arg0 + 0x20, M2C_FIELD(arg0, f32 *, 0x2C));
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & ~0x800);
    func_001452a0(arg0);
}

/* func_0013ecf8 (from auto/text_00130000_3.c). */
M2C_UNK func_0012ec60(s32, s32);
M2C_UNK func_001376e8(s32, void *);
void func_0013ecf8(s32 arg0, void *arg1, void *arg2) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg1, s32 *, 0);
    if ((temp_v0 != 0) && (temp_v0 != arg0)) {
        func_0012ec60(temp_v0, M2C_FIELD(arg1, s32 *, 4));
        PlatVu0SubVector(arg2, arg2, arg0 + 0x10);
        M2C_FIELD(arg2, s32 *, 4) = 0;
        PlatVu0Normalize(arg2, arg2);
    } else {
        PlatVu0CopyVector(arg2, arg0 + 0x30);
    }
    M2C_FIELD(arg2, s32 *, 0xC) = 0;
    func_001376e8(arg0, arg2);
}

/* func_0013f0c0 (from auto/text_00130000.c). */
M2C_UNK func_0013ed88();
M2C_UNK func_0013ee40(s32, s32, s32);
void func_0013f0c0(s32 arg0, s32 arg1, s32 arg2) {
    func_0013ed88();
    func_0013ee40(arg0, arg1, arg2);
}

/* func_0013f108 (from auto/text_00130000_17.c). */
f32 func_0014cce0(s32, f32);
s32 func_00130340(s32, s32, f32);
s32 func_0014f600(s32);
s32 func_0013f108(s32 arg0) {
  s8 *new_var;
  s32 temp_v0;
  new_var = (s8 *) arg0;
  temp_v0 = *((s32 *) (0x398 + new_var));
  if (temp_v0 != 0)
  {
    if (func_0014f600(temp_v0) != 0)
    {
      if ((*((s32 *) (new_var + 0x70))) == 0)
      {
        func_0014cce0(arg0, 1e+01f);
        PlatVu0CopyVector(arg0 + 0x3C0, (s32) (&D_002C58A0));
        func_00130340(arg0, 0x10006, 8.0f);
        return 1;
        goto block_4;
      }
    }
    return 0;
  }
  block_4:
  return 0;

}

/* func_0013f2c0 (from hand/text_00130000_h7.c). */
void *func_001477c8(void *p);
extern void *D_00304C18[];
extern void *D_0052AE70[];
void func_0013f2c0(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        D_0052AE70[i] = func_001477c8(D_00304C18[i]);
    }
}

/* func_0013f330 (from auto/text_00130000.c). */
s32 func_0013f330(void *arg0, s32 arg1) {
    s32 var_a1;

    var_a1 = arg1;
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x148), f32 *, 0x50) > 25.0f) {
        var_a1 += 9;
    }
    return var_a1;
}

