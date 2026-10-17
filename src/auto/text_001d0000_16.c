/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00304BE8;

s32 func_001db9f8(s32 arg0) {
  s8 *new_var2;
  s8 *new_var;
  void *temp_a1;
  temp_a1 = ((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0;
  new_var = (s8 *) temp_a1;
  new_var2 = new_var + 0x184;
  *((s32 *) new_var2) = (s32) (*((u16 *) (((s8 *) (((*((s32 *) (((s8 *) temp_a1) + 0x184))) * 2) + D_00304BE8)) + 0x580)));
  return 2;
}
