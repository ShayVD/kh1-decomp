#include "common.h"

void func_00262c78(void);
void func_00109288(void);
void func_00109770(void);

extern s32 D_0048C6F0[];
extern s32 D_00472150[];

void func_00100558(void) {
    func_00262c78();
    func_00109288();
    for (;;) func_00109770();
}

void func_00100580(s32 idx, s32 *dst) {
    s32 i;
    for (i = 0; i < 2; i++) {
        dst[0] = D_0048C6F0[idx * 4 + 0];
        dst[1] = D_0048C6F0[idx * 4 + 1];
        dst[2] = D_0048C6F0[idx * 4 + 2];
        dst[3] = D_0048C6F0[idx * 4 + 3];
        dst[4] = D_00472150[0];
        dst[5] = D_00472150[1];
        dst[6] = D_00472150[2];
        dst[7] = D_00472150[3];
        dst += 8;
    }
}
