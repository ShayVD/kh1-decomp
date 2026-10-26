/* gb.x func_00f3ff10: the twin of gb.x func_00f3fe80 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[0x10]; s32 v; } Task;
Task *func_0015ed80(s32, void (*)());
void func_00f40078();
void func_00f3ff10(s32 arg0, s32 arg1) {
    Task *t = func_0015ed80(arg0, func_00f40078);
    if (t != NULL) {
        t->v = arg1;
    }
}
