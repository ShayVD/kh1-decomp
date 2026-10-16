/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


f32 func_001beef8(void *arg0, void *arg1) {
  f32 temp_f0;
  f32 new_var[2];
  temp_f0 = (*((f32 *) (0 + ((s8 *) arg0)))) - (*((f32 *) (((s8 *) arg1) + 0)));
  new_var[0] = (*((f32 *) (((s8 *) arg0) + 4))) - (*((f32 *) (((s8 *) arg1) + 4)));
  new_var[1] = (*((f32 *) (((s8 *) arg0) + 8))) - (*((f32 *) (((s8 *) arg1) + 8)));
  return ((temp_f0 * temp_f0) + (new_var[0] * new_var[0])) + (new_var[1] * new_var[1]);
}
