/* wm.x func_00f26d50: matched by hand. */
#include "ovl.h"

typedef struct { u64 btn; s32 flag; } Pad;
Pad *func_001ba488(s32);
void func_00f29500(s32, s32, s32);
void func_00f28448(s32, s32, s32, s32);
void func_00f26810(s32, s32, s32, s32);
void func_001bfac8(void);
extern s32 D_00F878E8;
extern s32 D_00FBAA68;
s32 func_00f26d50(s32 arg0, s32 arg1) {
    Pad *p;
    s32 hold;
    while (p = func_001ba488(0), D_00F878E8 == 0) {
        if (p->flag & 1) return 4;
        if (p->btn & 0x2000002000000000LL) return 2;
        if (p->btn & 0x8000008000000000LL) return 3;
        hold = ((s32 *)&p->btn)[1] & 0x2000;
        hold = hold != 0;
        func_00f29500(0, 0x3600, D_00FBAA68);
        func_00f28448(0, 0, 0, arg1);
        func_00f26810(0, 0, arg0, hold);
        func_001bfac8();
    }
    return 0;
}
