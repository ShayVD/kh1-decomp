/* gb.x func_00f40078: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; u32 v; } Task;
void iFlushCache(s32);

s32 func_00f40078(Task *t) {
    u32 v = t->v;
    *(volatile u32 *)0x10009020 = 0;
    *(volatile u32 *)0x10009030 = v & 0x0FFFFFFF;
    *(volatile u32 *)0x1000E010 = 2;
    iFlushCache(0);
    *(volatile u32 *)0x10009000 = 0x145;
    return 2;
}
