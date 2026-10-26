/* gb.x func_00f431c8: matched by hand. */
#include "ovl.h"

extern s8 D_00F70738, D_00F70739, D_00F7073B;
extern kh1_u128 *D_00F82A88[];
typedef struct { void (*a)(void); void (*b)(void); } VT;
extern VT *D_00F707CC;
void func_00f428e0(s32);
void func_00f431c8(kh1_u128 **p) {
    s32 i;
    if (D_00F70738) return;
    for (i = 0; i < 3; i++) D_00F82A88[i] = p[i];
    D_00F707CC->a();
    for (i = 0; i < 3; i++) {
        if (D_00F82A88[i] != p[i]) func_00f428e0(i);
        p[i] = D_00F82A88[i];
    }
    if (D_00F70739) {
        D_00F70738 = D_00F70739;
        D_00F70739 = 0;
        D_00F7073B = 0;
        D_00F707CC->b();
        D_00F707CC = 0;
    }
}
