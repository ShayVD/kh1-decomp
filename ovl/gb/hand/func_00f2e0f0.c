/* gb.x func_00f2e0f0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x40]; u8 a[4]; u8 b[4]; u8 pad48[0x36]; s16 idx; } World;
extern u8 D_00379F28[][4];
extern u8 D_0037A028[][4];
extern World *D_00F56DC0;

void func_00f2e0f0(void) {
    D_00F56DC0->a[0] = D_00379F28[D_00F56DC0->idx][0];
    D_00F56DC0->a[1] = D_00379F28[D_00F56DC0->idx][1];
    D_00F56DC0->a[2] = D_00379F28[D_00F56DC0->idx][2];
    D_00F56DC0->b[0] = D_0037A028[D_00F56DC0->idx][0];
    D_00F56DC0->b[1] = D_0037A028[D_00F56DC0->idx][1];
    D_00F56DC0->b[2] = D_0037A028[D_00F56DC0->idx][2];
}
