/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_003C5898[];
void func_00131500(s32);

s32 func_001cd208(s32 arg0, s32 arg1) {
  s32 temp_a1;
  (*((M2C_UNK (**)()) (((s32) (&D_003C5898)) + ((s32) (arg1 * 4)))))(temp_a1);
  temp_a1 = arg1 * 4;
  return 2;
}

s32 func_001cf838(void *arg0) {
  void **new_var;
  int new_var2;
  new_var = &arg0;
  new_var2 = ((s32) ((s32) ((s32) (((s64) ((*((s64 *) (((s8 *) (*new_var)) + 0x328))) << 0x19)) >> 0x20)))) & 1;
  if (new_var2 == 1)
  {
    func_00131500(*((s32 *) (((s8 *) arg0) + 4)));
    *((s64 *) (((s8 *) (*new_var)) + 0x328)) = (s64) ((*((s64 *) (((s8 *) arg0) + 0x328))) & (~0x80));
  }
  return 2;
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_001cce38();
void func_001cce70();
void func_001ccea8();
void func_001ccec8();
void func_001ccf00();
void func_001ccf40();
void func_001ccf80();
void func_001ccfb8();
void func_001ccff0();
void func_001cd028();
void func_001cd060();
void func_001cd098();
void func_001cd0d0();
void func_001cd108();
void func_001cd140();
void func_001cd178();
void func_001cd198();
void func_001cd1d0();
M2C_UNK D_003C5898[0x12] ALIGNED(8) = {
    (s32)func_001cce38, (s32)func_001cce70, (s32)func_001ccec8, (s32)func_001ccf00,
    (s32)func_001ccf40, (s32)func_001ccea8, (s32)func_001ccf80, (s32)func_001ccfb8,
    (s32)func_001ccff0, (s32)func_001cd028, (s32)func_001cd060, (s32)func_001cd098,
    (s32)func_001cd0d0, (s32)func_001cd108, (s32)func_001cd140, (s32)func_001cd178,
    (s32)func_001cd198, (s32)func_001cd1d0,
};
