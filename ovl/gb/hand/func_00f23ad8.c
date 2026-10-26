/* gb.x func_00f23ad8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 id; } Ent;
s32 func_001ba3f0(s32);
Ent *func_001bb658(s32);
s32 func_001bb720(void);
s32 func_001bb730(void);

s32 func_00f23ad8(s32 id) {
    s32 i;
    if (id >= 9) { for (i = 0; i < func_001bb730(); i++) { if (func_001ba3f0(i + 128) > 0 && func_001bb658(i + 128)->id == id) return i + 128; } } else { for (i = 0; i < func_001bb720(); i++) { if (i == 49) continue; if (func_001ba3f0(i) > 0 && func_001bb658(i)->id == id) return i; } }
    return 0;
}
