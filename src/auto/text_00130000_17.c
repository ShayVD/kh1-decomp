/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "data/bss_0052.h"

M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_0011f090(M2C_UNK *, M2C_UNK, M2C_UNK *);
#include "data/pieces/D_002C58A0.h"
M2C_UNK D_0052A158[0x240] ALIGNED(8);
extern M2C_UNK D_0052AA58; /* src/data/bss_0052.c: u8 D_0052AA58[0x10] */
extern M2C_UNK D_0052ACF0; /* src/data/bss_0052.c: s32 D_0052ACF0[2] */
extern M2C_UNK func_00138130;
extern M2C_UNK func_00138258;
extern M2C_UNK func_00138718;
extern s32 D_0052ACF8;
f32 func_0014cce0(s32, f32);
s32 func_0011ef38(M2C_UNK *);
s32 func_00130070(s32, s32, s32, s32);
s32 func_00130340(s32, s32, f32);
s32 func_001320a8(s32);
s32 func_00148a40(s32, s32);
s32 func_0014f600(s32);
s32 func_001559a8(s32);
s32 func_002675a8(s32, s32);
void func_001149b0(void *);
void func_0011ef10(M2C_UNK, M2C_UNK *);
void func_0015c9f8(void *);
void func_001763f0(void *);

s32 func_00130190(s32 arg0, s32 arg1) {
  s32 var_a2;
  int new_var;
  new_var = arg0 + 0x1D0;
  var_a2 = 0;
  if (((*((s32 *) (((s8 *) arg0) + 0))) & 0x4000) || ((*((s32 *) (((s8 *) arg0) + 0x14C))) == 0))
  {
    var_a2 = 1;
  }
  return func_00130070(new_var, arg1, var_a2, ((s32) ((s32) ((s32) (((u64) (*((u64 *) (((s8 *) arg0) + 0x370)))) >> 0x32)))) & 1);
}

void func_00130210(s32 arg0, s32 arg1) {
  s32 temp_a1;
  s32 temp_v1;
  s8 *new_var;
  new_var = (s8 *) (arg0 + 0x1D0);
  if (!(arg1 & 0x20000000))
  {
    temp_a1 = *((s32 *) (new_var + 8));
    if (temp_a1 != 0)
    {
      temp_v1 = (*((u16 *) (((s8 *) (((arg1 & 0xFFFF) * 4) + temp_a1)) + 2))) & 0xFFF;
      if (temp_v1 > 0)
      {
        func_00148a40(arg0, temp_v1 - 1);
      }
    }
  }
}

void func_00131d68(s32 arg0, s32 arg1) {
  s32 temp_a0;
  s32 temp_v0_2;
  s32 temp_v1;
  void *temp_s0;
  void *temp_v0;
  temp_s0 = func_001320a8(arg0);
 do { temp_v0 = *((void **) (((s8 *) temp_s0) + 8)); } while (0);
  temp_v1 = *((s32 *) (((s8 *) temp_v0) + 4));
  *((s32 *) (((s8 *) arg1) + 4)) = 0;
  *((void **) (((s8 *) arg1) + 0)) = (void *) (temp_v0 + temp_v1);
  *((s32 *) (((s8 *) arg1) + 8)) = func_001559a8(*((s32 *) (((s8 *) temp_s0) + 8)));
  temp_v0_2 = *((s32 *) (((s8 *) temp_s0) + 8));
  temp_a0 = *((s32 *) (((s8 *) temp_v0_2) + 8));
  if (((*((s32 *) (((s8 *) temp_v0_2) + 0xC))) - temp_a0) > 0)
  {
    *((s32 *) (((s8 *) arg1) + 0xC)) = (s32) (temp_v0_2 + temp_a0);
    return;
  }
  *((s32 *) (((s8 *) arg1) + 0xC)) = 0;
}

void func_00132718(void *arg0) {
  s32 temp_v0;
  func_001149b0(arg0 + (*((s32 *) (((s8 *) arg0) + 4))));
  ;
  if (((*((s32 *) (((s8 *) arg0) + 0xC))) - (*((s32 *) (((s8 *) arg0) + 8)))) > 0)
  {
    func_0015c9f8(arg0 + (*((s32 *) (((s8 *) arg0) + 8))));
  }
  if (((*((s32 *) (((s8 *) arg0) + 0x10))) - (*((s32 *) (((s8 *) arg0) + 0xC)))) <= 0)
  {
    return;
  }
  func_001763f0(arg0 + (*((s32 *) (((s8 *) arg0) + 0xC))));
}

s32 func_001375d8(void *arg0) {
  u32 new_var2;
  long new_var3;
  s8 *new_var;
  new_var = (s8 *) arg0;
  new_var2 = (new_var3 = *((u32 *) (new_var + 0x444)));
  return ((new_var2 << 0x20) >> 0x20) & 1;
}

s32 func_00137660(void *arg0) {
  int new_var;
  int new_var2;
  s32 var_v1;
  var_v1 = 0;
  if (!((*((s32 *) (((s8 *) arg0) + 0))) & 4))
  {
    new_var2 = 1;
    new_var = (((u64) (*((u64 *) (((s8 *) arg0) + 0x440)))) >> 0x21) & new_var2;
    var_v1 = new_var == 0;
  }
  return var_v1;
}

void func_00138738(void) {
  *((s32 *) (((s8 *) (&D_0052ACF0)) + 0)) = (*((s32 *) (((s8 *) (&D_0052ACF0)) + 4)) = 0);
  D_0052ACF8 = 0;
  func_0011efa8(&D_0052AA58, &D_0052A158, 0x18, 0x60);
  if (func_0011ef38(&func_00138258) == 0)
  {
    func_0011ef10(0x13880, &func_00138258);
  }
  func_0011f090(&D_0052AA58, 0x3E8, &func_00138718);
  func_0011f090(&D_0052AA58, -0x3E8, &func_00138130);
  func_0011f090(&D_0052AA58, 0x1388, &func_00138130);
  func_0011f090(&D_0052AA58, 0x1F40, &func_00138130);
}

s32 func_0013f108(s32 arg0) {
  s8 *new_var;
  s32 temp_v0;
  new_var = (s8 *) arg0;
  temp_v0 = *((s32 *) (0x398 + new_var));
  if (temp_v0 != 0)
  {
    if (func_0014f600(temp_v0) != 0)
    {
      if ((*((s32 *) (new_var + 0x70))) == 0)
      {
        func_0014cce0(arg0, 1e+01f);
        func_002675a8(arg0 + 0x3C0, (s32) (((M2C_UNK *)&D_002C58A0)));
        func_00130340(arg0, 0x10006, 8.0f);
        return 1;
        goto block_4;
      }
    }
    return 0;
  }
  block_4:
  return 0;

}
