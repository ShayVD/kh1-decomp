/* xs_dumbo.x func_00f21010: matched by hand. */
#include "ovl.h"

typedef struct { s32 pad[3]; void (*fC)(void); } T;
void func_00130340(s32, s32, f32);
T *func_00130578(s32, s32, f32);
void func_00f20fd8(void);
void func_00f21010(s32 arg0) {
    func_00130340(arg0, 0x010000CB, 0.0f);
    func_00130578(arg0, 0x40000006, 0.0f)->fC = func_00f20fd8;
}
