/* gb.x func_00f2e8d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x4C]; u16 n; u8 pad4e[0x36]; s16 cur; } World;
s32 func_00f23928(s32);
s32 func_00f23a00(s32);
void func_00f2e578(void *);
void func_00f2e660(void *, s32, s32, s32, s32);
void func_00f2e788(void *, s32);
void func_00f2e808(void *);
extern World *D_00F56DC0;
extern u8 D_00F56DC8[];
extern f32 D_00F6156C;

void func_00f2e8d8(void) {
    s32 cur, next, prev, a, b;
    func_00f2e578(D_00F56DC8);
    cur = D_00F56DC0->cur;
    next = func_00f23928(cur); prev = func_00f23a00(cur); a = D_00F6156C * 80.0f; b = D_00F6156C * 128.0f; func_00f2e660(D_00F56DC8, prev, -432, 352, a); func_00f2e660(D_00F56DC8, cur, 0, 512, b); func_00f2e660(D_00F56DC8, next, 432, 352, a);
    func_00f2e788(D_00F56DC8, D_00F56DC0->n - 1);
    func_00f2e808(D_00F56DC8);
}
