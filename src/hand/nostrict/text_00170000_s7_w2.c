/* session 7 w2: func_0017f1c8 (nostrict). Returning the symbol again ('return &D_00575870;' instead of 'return d;') gives the v0/t0 copy and the slot layout. */
#include "common.h"
typedef struct { f32 x, y, z; } V3;
typedef struct { V3 a; V3 b; f32 c; u8 x1c, x1d, x1e; } S870;
typedef struct { u8 pad[0x1c]; u8 x1c; } P1c;
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
extern f32 D_002E27A0;
extern s32 D_002E27A8;
S870 D_00575870 ALIGNED(16);
#include "data/pieces/D_00362434.h"
#include "data/pieces/D_00362438.h"

S870 *func_0017f1c8(void) {
    S870 *d = &D_00575870;
    d->a.x = (*(V3 *)&D_002E2780).x;
    d->a.y = (*(V3 *)&D_002E2780).y;
    d->a.z = (*(V3 *)&D_002E2780).z;
    d->b.x = (*(V3 *)&D_002E2790).x;
    d->b.y = (*(V3 *)&D_002E2790).y;
    d->b.z = (*(V3 *)&D_002E2790).z;
    d->c = D_002E27A0;
    d->x1c = *(u8 *)&D_002E27A8;
    if (D_002E27A8 == 9) {
        if (((P1c *)D_00362434)) {
            d->x1d = ((P1c *)D_00362434)->x1c;
            d->x1e = 0;
        } else if (((P1c *)D_00362438)) {
            d->x1d = ((P1c *)D_00362438)->x1c;
            d->x1e = 1;
        }
    } else {
        d->x1d = 0;
    }
    return &D_00575870;
}
#include "data/data_002E.h"
