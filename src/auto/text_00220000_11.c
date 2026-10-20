/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0064.h"

M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_001f3110();
M2C_UNK func_0020d530();
M2C_UNK func_00229690(s32);
extern M2C_UNK func_0020d2f8;
extern s32 D_003F34A8;
extern s32 D_003F34C4;
extern s32 D_00643708;
s32 func_0020d030();
void *func_0011ef10(M2C_UNK, M2C_UNK *);

void func_002297a0(unsigned int arg0) {
  s32 temp_v0;
  s32 new_var;
  func_001f3110();
  D_003F34A8 = 2;
  func_0020d530();
  D_00643708 = 0;
  func_0011d768(6);
  new_var = func_0020d030();
  temp_v0 = new_var;
  D_003F34C4 = temp_v0;
  if (temp_v0 != 0)
  {
    func_00229690(temp_v0);
  }
  *((s16 *) (((s8 *) func_0011ef10(0x270FF, &func_0020d2f8)) + 2)) = arg0;
}
#include "data/data_003F.h"
