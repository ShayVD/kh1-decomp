#include "common.h"

typedef struct { u8 pad[848]; } E848;
typedef struct { u8 pad0[0x3034]; s32 f3034; s32 f3038; u8 pad303c[0x130]; s32 f316c; } Big98;
typedef struct { f32 x, y, z; } Vec3;
extern Big98 D_00389C90;
extern E848 D_003C3A70[];
extern E848 D_003A7990[];
extern E848 D_003B4DA0[];
extern E848 D_0038D170[];
extern E848 D_0039A580[];
extern s32 D_003B4D90;
extern s32 D_003C21A0;
extern s32 D_0039A570;
extern s32 D_003A7980;
double sqrt(double);
f32 atan2f(f32, f32);

E848 *func_001e98d0(s32 a, s32 b) {
    if (D_00389C90.f316c) return &D_003C3A70[b];
    if (a == 1) {
        if (!D_00389C90.f3038) {
            if (b < D_003B4D90) return &D_003A7990[b];
        } else {
            if (b < D_003C21A0) return &D_003B4DA0[b];
        }
    } else {
        if (!D_00389C90.f3034) {
            if (b < D_0039A570) return &D_0038D170[b];
        } else {
            if (b < D_003A7980) return &D_0039A580[b];
        }
    }
    return 0;
}

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
