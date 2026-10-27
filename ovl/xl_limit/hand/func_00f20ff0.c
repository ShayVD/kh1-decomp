/* xl_limit.x func_00f20ff0: matched by hand (session 139; the last step by decomp-permuter). */
#include "ovl.h"

void func_00f20130(void *);
void func_0014f830(s32, s32, void *, void *, void *, void *, void *, void *, s32);
void func_0014f658(void *, s32);
void func_00130340(void *, s32, f32);
/* returns the motion task (Res * in func_00f21d90); declared u8 here, as the match wants */
u8 func_00130578(void *, s32, f32);
s32 func_00148968(void *, s32, s32);
void func_00f20a20(void);
void func_00f20a78(void);
void func_00f20d70(void);
void func_0014cee8(void);
void func_00f20da0(void);
void func_00f20ae0(void);
extern void *D_002E26A0;
extern s32 D_00F23208;
extern u8 D_00F23210[];
extern f32 D_00F23484;
extern s32 D_00F23488, D_00F2348C, D_00F23480, D_00F23E00;
void func_00f20ff0(void) {
    void *p;
    func_00f20130(D_00F23210);
    p = D_002E26A0;
    func_0014f830(0x25, 5, func_00f20a20, func_00f20a78, func_00f20d70, func_0014cee8, func_00f20da0, func_00f20ae0, 0);
    func_0014f658(p, 0x25);
    func_00130340(p, 0x010000F0, 8.0f);
    func_00130578(p, 0x40000000, 0.0f);
    func_00148968(p, D_00F23208, 0);
    D_00F23488 = D_00F2348C = 0;
    D_00F23480 = 0;
    D_00F23484 = 0.0f;
    D_00F23E00 = 0;
}
