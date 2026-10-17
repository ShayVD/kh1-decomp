/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern int D_003E3D68;
extern volatile u32 D_00641BC4;

void func_00213d00(void) {
  u32 new_var;
  u32 temp_a0;
  new_var = (u32) D_00641BC4;
  temp_a0 = D_003E3D68 - 1;
  if (temp_a0 < new_var)
  {
    D_00641BC4 = temp_a0;
  }
}
