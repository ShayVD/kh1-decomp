/* gb.x func_00f23e30: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10EC]; u8 n; } W;
extern s32 D_00F56DC0;
void func_00f23e30(s32 arg0) { u8 *p = &((W *)(arg0 + D_00F56DC0))->n; if (*p != 0) (*p)--; }
