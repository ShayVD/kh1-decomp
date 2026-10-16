/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ea10(M2C_UNK *, M2C_UNK *, unsigned long long);
extern M2C_UNK D_003D9FE0;
extern M2C_UNK D_003DABD4;
extern M2C_UNK func_001dbcb8;
extern s64 D_00389C90[];

s32 func_001dbd20(void) {
  D_00389C90[1551] = (s64) (D_00389C90[1551] | 0x100);
  func_0011ea10(&func_001dbcb8, &D_003DABD4, 0x100);
  return 2;
}

void func_001dcad0(s32 arg0, s32 arg1) {
  s32 new_var;
  s32 temp_a1;
  ;
  new_var = temp_a1;
  (*((M2C_UNK (**)()) (((s32) (&D_003D9FE0)) + ((s32) (4 * arg1)))))(new_var);
}
