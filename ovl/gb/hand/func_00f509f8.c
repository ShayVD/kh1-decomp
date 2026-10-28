/* gb.x func_00f509f8: the main state machine (session 141): an endless switch over the 10 modes; its cases sit after the jump. */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 (*f8)(void (*)(void), s32, s32); } GbVt;
extern GbVt *D_00F707CC;
extern s32 D_00F82ABC, D_00F82AC0, D_00F82AC4;
extern s32 D_00F703CC, D_00F703D0, D_00F703D4, D_00F703D8, D_00F703DC, D_00F703E0, D_00F702F0;
extern s32 D_00F829F4, D_00F829C4;
extern u8 D_00F7073A;
extern s32 D_00F82A0C, D_00F82A10, D_00F82A14, D_00F82A1C;
extern f32 D_00F82A28;
extern s32 D_00F705B4, D_00F705B8, D_00F705BC, D_00F705C0, D_00F705C4, D_00F705C8, D_00F705CC, D_00F705D0, D_00F705D4;
extern s32 D_00F702E4, D_00F702E8;
extern f32 D_00F702E0, D_00F7032C, D_00F70330, D_00F70334;
void func_00f446d0(void);
void *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f45ea8(void);
void func_00f4de38(void);
void func_00f481b0(void);
void func_00f47180(void);
void func_00f49730(void);
void func_00f4ec88(void);
void func_00f50550(void);
void func_0024e468(s32);
void func_00f509f8(void) {
    s32 state;
    D_00F82ABC = 0;
    D_00F82AC0 = 0;
    D_00F82AC4 = 0;
    D_00F707CC->f8(func_00f446d0, 1, 2);
    func_00f445a8(7, 1, 0, 1, 0, 18, 25, 0, D_00F703CC, D_00F703D0, 0, 0, 0, D_00F703D4, D_00F703D8, D_00F703DC, D_00F703E0, 256, D_00F702F0);
    func_00f445a8(7, 11, 0, 1, 0, 18, 20, 0, D_00F703CC - 16, D_00F703D0 + 2, 0, 0, 0, D_00F703D4, D_00F703D8, D_00F703DC, D_00F703E0, 256, D_00F702F0);
    state = D_00F829F4 == 1 ? 7 : 0;
    for (;;) {
        switch (state) {
        case 0:
            D_00F82A0C = D_00F705B4;
            D_00F82A28 = 128.0f;
            D_00F82A10 = D_00F705B8;
            D_00F82A14 = D_00F705CC;
            D_00F82A1C = D_00F702E4;
            D_00F82AC0 = 0;
            D_00F702E0 = D_00F7032C;
            state = func_00f45ea8();
            break;
        case 1:
            D_00F82A0C = D_00F705C4;
            D_00F82A28 = 128.0f;
            D_00F82A10 = D_00F705C8;
            D_00F82A14 = D_00F705D4;
            D_00F702E0 = D_00F70334;
            D_00F82A1C = D_00F702E8;
            func_00f4de38();
            D_00F82A1C = D_00F702E4;
            state = 0;
            break;
        case 2:
            D_00F82A0C = D_00F705BC;
            D_00F82A28 = 128.0f;
            D_00F82A10 = D_00F705C0;
            D_00F82A14 = D_00F705D0;
            D_00F82A1C = D_00F702E4;
            D_00F702E0 = D_00F70330;
            func_00f481b0();
            state = 0;
            break;
        case 5:
            func_00f47180();
            state = 0;
            break;
        case 6:
            func_00f49730();
            state = 0;
            break;
        case 7:
            D_00F82A0C = D_00F705BC;
            D_00F82A28 = 128.0f;
            D_00F82A10 = D_00F705C0;
            D_00F82A14 = D_00F705D0;
            D_00F82A1C = D_00F702E4;
            D_00F702E0 = D_00F70330;
            func_00f4ec88();
            state = 0;
            break;
        case 8:
            func_00f50550();
            state = 0;
            break;
        case 9:
            D_00F829C4 = 0;
            D_00F7073A = 1;
            for (;;)
                func_0024e468(1);
        }
    }
}
