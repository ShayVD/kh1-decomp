/* wm.x func_00f77af0: the main state machine (session 141), gb func_00f509f8 ported (tools: symbols mapped by position). */
#include "ovl.h"

typedef struct { u8 pad[8]; s32 (*f8)(void (*)(void), s32, s32); } GbVt;
extern GbVt *D_00FB4F4C;
extern s32 D_0108F27C, D_0108F280, D_0108F284;
extern s32 D_00FB4B4C, D_00FB4B50, D_00FB4B54, D_00FB4B58, D_00FB4B5C, D_00FB4B60, D_00FB4A70;
extern s32 D_0108F1B4, D_0108F184;
extern u8 D_00FB4EBA;
extern s32 D_0108F1CC, D_0108F1D0, D_0108F1D4, D_0108F1DC;
extern f32 D_0108F1E8;
extern s32 D_00FB4D34, D_00FB4D38, D_00FB4D3C, D_00FB4D40, D_00FB4D44, D_00FB4D48, D_00FB4D4C, D_00FB4D50, D_00FB4D54;
extern s32 D_00FB4A64, D_00FB4A68;
extern f32 D_00FB4A60, D_00FB4AAC, D_00FB4AB0, D_00FB4AB4;
void func_00f6b7c8(void);
void *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_00f6cfa0(void);
void func_00f74f30(void);
void func_00f6f2a8(void);
void func_00f6e278(void);
void func_00f70828(void);
void func_00f75d80(void);
void func_00f77648(void);
void func_0024e468(s32);
void func_00f77af0(void) {
    s32 state;
    D_0108F27C = 0;
    D_0108F280 = 0;
    D_0108F284 = 0;
    D_00FB4F4C->f8(func_00f6b7c8, 1, 2);
    func_00f6b6a0(7, 1, 0, 1, 0, 18, 25, 0, D_00FB4B4C, D_00FB4B50, 0, 0, 0, D_00FB4B54, D_00FB4B58, D_00FB4B5C, D_00FB4B60, 256, D_00FB4A70);
    func_00f6b6a0(7, 11, 0, 1, 0, 18, 20, 0, D_00FB4B4C - 16, D_00FB4B50 + 2, 0, 0, 0, D_00FB4B54, D_00FB4B58, D_00FB4B5C, D_00FB4B60, 256, D_00FB4A70);
    state = D_0108F1B4 == 1 ? 7 : 0;
    for (;;) {
        switch (state) {
        case 0:
            D_0108F1CC = D_00FB4D34;
            D_0108F1E8 = 128.0f;
            D_0108F1D0 = D_00FB4D38;
            D_0108F1D4 = D_00FB4D4C;
            D_0108F1DC = D_00FB4A64;
            D_0108F280 = 0;
            D_00FB4A60 = D_00FB4AAC;
            state = func_00f6cfa0();
            break;
        case 1:
            D_0108F1CC = D_00FB4D44;
            D_0108F1E8 = 128.0f;
            D_0108F1D0 = D_00FB4D48;
            D_0108F1D4 = D_00FB4D54;
            D_00FB4A60 = D_00FB4AB4;
            D_0108F1DC = D_00FB4A68;
            func_00f74f30();
            D_0108F1DC = D_00FB4A64;
            state = 0;
            break;
        case 2:
            D_0108F1CC = D_00FB4D3C;
            D_0108F1E8 = 128.0f;
            D_0108F1D0 = D_00FB4D40;
            D_0108F1D4 = D_00FB4D50;
            D_0108F1DC = D_00FB4A64;
            D_00FB4A60 = D_00FB4AB0;
            func_00f6f2a8();
            state = 0;
            break;
        case 5:
            func_00f6e278();
            state = 0;
            break;
        case 6:
            func_00f70828();
            state = 0;
            break;
        case 7:
            D_0108F1CC = D_00FB4D3C;
            D_0108F1E8 = 128.0f;
            D_0108F1D0 = D_00FB4D40;
            D_0108F1D4 = D_00FB4D50;
            D_0108F1DC = D_00FB4A64;
            D_00FB4A60 = D_00FB4AB0;
            func_00f75d80();
            state = 0;
            break;
        case 8:
            func_00f77648();
            state = 0;
            break;
        case 9:
            D_0108F184 = 0;
            D_00FB4EBA = 1;
            for (;;)
                func_0024e468(1);
        }
    }
}
