/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001f94f0(s32, s32, s32, s32, s32, s32, s32);

s32 func_001fa490(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
  s32 sp0;
  s32 sp4;
  s32 temp_s5;
  s32 temp_s5_2;
  s32 temp_s7;
  s32 temp_s8;
  temp_s5 = arg3 - 1;
  temp_s8 = arg2 - 1;
  sp0 = arg3;
  sp4 = arg6;
  func_001f94f0(arg0, arg1, temp_s8, temp_s5, arg4, arg5, arg7);
  temp_s7 = arg2 + 1;
  func_001f94f0(arg0, arg1, temp_s7, temp_s5, arg4, arg5, arg7);
  temp_s5_2 = sp0 + 1;
  func_001f94f0(arg0, arg1, temp_s8, temp_s5_2, arg4, arg5, arg7);
  func_001f94f0(arg0, arg1, temp_s7, temp_s5_2, arg4, arg5, arg7);
  return func_001f94f0(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
