/* xl_limit.x func_00f22408: matched by hand. */
#include "ovl.h"

s32 func_00148968(void *, s32, s32);
s32 func_00149678(void);
s32 printf(const char *, ...);
extern s32 D_00F23208;
extern char D_00F23430[];
extern s32 D_00F23EC0[];
void func_00f22408(void *p) {
    s32 i;
    s32 n;
    for (i = 0; i < 12; i++) {
        D_00F23EC0[i] = func_00148968(p, D_00F23208, i);
        printf(D_00F23430, i, D_00F23EC0[i]);
    }
    switch (func_00149678()) {
    case 0:
        n = 14;
        break;
    case 1:
        n = 12;
        break;
    default:
        n = 13;
        break;
    }
    D_00F23EC0[12] = func_00148968(p, D_00F23208, n);
}
