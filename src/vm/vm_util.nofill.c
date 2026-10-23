/* The helpers of src/vm/vm_util.c that need nofill (h45 and h21 had them in
 * src/hand/nofill/): the angles from one point to another, and the 3D and
 * flat distances. */
#include "common.h"

typedef struct { f32 x, y, z; } VmVec3;

double sqrt(double);
f32 atan2f(f32, f32);

/* out = (pitch, yaw) from b to a, and r. */
void func_001e9d00(VmVec3 *out, VmVec3 *a, VmVec3 *b, f32 r) {
    f32 d = sqrt((a->z - b->z) * (a->z - b->z) + (a->x - b->x) * (a->x - b->x));
    out->x = atan2f(-(a->y - b->y), d);
    out->y = atan2f(a->x - b->x, a->z - b->z);
    out->z = r;
}

f32 func_001e9e58(VmVec3 *a, VmVec3 *b) {
    f32 dx = a->x - b->x;
    f32 dy = a->y - b->y;
    f32 dz = a->z - b->z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

f32 func_001e9ec0(VmVec3 *a, VmVec3 *b) {
    f32 dx = a->x - b->x;
    f32 dz = a->z - b->z;
    return sqrt(dx * dx + dz * dz);
}
