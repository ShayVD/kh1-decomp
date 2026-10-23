#include "common.h"

typedef struct { f32 x, y, z; } V3;

double sqrt(double);

/* func_001e9830 is in src/screen/wave.nofill.c. */

f32 func_001e9e58(V3 *a, V3 *b) {
    f32 dx = a->x - b->x;
    f32 dy = a->y - b->y;
    f32 dz = a->z - b->z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

f32 func_001e9ec0(V3 *a, V3 *b) {
    f32 dx = a->x - b->x;
    f32 dz = a->z - b->z;
    return sqrt(dx * dx + dz * dz);
}
