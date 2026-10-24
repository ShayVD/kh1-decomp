/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/pieces/D_002C5C80.h"
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

void func_00122cb8(void) {
  int new_var;
  s8 *var_v1;
  s32 var_a0;
  var_v1 = &D_002C5C80;
  new_var = ~0x10;
  var_a0 = 0x1E;
  do
  {
    var_a0 -= 1;
    *((s32 *) (((s8 *) var_v1) + 4)) = (s32) ((*((s32 *) (((s8 *) var_v1) + 4))) & new_var);
    var_v1 += 0x40;
  }
  while (var_a0 >= 0);
}
