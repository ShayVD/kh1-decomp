/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"


void pppRyjMegaPlaceShapeCon(s32 arg0, void *arg1) {
  void *temp_v1;
  s8 *new_var;
  void *temp_a0;
  temp_v1 = *((void **) (((s8 *) arg1) + 0xC));
  temp_a0 = arg0 + (*((s32 *) (((s8 *) temp_v1) + 0)));
  *((s8 *) (((s8 *) (arg0 + (*((s32 *) (((s8 *) temp_v1) + 4))))) + 0xA0)) = 0;
  new_var = ((s8 *) temp_a0) + 0xA0;
  *((s32 *) new_var) = (s32) ((*((s32 *) (((s8 *) temp_a0) + 0xA0))) + 1);
}
