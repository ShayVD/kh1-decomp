/* wm.x func_00f63078: the twin of gb.x func_00f3bf80 (tools/ovl/twins.py). */
#include "ovl.h"

f32 func_00f63078(f32 *a, f32 *b) {
    f32 d[3];
    d[0] = a[0] - b[0];
    d[1] = a[1] - b[1];
    d[2] = a[2] - b[2];
    return d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
}
