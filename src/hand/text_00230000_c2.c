/* State setters at 0x233610-0x2336e4 (layout symbol func_00233610 split
 * into eight functions). */
#include "common.h"
extern void *D_00425BC8;
extern u8 D_002C5AD0[];
extern s32 D_00647780, D_00647784, D_00647788;
extern s32 D_0064778C, D_00647790, D_00647794;
extern s32 D_00647798, D_0064779C;
extern s32 D_006477A4;
void func_002336d8(void);

void func_00233610(void) {
    D_00425BC8 = D_002C5AD0;
    D_00647780 = 0;
    D_0064778C = 0;
    D_00647798 = 0;
    func_002336d8();
}

void func_00233650(s32 a, s32 b) {
    D_00647780 = 1;
    D_00647784 = a;
    D_00647788 = b;
}

void func_00233670(void) {
    D_00647780 = 0;
}

void func_00233680(s32 a, s32 b) {
    D_0064778C = 1;
    D_00647790 = a;
    D_00647794 = b;
}

void func_002336a0(void) {
    D_0064778C = 0;
}

void func_002336b0(s32 a) {
    D_00647798 = 1;
    D_0064779C = a;
}

void func_002336c8(void) {
    D_00647798 = 0;
}

void func_002336d8(void) {
    D_006477A4 = 0;
}
