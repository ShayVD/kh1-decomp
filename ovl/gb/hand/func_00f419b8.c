/* gb.x func_00f419b8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; s8 *p; u8 pad2[0x34]; } E48;
s32 func_00f41048();
void func_00f417a8(s32);
extern E48 *D_00F70268;

void func_00f419b8(s32 arg0) {
    if (func_00f41048() == 0) {
        if (arg0 >= 0) {
            func_00f417a8(arg0);
        }
    } else {
        E48 *e; e = D_00F70268 + arg0; *e->p = 1;
    }
}
