/* dkmovie.x func_00f25010: matched by hand. */
#include "ovl.h"

void func_00f208b8(u8 *);
void func_00f21b98(void);
s32 func_00f21d10(s32);
s32 func_00f235d8(u8 *);
s32 func_00f23620(u8 *);
void func_00f24fe0(s32);
void func_00f27ec8(s32);
extern s32 D_00F28460;
#define FD (*(s32 *)(w + 0x3DD48))

void func_00f25010(u8 *w, s32 a1) {
    s32 r;
    if (w == 0) {
        return;
    }
    func_00f208b8(w);
    if (FD < 0) {
        return;
    }
    if (*(s8 *)(w + 0x3DF52) != 0) {
        while (func_00f235d8(w) != 0) {
            func_00f24fe0(a1);
        }
        func_00f27ec8(FD);
    } else if (*(s8 *)(D_00F28460 + 0x3DF51) != 0) {
        for (;;) {
            r = func_00f23620(w);
            if (r == 0) break;
            if (r != -1) {
                s32 r2;
                func_00f21b98();
                r2 = func_00f21d10(a1);
                if (r2 == 0) break;
                if (r2 == 1) break;
                if (r2 == 10) break;
            }
            func_00f24fe0(a1);
        }
    } else {
        while (func_00f23620(w) != 0) {
            func_00f24fe0(a1);
        }
        func_00f27ec8(FD);
    }
    FD = -1;
}
