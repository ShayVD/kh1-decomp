/* xs_genie.x func_00f222d0: matched by hand. */
#include "ovl.h"

typedef struct { s32 on; s32 a; s32 b; } Slot12;
typedef struct { s32 x; s32 n; s32 m; Slot12 s[16]; f32 *path; } Path208;
void *memset(void *, s32, u32);

void func_00f222d0(Path208 *arg0, f32 *arg1) {
    s32 n;
    s32 i;
    f32 *p;

    n = 0;
    for (p = arg1; *p != -1.0f; p += 7) {
        n++;
    }
    memset(arg0, 0, 0xD0);
    memset(arg0->s, 0, 0xC0);
    arg0->path = arg1;
    arg0->n = n;
    arg0->m = n;
    for (i = 0; i < n; i++) {
        arg0->s[i].on = 1;
    }
}
