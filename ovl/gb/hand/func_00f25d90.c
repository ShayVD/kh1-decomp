/* gb.x func_00f25d90: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x50]; u8 name[32]; } N4c;
N4c *func_001ba9d8(s32);
void func_001bb558(void);
u8 *func_001efbb8(s32);

void func_00f25d90(s32 arg0, s32 arg1) {
    N4c *n = func_001ba9d8(arg0);
    u8 *s;
    s32 i;
    func_001bb558();
    s = func_001efbb8(arg1 + 1);
    for (i = 0; i < 32 && s[i] != 0; i++) {
        n->name[i] = s[i];
    }
    for (; i < 32; i++) {
        n->name[i] = 0;
    }
}
