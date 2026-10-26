/* gb.x func_00f22360: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 id; u8 name; } Ent;
Ent *func_001bb658(s32);
void func_001bb558(void);
s32 func_001be630(u8);
u8 *func_001efbb8(s32);

void func_00f22360(u8 *d, s32 idx) {
    Ent *e;
    u8 *s;
    *d++ = 98; e = func_001bb658(idx); func_001bb558(); s = func_001efbb8(func_001be630(e->id)); while (*s) *d++ = *s++; *d++ = 99; *d++ = 1; s = func_001efbb8(e->name + 1); while (*s) *d++ = *s++; *d = 0;
}
