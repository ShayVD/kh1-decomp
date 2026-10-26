/* dktitle.x func_00f20038: matched by hand. */
#include "ovl.h"

typedef struct { s32 a, b, c, d; } Q;
extern Q D_00F286F0[];
extern s32 D_00F2C6F0;
extern char D_00F27280[];
void printf(char *, ...);
s32 exit(s32);
Q *func_00f20038(s32 n) {
    Q *p = &D_00F286F0[D_00F2C6F0];
    D_00F2C6F0 += n;
    if (D_00F2C6F0 >= 1024) { printf(D_00F27280); exit(1); }
    return p;
}
