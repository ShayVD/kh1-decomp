/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00102a48(M2C_UNK, M2C_UNK);
extern s32 D_004D9330;

s32 func_00113ee0(void) {
  int *new_var2;
  int new_var;
  new_var2 = &new_var;
  new_var = 4;
  func_00102a48(0x80, 0x20);
  return ((D_004D9330 ^ (*new_var2)) == 0) ? (0) : (4);
}
