/* gb.x func_00f40fc8: the twin of wm.x func_00f680c0 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct {
    u8 pad[0x14];
    s32 f14;
    u8 pad2[0x48 - 0x18];
} E;
extern E *D_00F70268;
s32 func_00f40fc8(s32 i) { if (i < 0) return 0; if (D_00F70268[i].f14 & 1) return 1; return 0; }
