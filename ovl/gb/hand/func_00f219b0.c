/* gb.x func_00f219b0: matched by hand. */
#include "ovl.h"

/* gb.x func_00f219b0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x76]; s16 mode; } GbState;
extern GbState *D_00F56DC0;
void func_0011d768(s32);
void func_00106880(s32);
s32 func_001c01b0(s32, void *, s32, s32);
void func_001bfac8(void);
void func_00f21778(s32, s32);
void func_00f32728(s32, s32);
void func_00f333f8(s32);

void func_00f219b0(s32 mode) {
    s32 old, i;
    if (mode == D_00F56DC0->mode)
        return;
    if (mode == 3) {
        D_00F56DC0->mode = mode;
        func_0011d768(mode);
        func_00106880(30);
        return;
    }
    func_001c01b0(-1, func_00f21778, mode, 30);
    old = D_00F56DC0->mode;
    mode |= old << 8;
    if (mode == 1 || mode == 0x100)
        func_0011d768(21);
    else
        func_0011d768(22);
    func_001bfac8();
    switch (mode) {
    case 0x100:
        for (i = 0; i < 30; i++) {
            func_00f32728(5, old * 15 - i / 2);
            func_001bfac8();
        }
        break;
    case 1:
        for (i = 0; i < 30; i++) {
            func_00f32728(5, old * 15 + i / 2);
            func_001bfac8();
        }
        break;
    case 2:
    case 0x102:
    case 0x200:
    case 0x201:
        func_00f333f8(mode & 0xFF);
        break;
    }
    func_00f32728(5, (mode & 0xFF) * 15);
    D_00F56DC0->mode = mode & 0xFF;
}
