/* gb.x func_00f29558: the twin of wm.x func_00f50650 (tools/ovl/twins.py). */
#include "ovl.h"

void func_001bfac8(void);
void func_00f20248(s32);
void func_00f29450(s32);
void func_00f29470(s32);
void func_00f29480(s32);
void func_00f2e238(s32);
void func_00f2e280(s32);
void func_00f32778(s32, s32, s32, s32, s32);

void func_00f29558(void) {
    s32 i;
    s32 v;
    s32 w;

    for (i = 0; i < 5; i++) {
        v = (i * -128) / 5 + 128;
        w = (i * -32) / 5 + 128;
        func_00f29450(v);
        func_00f29470(v);
        func_00f29480(v);
        func_00f2e238(v);
        func_00f2e280(v);
        func_00f32778(-1, v, v, w, 0x80);
        func_00f32778(-1, 0x80, 0x80, 0x80, v);
        func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
        func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
        func_00f32778(1, 0x80, 0x80, 0x80, 0);
        func_001bfac8();
    }
    func_00f29450(0);
    func_00f29470(0);
    func_00f29480(0);
    func_00f2e238(0);
    func_00f2e280(0);
    func_00f32778(-1, 0x80, 0x80, 0x80, 0);
    func_00f32778(0, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(2, 0x80, 0x80, 0x80, 0x80);
    func_00f32778(1, 0x80, 0x80, 0x80, 0);
    func_00f20248(11);
    func_00f20248(12);
}
