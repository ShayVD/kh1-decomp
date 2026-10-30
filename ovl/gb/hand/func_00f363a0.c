/* gb.x func_00f363a0: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad0[8];
    u32 hold;
    u8 padc[4];
    u32 trig;
} GbPad;
void func_001bfac8(void);
GbPad *func_001ba488(s32);
s32 func_001bb720(void);
void func_00f28aa8(void *, s32, s32);
extern u8 D_00F56DC8[];

void func_00f363a0(void) {
    s32 sel = 0;
    s32 top = 0;
    GbPad *p;

    func_001bfac8();
    for (;;) {
        p = func_001ba488(0);
        if (p->hold & 0x4000)
            return;
        if (p->trig & 0x10)
            sel--;
        if (p->trig & 0x40)
            sel++;
        if (sel >= func_001bb720())
            sel = func_001bb720() - 1;
        if (sel < 0)
            sel = 0;
        if (sel - top >= 10)
            top = sel - 9;
        if (sel < top)
            top = sel;
        func_00f28aa8(D_00F56DC8, sel, top);
        func_001bfac8();
    }
}
