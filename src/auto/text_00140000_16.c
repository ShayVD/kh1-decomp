/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0014c530();
M2C_UNK func_0014dcd8();
M2C_UNK func_0014f658(void *, M2C_UNK);
M2C_UNK func_002675a8(s32);
extern M2C_UNK func_00147f20;
extern s32 D_00304BE8;
extern s32 D_0054C1B0; /* src/data/bss_0054.c: Ent9c D_0054C1B0[0x3] */
extern u32 D_002C5958;
#include "data/pieces/D_002E27C8.h"
extern volatile s32 D_00532B90; /* src/data/bss_0053.c: Ent32 D_00532B90[128] */
s32 func_00141a40();
s32 func_00147840(s32);
void *func_00147d18(M2C_UNK *);
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

void func_00147f88(void *arg0, f32 fparg0) {
  float new_var;
  void *temp_v0;
  temp_v0 = func_00147d18(&func_00147f20);
  if (temp_v0 != 0)
  {
    *((void **) (((s8 *) temp_v0) + 0x14)) = arg0;
 new_var = 1.0f / fparg0; do { *((s32 *) (((s8 *) temp_v0) + 0x18)) = (s32) (*((s32 *) (((s8 *) arg0) + 0x30))); } while (0);
    *((f32 *) (((s8 *) temp_v0) + 0x1C)) = (f32) new_var;
  }
}

void func_00149968(void) {
  s32 *var_v1;
  s32 var_a0;
  int new_var;
  new_var = ~6;
  var_v1 = &D_0054C1B0;
  var_a0 = 2;
  do
  {
    var_a0 -= 1;
    *var_v1 &= new_var;
    var_v1 += 8;
  }
  while (var_a0 >= 0);
}

s32 func_00149eb8(s32 arg0) {
  s32 temp_a0;
  int new_var;
  temp_a0 = (*((u8 *) (func_00147840(arg0) + 2))) - 2;
  new_var = D_00304BE8 + (temp_a0 * 0x74);
  *((s8 *) (((s8 *) new_var) + 0x36)) = (s8) arg0;
  return temp_a0;
}

s32 func_0014d3c8(void) {
  unsigned long long new_var;
  if ((((u32) D_002C5958) >> 5) & 1)
  {
    func_0014dcd8();
  }
  else
  {
    new_var = (u64) (*(u8 *)&D_002E27C8);
    if ((new_var >> 7) != 0)
    {
      func_0014c530();
    }
  }
  return 0;
}

void func_0014d4f8(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
  f32 *new_var;
  f32 *new_var2;
  func_002675a8(arg0 + 0x3C0);
  *((f32 *) (((s8 *) arg0) + 0x3CC)) = fparg0;
  *((f32 *) (((s8 *) arg0) + 0x3B4)) = fparg1;
  new_var2 = (f32 *) (((s8 *) arg0) + 0x3B8);
  new_var = (s32 *) (((s8 *) arg0) + 0x3B0);
  *new_var = 0;
  new_var = (f32 *) (((s8 *) arg1) + 4);
  *new_var2 = (f32) ((-(*new_var)) / fparg1);
  func_0014f658(arg0, 3);
}

void func_0014f370(void *arg0) {
  s32 new_var;
 do { new_var = func_00141a40(); } while (0);
  *((s32 *) (((s8 *) arg0) + 0x6C)) = new_var;
}
#include "data/pieces/D_002C5958.h"
