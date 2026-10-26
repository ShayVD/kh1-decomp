/* wm.x func_00f49458: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 a; u8 b; } R49;
R49 *func_001bb658(s32);
void func_001bb558(void);
s32 func_001be630(s32);
u8 *func_001efbb8(s32);

void func_00f49458(u8 *d, s32 id) {
    R49 *r;
    u8 *s;
    *d++ = 'b';
    r = func_001bb658(id);
    func_001bb558();
    s = func_001efbb8(func_001be630(r->a));
    while (*s != 0) {
        *d++ = *s++;
    }
    *d++ = 'c';
    *d++ = 1;
    s = func_001efbb8(r->b + 1);
    while (*s != 0) {
        *d++ = *s++;
    }
    *d = 0;
}
