/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
extern volatile M2C_UNK *D_004F6EB8; /* src/data/bss_004F.c: u32 *D_004F6EB8 */
extern volatile M2C_UNK D_004F6DB8;

void func_00122028(void) {
  volatile M2C_UNK *new_var;
  s8 *new_var2;
  new_var2 = (s8 *) (new_var = &D_004F6DB8);
  *((s32 *) (new_var2 + 4)) = 0x70000000;
  *((s32 *) (0 + ((s8 *) new_var))) = 0x70000000;
  D_004F6EB8 = &D_004F6DB8;
}
