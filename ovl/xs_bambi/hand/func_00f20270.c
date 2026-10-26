/* xs_bambi.x func_00f20270: matched by hand (session 131b). */
#include "ovl.h"

extern s32 D_002E26A0;
extern s32 D_00F20900;
extern u8 *D_00F20904;
extern f32 D_00F20A04, D_00F20A08;
extern s32 D_00F20A00, D_00F20A0C;
extern s32 D_00304B7C, D_00304B80;
void *func_00130340(s32, s32, f32);
void *func_00123488(s32);
void func_00241c00(void *, f32 *, void *, f32 *, void *);
void func_0011ef10(s32, void *);
void func_00f20550(void);
void func_00f20188(void);
void func_00f20270(void) {
    void *p;

    D_00F20900 = D_002E26A0;
    func_00130340(D_002E26A0, 0x40000000, 0.0f);
    p = func_00123488(0x70001);
    D_00F20A04 = 0.0f;
    D_00F20A08 = 18000.0f;
    D_00F20904 = p;
    func_00241c00(&D_00304B7C, &D_00F20A04, &D_00304B80, &D_00F20A08, p);
    func_00f20550();
    D_00F20A0C = *(s32 *)(D_00F20904 + 0x68);
    func_0011ef10(0xCB20, func_00f20188);
    D_00F20A00 = 1;
}
