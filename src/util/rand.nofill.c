/* The random numbers of src/util/rand.c that need -fno-fill (docs/modules.md
 * "Session 44"): func_00236970(p) steps a caller's 32-bit seed and returns
 * it as a float in [0, 1), func_002369e8(x) does the same with a copy. */
#include "common.h"

f32 func_00236970(u32 *arg0) {
    *arg0 = (u64)*arg0 * 0x41C64E6D + 12345;
    return (f32)*arg0 * 2.3283064365386963e-10f;
}

f32 func_002369e8(u32 arg0) {
    arg0 = (u64)arg0 * 0x41C64E6D + 12345;
    return (f32)arg0 * 2.3283064365386963e-10f;
}
