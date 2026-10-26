/* wm.x func_00f65118: matched by hand. */
#include "ovl.h"

typedef struct { u8 a; u8 b; u8 c; u8 d; u8 fix; } AlphaSrc;
u64 func_00f65118(u8 *p) {
    AlphaSrc *s = (AlphaSrc *)(p + 8);
    return (u64)s->a | ((u64)s->b << 2) | ((u64)s->c << 4) | ((u64)s->d << 6) | ((u64)s->fix << 32);
}
