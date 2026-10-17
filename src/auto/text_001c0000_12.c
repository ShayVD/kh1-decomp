/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern volatile M2C_UNK D_00629924;

s32 func_001ccdf0(s32 arg0) {
  void *temp_a1;
  temp_a1 = ((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0;
  *((s32 *) (((s8 *) (((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0)) + 0x184)) = (s32) (*((f32 *) (((s8 *) ((s8 *) (&D_00629924))) + ((*((s32 *) (((s8 *) temp_a1) + 0x184))) * 0xB0))));
  return 2;
}
