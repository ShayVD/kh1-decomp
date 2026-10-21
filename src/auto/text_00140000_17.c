/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern f32 D_002BBDFC;
f32 func_0014cce0(s32, f32);
s32 func_0014f658(s32, s32);
s32 func_002675a8(s32, s32);

s32 func_0014d7b8(s32 arg0, s32 arg1) {
  f32 temp_f1;
  s32 temp_s0;
  s32 temp_v1;
  temp_f1 = *((f32 *) (((s8 *) arg0) + 0x3B0));
  if (temp_f1 >= 4.0f)
  {
    temp_v1 = *((s32 *) (((s8 *) arg0) + 0x164));
    if ((temp_v1 != 4) && (temp_v1 != 9))
    {
      func_0014f658(arg0, 0);
      *((s32 *) (((s8 *) arg1) + 0xC)) = 0;
    }
    else
    {
      temp_s0 = *((s32 *) (((s8 *) arg0) + 0x3D0));
      func_0014cce0(arg0, *((f32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x6C)))) + 0x10)));
      *((s32 *) (((s8 *) arg0) + 0x3D0)) = temp_s0;
    }
    *((s32 *) (((s8 *) arg0) + 0)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0))) | 0x60000);
  }
  else
  {
    *((f32 *) (((s8 *) arg0) + 0x3B0)) = (f32) (temp_f1 + D_002BBDFC);
 do { *((s32 *) (((s8 *) arg1) + 0xC)) = 0; } while (0);
  }
  return func_002675a8(arg0 + 0x20, arg1);
}
#include "data/pieces/D_002BBDFC.h"
