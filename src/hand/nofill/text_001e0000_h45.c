#include "common.h"

typedef struct { f32 x, y, z; } Vec3;
double sqrt(double);
f32 atan2f(f32, f32);

/* func_001e98d0 is in src/vm/vm_find.nofill.c. */

void func_001e9d00(Vec3 *out, Vec3 *a, Vec3 *b, f32 r) {
    f32 d = sqrt((a->z - b->z) * (a->z - b->z) + (a->x - b->x) * (a->x - b->x));
    out->x = atan2f(-(a->y - b->y), d);
    out->y = atan2f(a->x - b->x, a->z - b->z);
    out->z = r;
}
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_003C.h"
