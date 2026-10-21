/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

#include "data/pieces/D_00304BE8.h"

s32 func_001d3828(s32 arg0) {
  void *temp_a1;
  temp_a1 = ((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0;
  *((s32 *) (((s8 *) (((*((s32 *) (((s8 *) arg0) + 0x180))) * 4) + arg0)) + 0x184)) = (s32) (*((u8 *) (((s8 *) ((*((s32 *) (((s8 *) temp_a1) + 0x184))) + ((s32)D_00304BE8))) + 0x499)));
  return 2;
}
