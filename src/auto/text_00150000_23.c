/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_0014f658(void *, M2C_UNK);
extern void *D_0054F950;
s64 *func_00156628();
void func_00137418(s32, f32);

void func_00151208(s32 arg0) {
  if ((D_0054F950 != 0) && ((*((f32 *) (((s8 *) D_0054F950) + 8))) < (*((f32 *) (((s8 *) arg0) + 0x14)))))
  {
 do { func_00137418(arg0, 12.0f); } while (0);
    *((s32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x144)))) + 4)) = 0;
    *((void **) (((s8 *) arg0) + 0x144)) = 0;
  }
}

void func_00152538(void *arg0) {
  void **new_var;
  void *temp_a0;
  temp_a0 = *((void **) (((s8 *) arg0) + 0x98));
  if (temp_a0 != 0)
  {
 do { if ((*((s32 *) (((s8 *) temp_a0) + 0x70))) == 0x1C) { func_0014f658(temp_a0, 0); } *((s32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x98)))) + 0x98)) = 0; } while (0);
    new_var = (void **) (((s8 *) arg0) + 0x98);
    *new_var = 0;
  }
  *((s32 *) (((s8 *) arg0) + 0)) = (s32) ((*((s32 *) (((s8 *) arg0) + 0))) & (~0x200));
}

void func_001566a8(void) {
  s64 *temp_v0;
  int new_var;
  new_var = 0xFFFEFFFF;
  ;
  *func_00156628() &= new_var;
}
#include "data/bss_0054_mixed.h"
