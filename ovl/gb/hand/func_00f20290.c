/* gb.x func_00f20290: matched by hand. */
#include "ovl.h"

extern s32 D_00F74200[];
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
void func_00f22620(void);
void func_00f2eb00(void);
void func_00f2a420(void);
void func_00f20290(s32 n) {
    s32 r;
    switch (n) {
    case 10:
        r = func_001c00e8(n, func_00f22620, KH1_Q(0));
        break;
    case 11:
        r = func_001c00e8(n, func_00f2eb00, KH1_Q(0));
        break;
    case 12:
        r = func_001c00e8(n, func_00f2a420, KH1_Q(0));
        break;
    default:
        return;
    }
    D_00F74200[n] = r;
}
