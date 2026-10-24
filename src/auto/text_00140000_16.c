/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0014c530();
M2C_UNK func_0014dcd8();
M2C_UNK func_0014f658(void *, M2C_UNK);
M2C_UNK func_002675a8(s32);
extern u32 D_002C5958;
#include "data/pieces/D_002E27C8.h"
s32 func_00141a40();

s32 func_0014d3c8(void) {
  unsigned long long new_var;
  if ((D_002C5958 >> 5) & 1)
  {
    func_0014dcd8();
  }
  else
  {
    new_var = (u64) (*(u8 *)&D_002E27C8);
    if ((new_var >> 7) != 0)
    {
      func_0014c530();
    }
  }
  return 0;
}

void func_0014d4f8(void *arg0, void *arg1, f32 fparg0, f32 fparg1) {
  f32 *new_var;
  f32 *new_var2;
  func_002675a8(arg0 + 0x3C0);
  *((f32 *) (((s8 *) arg0) + 0x3CC)) = fparg0;
  *((f32 *) (((s8 *) arg0) + 0x3B4)) = fparg1;
  new_var2 = (f32 *) (((s8 *) arg0) + 0x3B8);
  new_var = (s32 *) (((s8 *) arg0) + 0x3B0);
  *new_var = 0;
  new_var = (f32 *) (((s8 *) arg1) + 4);
  *new_var2 = (f32) ((-(*new_var)) / fparg1);
  func_0014f658(arg0, 3);
}

void func_0014f370(void *arg0) {
  s32 new_var;
 do { new_var = func_00141a40(); } while (0);
  *((s32 *) (((s8 *) arg0) + 0x6C)) = new_var;
}
#include "data/pieces/D_002C5958.h"
