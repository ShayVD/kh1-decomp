/* gb.x func_00f2e9e0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x2210]; u64 tex; } World;
typedef struct { u8 pad[0x2C]; s32 x, y; } Tbl;
u64 *func_00f26ca8(u64 *, s32, s32, s32, s32, s32, s32, s32, u64, u64);
u64 *func_00f26fb8(u64 *, s32, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
extern World *D_00F56DC0;
extern u64 *D_00F56DC8;
extern Tbl D_00F61880;
extern u64 D_00F806D0[];

void func_00f2e9e0(void) {
    s32 i, x, y;
    u64 *p;
    u64 **pp = &D_00F56DC8;
    *pp = func_00f3f9d0(*pp); *pp = func_00f26fb8(*pp, 0, 0); y = D_00F61880.y; x = D_00F61880.x; for (i = 0; i < 8; i++, x += 48) { *pp = p = func_00f26ca8(*pp, 90, 30, 0, x, y, 48, 48, D_00F806D0[i], D_00F56DC0->tex); }
    func_00f3fe80(0x2B70, func_00f3f9e8(p));
}
