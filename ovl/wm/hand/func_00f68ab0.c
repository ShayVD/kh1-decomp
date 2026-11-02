/* wm.x func_00f68ab0: the twin of gb.x func_00f419b8 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[0x10]; s8 *p; u8 pad2[0x34]; } E48;
s32 func_00f68140();
void func_00f688a0(s32);
extern E48 *D_00FB49E8;

void func_00f68ab0(s32 arg0) {
    if (func_00f68140(arg0) == 0) {
        if (arg0 >= 0) {
            func_00f688a0(arg0);
        }
    } else {
        E48 *e; e = D_00FB49E8 + arg0; *e->p = 1;
    }
}
