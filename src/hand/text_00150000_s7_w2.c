/* session 7 w2: func_0015a348 (strict). func_0015ac58 takes the object in a0; passing it fixes the beqzl/alignment layout. */
#include "common.h"

typedef struct {
    u32 w0;
    u8 pad4[0xc];
    f32 pos[4];
    u8 pad20[0x70 - 0x20];
    s32 x70;
    u8 pad74[0x164 - 0x74];
    s32 x164;
    u8 pad168[0x320 - 0x168];
    f32 x320[4];
} A348;
void func_002675a8(f32 *, f32 *);
void func_0015ac58(A348 *);

s32 func_0015a348(A348 *a, s32 f) {
    if (f != 0 || (a->w0 & 0x1000)) {
        if (a->w0 & 0x100) { func_002675a8(a->pos, a->x320); return a->x70; }
        if (a->x164 == 220) func_0015ac58(a);
        return 2;
    }
    return a->x70;
}
