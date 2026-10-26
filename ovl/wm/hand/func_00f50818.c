/* wm.x func_00f50818: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f47388(s32);
void func_00f50548(s32);
void func_00f50568(s32);
void func_00f50578(s32);
void func_00f55330(s32);
void func_00f55378(s32);
void func_00f59870(s32, s32, s32, s32, s32);

void func_00f50818(void) {
    /* register pin: gcc otherwise swaps the loop counter and the hoisted divisor (s1/s2) */
    register s32 i asm("s2");
    s32 v;

    func_00f47388(11);
    func_00f47388(12);
    for (i = 0; i < 5; i++) {
        v = (i * 128) / 5;
        func_00f50548(v);
        func_00f50568(v);
        func_00f50578(v);
        func_00f55330(v);
        func_00f55378(v);
        func_00f59870(-1, 0x80, 0x80, 0x80, v);
        func_00f59870(0, 0x80, 0x80, 0x80, 0x80);
        func_00f59870(2, 0x80, 0x80, 0x80, 0x80);
        func_00f59870(1, 0x80, 0x80, 0x80, 0);
        func_001bfac8();
    }
    func_00f50548(0x80);
    func_00f50568(0x80);
    func_00f50578(0x80);
    func_00f55330(0x80);
    func_00f55378(0x80);
    func_00f59870(-1, 0x80, 0x80, 0x80, 0x80);
    func_00f59870(1, 0x80, 0x80, 0x80, 0);
}
