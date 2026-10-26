/* gb.x func_00f23ed8: matched by hand. */
#include "ovl.h"

typedef struct { u16 a; u16 b; u16 c; u8 pad[6]; } E4a;
typedef struct { u8 pad[0xA4]; u16 n; u8 pad2[0x6A]; E4a e[320]; u8 pad3[0x10EC - 0x110 - 320 * 12]; s8 arr[1]; } W4a;
s8 func_001ba3f0(s32);
s32 func_001bb740(void);
extern W4a *D_00F56DC0;

void func_00f23ed8(void) {
    s32 i;
    s32 j;
    E4a *e = D_00F56DC0->e;

    for (j = 0; j < 320; j++, e++) {
        e->c = 0;
        e->b = (e->b & 0xF420) | 0x420;
    }
    D_00F56DC0->n = 0;
    for (i = 0; i < func_001bb740(); i++) {
        D_00F56DC0->arr[i] = func_001ba3f0(i);
    }
}
