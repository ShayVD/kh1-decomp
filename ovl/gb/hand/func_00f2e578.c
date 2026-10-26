/* gb.x func_00f2e578: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x2208]; u64 tex; } World;
typedef struct { u8 pad[0x18]; s32 a, b, c, d; } Tbl;
u64 *func_00f26520(u64 *, s32, s32, s32, s32);
u64 *func_00f26688(u64 *, s32, s32, s32, s32, s32, s32);
u64 *func_00f26ca8(u64 *, s32, s32, s32, s32, s32, s32, s32, u64, u64);
u64 *func_00f26fb8(u64 *, s32, s32);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
void func_00f3fe80(s32, u64 *);
extern World *D_00F56DC0;
extern Tbl D_00F61880;

void func_00f2e578(u64 **pp) {
    *pp = func_00f3f9d0(*pp);
    *pp = func_00f26520(*pp, 400, 256, 256, 1);
    *pp = func_00f26fb8(*pp, 0, 0);
    *pp = func_00f26ca8(*pp, 0, 0, 0, D_00F61880.a, D_00F61880.b, D_00F61880.c, D_00F61880.d, 0x3F80000080000000, D_00F56DC0->tex);
    *pp = func_00f26688(*pp, 400, 256, 0, 0, 0, 255);
    func_00f3fe80(0x2B70, func_00f3f9e8(*pp));
}
