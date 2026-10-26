/* dkmovie.x func_00f221b0: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; } Pair;
void func_00f21da0(s32, s32, s32, void *, s32);
extern u8 D_00F283D0[];
extern Pair D_00F28648;
extern s32 D_00F2866C;
s32 func_00f221b0(s32 off, s32 arg1, s32 *skip, s32 arg3) {
    s32 n;
    if (D_00F2866C != 0) {
        *skip = 0x800 - D_00F2866C;
        off = off - D_00F2866C + 0x800;
        D_00F28648.a--;
    } else {
        *skip = 0;
    }
    n = off / 0x800;
    if (off & 0x7FF) {
        D_00F2866C = 0x800 - (off - n * 0x800);
        n++;
    } else {
        D_00F2866C = 0;
    }
    func_00f21da0(D_00F28648.a, n, arg1, D_00F283D0, arg3);
    D_00F28648.a += n;
    return 1;
}
