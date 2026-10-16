/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00108cd0(void *, void *);
extern M2C_UNK D_002AD460;
extern M2C_UNK D_002BC190;
extern M2C_UNK D_004D6B10;
extern M2C_UNK D_004D6B20;
extern M2C_UNK func_00108d90;
extern f32 D_002BBDFC;
extern s32 D_00351BD0;
extern u32 D_002A6208;
extern u64 D_002A6178;
extern volatile char D_00494C00;
extern volatile unsigned char D_002A6C60;
void *func_0015ed80(s32, M2C_UNK *);
void func_00108b60(s32, void *);
void func_00108c58(s32, void *);
void func_00267548(void *, M2C_UNK *, s32);

u32 func_00104388(void *arg0) {
  f32 temp_f2;
  temp_f2 = (*((f32 *) (((s8 *) arg0) + 0x10))) + D_002BBDFC;
  *((f32 *) (((s8 *) arg0) + 0x10)) = temp_f2;
  if ((*((f32 *) (((s8 *) arg0) + 0x18))) <= temp_f2)
  {
    D_002A6208 = 0;
    D_002A6178 = 0xC000;
    D_002A6178 = D_002A6178 << 0x11;
    return 4;
  }
  D_002A6178 = (((s64) ((s32) ((*((f32 *) (((s8 *) arg0) + 0x14))) * temp_f2))) << 0x18) | (((s64) 0x8000) << 0x11);
  return 0;
}

void func_00108618(void) {
  int new_var;
  s32 *var_v0;
  s32 var_v1;
  var_v1 = 0x1F;
  new_var = 0x174;
  var_v0 = (&D_00494C00) + new_var;
  do
  {
    var_v1 -= 1;
    *var_v0 = 0;
    var_v0 -= 3;
  }
  while (var_v1 >= 0);
}

void func_00108df8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
  s32 sp[4];
  s32 temp_s0;
  s32 temp_s1;
  temp_s0 = arg0 * 0xD0;
  func_00267548(sp, &D_002BC190, arg4);
  func_00108b60(arg3, temp_s0 + ((s8 *) (&D_002A6C60)));
  temp_s1 = arg0 * 0x90;
  func_00108c58(arg2, ((D_00351BD0 * 0x2400) + temp_s1) + ((s8 *) (&D_002AD460)));
  func_00108cd0(((D_00351BD0 * 0x2400) + temp_s1) + ((s8 *) (&D_002AD460)), sp);
  *((void **) (((s8 *) func_0015ed80(arg1, &func_00108d90)) + 0x10)) = (void *) ((temp_s0 + (D_00351BD0 * 0x60)) + (&D_002A6C60));
}

void func_0010ced0(void *arg0, s32 arg1) {
  s8 *new_var2;
  s32 temp_f2;
  s8 *new_var;
  s32 var_a1;
  void *var_v1;
  var_a1 = arg1;
  *((s32 *) (((s8 *) arg0) + 0x18)) = 0;
  if (var_a1 > 0)
  {
    var_v1 = (*((s32 *) (((s8 *) arg0) + 0x20))) + 0x10;
    do
    {
      new_var2 = (s8 *) arg0;
      new_var = new_var2 + 0x1C;
      temp_f2 = (s32) (((f32) (*((u16 *) (((s8 *) var_v1) + 0xA)))) + (*((f32 *) new_var)));
      if (!(temp_f2 >= 0))
      {
        *((u16 *) (((s8 *) var_v1) + 0xA)) = 0U;
      }
      else
      {
        *((u16 *) (((s8 *) var_v1) + 0xA)) = temp_f2;
      }
      var_a1 -= 1;
      var_v1 += 0x10;
    }
    while (var_a1 != 0);
  }
}

void *func_0010fce8(s32 arg0, s32 arg1) {
  s8 *new_var;
  void *temp_v0;
  temp_v0 = ((s8 *) (&D_004D6B10)) + (*((M2C_UNK *) (((s8 *) ((s8 *) (&D_004D6B20))) + (arg0 * 8))));
  new_var = ((s8 *) (temp_v0 + (arg1 * 8))) + 0x10;
  return temp_v0 + (*((s32 *) new_var));
}
