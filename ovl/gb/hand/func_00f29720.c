/* gb.x func_00f29720: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f20290(s32);
void func_00f29450(s32);
void func_00f29470(s32);
void func_00f29480(s32);
void func_00f2e238(s32);
void func_00f2e280(s32);
void func_00f32778(s32, s32, s32, s32, s32);

void func_00f29720(void) {
    s32 i, v;
    /* pinned: gcc otherwise gives the hoisted divisor s2 and the counter s1 */
    register s32 n asm("s1") = 5;
    func_00f20290(0xB);
    func_00f20290(0xC);
    for (i = 0; i < 5; i++) {
        v = (i << 7) / n;
        func_00f29450(v);
        func_00f29470(v);
        func_00f29480(v);
        func_00f2e238(v);
        func_00f2e280(v);
        func_00f32778(-1, 0x80, 0x80, 0x80, v);
        func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
        func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
        func_00f32778(1, 0x80, 0x80, 0x80, 0);
        func_001bfac8();
    }
    func_00f29450(0x80);
    func_00f29470(0x80);
    func_00f29480(0x80);
    func_00f2e238(0x80);
    func_00f2e280(0x80);
    func_00f32778(-1, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(1, 0x80, 0x80, 0x80, 0);
}
