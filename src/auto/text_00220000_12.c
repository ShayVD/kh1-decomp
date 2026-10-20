/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0022bb48(s32);
M2C_UNK func_0022bc80();
extern M2C_UNK D_003F71A0;
extern M2C_UNK func_0022bc28;
s32 func_001f31a8(M2C_UNK *, M2C_UNK);
void *func_0011ef10(M2C_UNK, M2C_UNK *);
void func_001f3110();

void func_0022bcb8(int arg0) {
  s32 temp_v0;
  func_001f3110();
  func_0022bc80();
  temp_v0 = func_001f31a8(&D_003F71A0, 0);
  if (temp_v0 != 0)
  {
    func_0022bb48(temp_v0);
  }
  *((s16 *) (((s8 *) func_0011ef10(0x2BFE7, &func_0022bc28)) + 2)) = arg0;
}
#include "data/data_003F.h"
