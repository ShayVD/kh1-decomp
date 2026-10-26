/* gb.x func_00f23928: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 id; } Ent;
Ent *func_001bb658(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);
s32 func_00f23c70(s32);

s32 func_00f23928(s32 cur) {
    s32 best = 10;
    s32 i, n, p, d;
    Ent *e;
    n = func_001bb720() + func_001bb730(); p = 0; for (i = 0; i < n; i++) { e = func_001bb658(p); d = (e->id - cur + 10) % 10; if (cur != e->id && e->id != 0 && d < best) best = d; p = func_00f23c70(p); if (p == 0) break; }
    return (best + cur) % 10;
}
