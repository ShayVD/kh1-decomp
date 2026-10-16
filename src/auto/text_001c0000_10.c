/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_003C5898;
void func_00131500(s32);

s32 func_001cd208(s32 arg0, s32 arg1) {
  s32 temp_a1;
  (*((M2C_UNK (**)()) (((s32) (&D_003C5898)) + ((s32) (arg1 * 4)))))(temp_a1);
  temp_a1 = arg1 * 4;
  return 2;
}

s32 func_001cf838(void *arg0) {
  void **new_var;
  int new_var2;
  new_var = &arg0;
  new_var2 = ((s32) ((s32) ((s32) (((s64) ((*((s64 *) (((s8 *) (*new_var)) + 0x328))) << 0x19)) >> 0x20)))) & 1;
  if (new_var2 == 1)
  {
    func_00131500(*((s32 *) (((s8 *) arg0) + 4)));
    *((s64 *) (((s8 *) (*new_var)) + 0x328)) = (s64) ((*((s64 *) (((s8 *) arg0) + 0x328))) & (~0x80));
  }
  return 2;
}
