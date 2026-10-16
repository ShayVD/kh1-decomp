/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

void func_001a8828(M2C_UNK *);

void func_001a67b8(void *arg0, s32 arg1) {
  void *var_v1;
  int new_var;
  new_var = arg1 | 8;
  var_v1 = *((void **) (((s8 *) arg0) + 0x18));
  if (var_v1 != 0)
  {
    do
    {
      *((s32 *) (((s8 *) var_v1) + 0xC)) = 0;
      *((u16 *) (((s8 *) var_v1) + 0x3E)) = (u16) ((*((u16 *) (((s8 *) var_v1) + 0x3E))) | new_var);
      var_v1 = *((void **) (((s8 *) var_v1) + 8));
    }
    while (var_v1 != 0);
  }
}

void func_001a8988(M2C_UNK **arg0, void *arg1) {
  M2C_UNK *new_var;
  M2C_UNK *temp_s0;
  M2C_UNK *var_s1;
  var_s1 = *arg0;
  if (var_s1 != 0)
  {
    do
    {
      temp_s0 = var_s1;
      var_s1 = *var_s1;
      new_var = temp_s0;
      func_001a8828(new_var);
 do { *new_var = *((M2C_UNK **) (((s8 *) arg1) + 4)); } while (0);
      *((M2C_UNK **) (((s8 *) arg1) + 4)) = new_var;
    }
    while (var_s1 != 0);
  }
  *arg0 = 0;
}

void func_001a9418(void *arg0, u16 *arg1, s32 arg2) {
  u16 *var_a1;
  u16 temp_a2;
  unsigned int new_var;
  u16 var_v1;
  var_a1 = arg1;
  var_v1 = 1;
  temp_a2 = arg2 & 0xFFFF;
  *((u16 **) (((s8 *) arg0) + 0)) = var_a1;
  new_var = 1U;
  *((s16 *) (((s8 *) arg0) + 6)) = 0;
  *((u16 *) (((s8 *) arg0) + 4)) = temp_a2;
  if (1)
  {
    if (temp_a2 > new_var)
    {
      do
      {
        *var_a1 = var_v1;
        var_v1 = (var_v1 + 1) & 0xFFFF;
        var_a1 += 1;
      }
      while (var_v1 < temp_a2);
    }
    *var_a1 = -1U;
  }
}

s32 func_001aa0a8(s32 arg0) {
  s32 var_a1;
  s32 var_v1;
  int new_var;
  var_v1 = 1;
  var_a1 = 0;
  new_var = 1;
  if (arg0 > new_var)
  {
    do
    {
      var_v1 *= 2;
      var_a1 += new_var;
    }
    while (var_v1 < arg0);
  }
  return var_a1;
}
