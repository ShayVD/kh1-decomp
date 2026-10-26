/* gb.x func_00f339a0: matched by hand. */
#include "ovl.h"

void func_001bfac8(void);
void func_00f20290(s32);
void func_00f2e238(s32);
void func_00f2e280(s32);
void func_00f32778(s32, s32, s32, s32, s32);
void func_00f33380(s32);

void func_00f339a0(void) {
    s32 i;
    s32 v;

    func_00f20290(11);
    for (i = 0; i < 5; i++) {
        v = i * 128 / 5;
        func_00f33380(v);
        func_00f2e238(i * 14);
        func_00f2e280(v);
        func_00f32778(-1, 35, 35, 65, i * 128 / 5);
        func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
        func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
        func_00f32778(5, 0x80, 0x80, 0x80, v);
        func_001bfac8();
    }
    func_00f33380(0x80);
    func_00f2e238(70);
    func_00f2e280(0x80);
    func_00f32778(-1, 35, 35, 65, 0x80);
    func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(5, 0x80, 0x80, 0x80, 0x80);
}
