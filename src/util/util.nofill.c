/* The helper of src/util/util.c that needs nofill: the length of a vector. */
#include "common.h"
#include "platform/math.h"

typedef struct { f32 x, y, z; } V3;

f32 func_001edc50(V3 *v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;
    return PlatSqrtf(x * x + y * y + z * z);
}
