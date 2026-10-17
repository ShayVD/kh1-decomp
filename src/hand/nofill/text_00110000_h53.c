#include "common.h"
typedef struct { s16 id; u8 pad[18]; } E7810;
extern E7810 *D_004F7810;
extern u32 *D_00308CDC;
extern f32 D_002E27CC;
extern f32 D_002E27D0;
extern f32 D_004F77F0;
extern f32 D_004F77F4;
f32 cosf(f32);
void *func_001477c8(s32);

void func_00127340(void) {
    D_002E27CC = D_00308CDC[2];
    D_004F77F4 = cosf((f32)(D_00308CDC[0] >> 1) / 180.0f * 3.1415928f);
    D_004F77F0 = cosf((f32)(D_00308CDC[1] >> 1) / 180.0f * 3.1415928f);
    D_002E27D0 = D_00308CDC[3];
    D_004F7810 = func_001477c8(0xa9f0);
}
