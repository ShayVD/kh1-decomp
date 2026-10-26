/* wm.x func_00f4af28: the twin of gb.x func_00f23e30 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[0x10EC]; u8 n; } W;
extern s32 D_00F9B540;
void func_00f4af28(s32 arg0) { u8 *p = &((W *)(arg0 + D_00F9B540))->n; if (*p != 0) (*p)--; }
