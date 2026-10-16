/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_00243168(s32 *, M2C_UNK, s32 *);
M2C_UNK func_00248840(s32, s32, s32, s32, s32);
M2C_UNK func_002488a8(s32, s32, s32, s32, f32);
M2C_UNK func_0024ac08(s32, void *);
M2C_UNK func_0024afc0(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00454A40;
extern M2C_UNK D_00455A10;
extern M2C_UNK D_004569E0;
extern M2C_UNK D_004577D0;
extern M2C_UNK D_00458520;
extern M2C_UNK D_00656230;
extern M2C_UNK func_00243a20;
extern s32 D_006561D0;
s32 func_0011ef38(M2C_UNK *);
void func_0024aac8(M2C_UNK *);

void func_00243a90(void) {
  memset(&D_006561D0, 0, 0x60);
  func_00243168(((s8 *) (&D_006561D0)) + 0x14, 5, ((s8 *) (&D_006561D0)) + 0x24);
  D_006561D0 = 0;
  func_0024aac8(&D_00454A40);
  func_0024aac8(&D_00455A10);
  func_0024aac8(&D_004569E0);
  func_0024aac8(&D_004577D0);
  func_0024afc0(&D_00458520, &D_00656230, &D_00454A40);
  func_0024afc0(&D_00458520, ((s8 *) (&D_00656230)) + 0x24, &D_00455A10);
  func_0024afc0(&D_00458520, ((s8 *) (&D_00656230)) + 0x48, &D_004569E0);
  func_0024afc0(&D_00458520, ((s8 *) (&D_00656230)) + 0x6C, &D_004577D0);
  if (func_0011ef38(&func_00243a20) == 0)
  {
    func_0011ef10(0x29811, &func_00243a20);
    if (1)
    {
    }
  }
}

void func_002489c8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 fparg0) {
  s32 sp[8];
  s32 temp_s7;
  s32 var_a1;
  s32 var_s0;
  s32 var_s1;
  var_s0 = arg1;
  *((s32 *) (((s8 *) sp) + 0x10)) = arg7;
  var_s1 = 6;
  temp_s7 = var_s0;
  do
  {
    var_a1 = var_s0;
    var_s0 += 0xC0;
    var_s1 -= 1;
    func_00248840(arg0, var_a1, arg2, arg4, arg5);
    var_a1 = var_s0;
  }
  while (var_s1 >= 0);
  func_00248840(arg0, var_a1, arg3, arg4, arg5);
  if (arg6 != 0)
  {
    func_0024ac08(temp_s7, sp);
    func_002488a8(arg4 + (*((M2C_UNK *) (((s8 *) sp) + 0x0))), arg5 + (*((M2C_UNK *) (((s8 *) sp) + 0x4))), arg6, *((s32 *) (((s8 *) sp) + 0x10)), fparg0);
  }
}
