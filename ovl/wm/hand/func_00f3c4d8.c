/* wm.x func_00f3c4d8: matched by hand. */
#include "ovl.h"

typedef struct { f32 x, y, z; } P3;
s32 func_00f3c4d8(P3 *arg0) {
    if (arg0->z < -10000.0f || arg0->z > 48000.0f) {
        return -1;
    }
    return ((arg0->z - -10000.0f) * 10000.0f) / 58000.0f;
}
