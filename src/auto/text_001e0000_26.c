/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

s32 func_001efc68(s32 arg0, s32 arg1, s32 arg2) {
  int new_var;
  new_var = arg0 + (arg2 * 2);
  return arg1 + (*((u16 *) (((s8 *) new_var) + (-2))));
}
