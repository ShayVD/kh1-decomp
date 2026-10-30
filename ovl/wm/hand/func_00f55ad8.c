/* wm.x func_00f55ad8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x2210]; u64 tex; } World;
typedef struct { u8 pad[0x2C]; s32 x, y; } Tbl;
u64 *func_00f4dda0(u64 *, s32, s32, s32, s32, s32, s32, s32, u64, u64);
u64 *func_00f4e0b0(u64 *, s32, s32);
u64 *func_00f66ac8(u64 *);
u64 *func_00f66ae0(u64 *);
void func_00f66f78(s32, u64 *);
extern World *D_00F9B540;
extern u64 *D_00F9B548;
extern Tbl D_00FA6000;
extern u64 D_0108CE90[];

void func_00f55ad8(void) {
    s32 i, x, y;
    u64 *p;
    u64 **pp = &D_00F9B548;
    *pp = func_00f66ac8(*pp); *pp = func_00f4e0b0(*pp, 0, 0); y = D_00FA6000.y; x = D_00FA6000.x; for (i = 0; i < 8; i++, x += 48) { *pp = p = func_00f4dda0(*pp, 90, 30, 0, x, y, 48, 48, D_0108CE90[i], D_00F9B540->tex); }
    func_00f66f78(0x2B70, func_00f66ae0(p));
}
