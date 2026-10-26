/* wm.x func_00f553b8: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f47340(s32);
void func_00f50548(s32);
void func_00f50568(s32);
void func_00f50578(s32);
void func_00f55330(s32);
void func_00f55378(s32);
void func_00f59870(s32, s32, s32, s32, s32);

void func_00f553b8(s32 arg0) {
    /* register pin: gcc otherwise rotates the loop registers (s1/s2/s3) */
    register s32 k asm("s2");
    register s32 n asm("s1");
    s32 i;
    s32 v;

    if (arg0 != 0) {
        n = 5;
        k = 0;
        for (i = 0; i < 5; i++) {
            v = k / n + 128;
            k -= 128;
            func_00f50548(v);
            func_00f50568(v);
            func_00f50578(v);
            func_00f55330(v);
            func_00f55378(v);
            func_00f59870(-1, 0x80, 0x80, 0x80, v);
            func_00f59870(0, 0x80, 0x80, 0x80, 0x80);
            func_00f59870(2, 0x80, 0x80, 0x80, 0x80);
            func_001bfac8();
        }
    }
    func_00f50548(0);
    func_00f50568(0);
    func_00f50578(0);
    func_00f55330(0);
    func_00f55378(0);
    func_00f59870(-1, 0x80, 0x80, 0x80, 0);
    func_00f59870(0, 0x80, 0x80, 0x80, 0x80);
    func_00f59870(2, 0x80, 0x80, 0x80, 0x80);
    func_00f47340(11);
    func_00f47340(12);
}
