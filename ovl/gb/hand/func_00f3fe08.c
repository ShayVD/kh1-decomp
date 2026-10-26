/* gb.x func_00f3fe08: matched by hand. */
#include "ovl.h"

typedef struct { void (*fn)(); s32 arg; u16 next; } Node;
extern u16 D_00F6CA68[];
extern Node D_00F6D268[];
extern s32 D_00F82880;

void func_00f3fe08(s32 pri, void (*fn)(), s32 arg) {
    u16 old;
    s32 n;

    if (pri < 0) pri = 0;
    if (pri >= 1024) pri = 1023;
    n = D_00F82880;
    old = D_00F6CA68[pri];
    D_00F6CA68[pri] = D_00F82880 + 1;
    D_00F6D268[n].fn = fn;
    D_00F6D268[n].next = old;
    D_00F6D268[n].arg = arg;
    D_00F82880 = n + 1;
}
