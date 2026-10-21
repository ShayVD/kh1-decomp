/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00267518(s32, s32, s32);
#include "data/pieces/D_002C5C80.h"
extern volatile M2C_UNK *D_004F6EB8; /* src/data/bss_004F.c: u32 *D_004F6EB8 */
extern volatile M2C_UNK D_004F6DB8;
s32 func_001425d0(s32);
s32 func_00266c08(s32);
void func_00121eb0(s32);
void func_00266f38(s32, s32);

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
  var_v1 = ((M2C_UNK *)&D_002C5C80);
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

s32 func_00127500(s32 arg0) {
  s32 *temp_v0;
  temp_v0 = func_00266c08(1);
  *temp_v0 = ((((*temp_v0) | 1) & (~0xC)) | 4) & (~0x30);
  *temp_v0 = (*temp_v0) & (~0x40);
  func_00266f38((s32) temp_v0, *((s32 *) (((s8 *) arg0) + 0x10)));
  func_00121eb0(*((s32 *) (((s8 *) arg0) + 0x10)));
  return 2;
}

void func_0012a240(void *arg0) {
  s32 temp_s0;
  s32 new_var;
  s32 temp_s0_2;
  temp_s0 = *((s32 *) (((s8 *) arg0) + 0));
  new_var = func_001425d0(temp_s0);
  temp_s0_2 = temp_s0 + 0x120;
  if (new_var == 0)
  {
    func_00267518(temp_s0_2, temp_s0_2, *((s32 *) (((s8 *) arg0) + 4)));
  }
}
