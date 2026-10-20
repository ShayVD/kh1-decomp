/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00615E68;
extern void *D_00615E60;
void *func_00182588(void *, s32, M2C_UNK);
void func_00267328(s32, void *, s32);
void func_00267620(void *);
void memset(s32, s32, s32);

void func_00181f50(s32 arg0) {
  memset(arg0, 0, 0xC0);
  *((s32 *) (((s8 *) arg0) + 0)) = 0;
  *((s16 *) (((s8 *) arg0) + 0x86)) = 9;
  *((f32 *) (((s8 *) arg0) + 0x4C)) = 1.0f;
  *((s32 *) (((s8 *) arg0) + 4)) = 0;
  *((s32 *) (((s8 *) arg0) + 8)) = 0;
  *((f32 *) (((s8 *) arg0) + 0xC)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x20)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x24)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x28)) = 1.0f;
 do { *((f32 *) (((s8 *) arg0) + 0x2C)) = 1.0f; *((s32 *) (((s8 *) arg0) + 0x10)) = 0; *((s32 *) (((s8 *) arg0) + 0x14)) = 0; *((s32 *) (((s8 *) arg0) + 0x18)) = 0; *((s32 *) (((s8 *) arg0) + 0x1C)) = 0; *((f32 *) (((s8 *) arg0) + 0x30)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x34)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x38)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x3C)) = 1.0f; *((f32 *) (((s8 *) arg0) + 0x40)) = 1.0f; } while (0);
  *((f32 *) (((s8 *) arg0) + 0x44)) = 1.0f;
  *((f32 *) (((s8 *) arg0) + 0x48)) = 1.0f;
}

void func_00185000(s32 arg0, void *arg1, unsigned short arg2) {
  s32 temp_v0;
  s32 temp_v0_2;
  void *var_a2;
  temp_v0 = *((s32 *) (((s8 *) arg1) + 0xC));
  if (temp_v0 != (-1))
  {
    var_a2 = 0;
    temp_v0_2 = (*((s32 *) (((s8 *) D_00615E60) + 0x80))) + (temp_v0 * 0x10);
    if (temp_v0_2 != 0)
    {
      var_a2 = func_00182588(D_00615E60, temp_v0_2, 0);
      *((s32 *) (((s8 *) var_a2) + 4)) = arg0;
    }
    *((s16 *) (((s8 *) (var_a2 + (*((s32 *) (((s8 *) arg1) + 0x10))))) + 0xA0)) = (s16) (arg2 & 0xFFFF);
  }
}

void pppChrXSclXYZMatrixFrame(s32 arg0, void *arg1) {
  s32 sp[16];
  f32 new_var;
  f32 temp_f0;
  f32 temp_f0_2;
  f32 *new_var2;
  f32 temp_f2;
  s32 temp_a0;
  func_00267620(sp);
  temp_f0 = *((f32 *) (((s8 *) D_00615E60) + 0x40));
  new_var2 = (f32 *) (((s8 *) sp) + 0x14);
  temp_f2 = *((f32 *) (((s8 *) arg1) + 8));
  ;
  *((f32 *) (((s8 *) sp) + 0x0)) = temp_f0 * (*((f32 *) (((s8 *) arg1) + 4)));
  *((f32 *) (((s8 *) sp) + 0x0)) = temp_f0 + (*((f32 *) (((s8 *) sp) + 0x0)));
  if (temp_f2 < (temp_f0 + (temp_f0 * (*((f32 *) (((s8 *) arg1) + 4))))))
  {
    *((f32 *) (((s8 *) sp) + 0x0)) = temp_f2;
  }
  new_var = *((f32 *) (((s8 *) sp) + 0x0));
  *new_var2 = new_var;
  temp_a0 = D_00615E68 + 0x10;
  *((f32 *) (((s8 *) sp) + 0x28)) = new_var;
  func_00267328(temp_a0, sp, temp_a0);
}
#include "data/bss_0061_mixed.h"
