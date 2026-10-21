/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_003E3D68.h"
extern volatile u32 D_00642D18; /* src/data/bss_0064.c: s32 D_00642D18 */

void func_002190e8(void) {
  u32 temp_a0;
  u32 new_var;
  temp_a0 = 1;
  new_var = (u32) D_00642D18;
  temp_a0 = D_003E3D68 - temp_a0;
  if (temp_a0 < new_var)
  {
    D_00642D18 = temp_a0;
    if (1)
    {
    }
  }
}
