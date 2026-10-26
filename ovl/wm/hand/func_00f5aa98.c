/* wm.x func_00f5aa98: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f47388(s32);
void func_00f55330(s32);
void func_00f55378(s32);
void func_00f59870(s32, s32, s32, s32, s32);
void func_00f5a478(s32);

void func_00f5aa98(void) {
    s32 i;
    s32 v;

    func_00f47388(11);
    for (i = 0; i < 5; i++) {
        v = i * 128 / 5;
        func_00f5a478(v);
        func_00f55330(i * 14);
        func_00f55378(v);
        func_00f59870(-1, 35, 35, 65, i * 128 / 5);
        func_00f59870(2, 0x80, 0x80, 0x80, 0x80);
        func_00f59870(0, 0x80, 0x80, 0x80, 0x80);
        func_00f59870(5, 0x80, 0x80, 0x80, v);
        func_001bfac8();
    }
    func_00f5a478(0x80);
    func_00f55330(70);
    func_00f55378(0x80);
    func_00f59870(-1, 35, 35, 65, 0x80);
    func_00f59870(2, 0x80, 0x80, 0x80, 0x80);
    func_00f59870(0, 0x80, 0x80, 0x80, 0x80);
    func_00f59870(5, 0x80, 0x80, 0x80, 0x80);
}
