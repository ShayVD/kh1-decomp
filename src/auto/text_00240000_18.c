/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00668E20;
extern volatile M2C_UNK D_0045FAC0;
void func_00237018(s32, s32, s32);
void func_002370c8(s32);
void func_002470d0(s32);

s32 func_00247190(void) {
  s8 *new_var;
  s8 *var_a0;
  s8 *var_s0;
  func_002370c8((s32) (&D_00668E20));
  new_var = (s8 *) (&D_00668E20);
  *((s64 *) (new_var + 0xE0)) = 5;
  *((s64 *) (new_var + 0x60)) = 0x30003;
  *((s64 *) (new_var + 0x70)) = (s64) ((((s64) 0x80) << 0x20) | 0x48);
  func_00237018((s32) (&D_00668E20), 0x16, 1);
  var_a0 = (var_s0 = &D_0045FAC0);
  do
  {
    var_a0 = var_s0;
    var_s0 += 0x930;
    func_002470d0((s32) var_a0);
  }
  while (((s32) var_s0) < ((s32) (((s8 *) (&D_0045FAC0)) + 0x5BE0)));
  return 0;
}

void func_00249eb8(void *arg0, void *arg1) {
  s32 temp_v0;
  s32 var_v1;
  u8 *var_a1;
  int new_var;
  void *var_a0;
  var_a0 = arg0;
  var_v1 = (new_var = 0);
  new_var = 0x40;
  var_a1 = (arg1 + new_var) + (*((s32 *) (((s8 *) arg1) + 0x18)));
  do
  {
    temp_v0 = var_v1 < 0x20;
    var_v1 += 1;
    if (temp_v0 != 0)
    {
      *((u8 *) (((s8 *) var_a0) + 0)) = (u8) (*var_a1);
    }
    else
    {
      *((u8 *) (((s8 *) var_a0) + 0x20)) = (u8) (*var_a1);
    }
    var_a1 += 1;
    var_a0 += 1;
  }
  while (var_v1 < new_var);
}

void func_0024b008(s32 arg0, s32 *arg1) {
  s32 *var_a2;
  s32 *var_v1;
  s32 temp_v0;
  s32 var_a0;
  s32 var_a3;
  s32 var_a4;
  var_a0 = arg0;
  var_a4 = 0;
  do
  {
 do { var_a2 = var_a0 + 0x20; var_v1 = arg1; var_a3 = 3; loop_2: temp_v0 = *var_v1; var_v1 += 1; var_a3 -= 1; *var_a2 = temp_v0; var_a2 += 1; if (var_a3 >= 0) { goto loop_2; } } while (0);
    var_a4 += 1;
    var_a0 += 0x10;
  }
  while (var_a4 < 4);
}
