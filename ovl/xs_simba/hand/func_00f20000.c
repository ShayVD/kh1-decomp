/* xs_simba.x func_00f20000: matched by hand. */
#include "ovl.h"

void func_00f202e8(s32);
void func_00f20878(void);
extern void *D_00F21C44;
extern u8 D_00F21C50[];
extern s32 D_00FA6A80;
s32 func_00f20000(s32 a, void *b) {
    switch (a) {
    case 0:
        if (b == 0) {
            D_00F21C44 = D_00F21C50;
        } else {
            D_00F21C44 = b;
        }
        func_00f20878();
        return 0;
    case 1:
        return D_00FA6A80;
    case 2:
        func_00f202e8(101);
        return 0;
    }
    return 0;
}
