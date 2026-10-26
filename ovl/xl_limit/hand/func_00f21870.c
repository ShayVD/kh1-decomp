/* xl_limit.x func_00f21870: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xC]; void *fC; } Res;
void func_00f20130(void *);
void func_0014f830(s32, s32, void *, void *, void *, s32, void *, s32, s32);
void func_0014f658(void *, s32);
void func_00130340(void *, s32, f32);
Res *func_00130578(void *, s32, f32);
s32 func_00148968(void *, s32, s32);
void func_00f215b8(void);
void func_00f21620(void);
void func_00f21678(void);
void func_00f216a8(void);
void func_00f21858(void);
extern void *D_002E26A0;
extern s32 D_00F23208;
extern u8 D_00F23250[];
extern s32 D_00F23E0C;
void func_00f21870(void) {
    void *p;
    func_00f20130(D_00F23250);
    p = D_002E26A0;
    func_0014f830(0x20, 4, func_00f215b8, func_00f21620, func_00f21678, 0, func_00f216a8, 0, 0);
    func_0014f658(p, 0x20);
    func_00130340(p, 0x010000C8, 8.0f);
    func_00130578(p, 0x40000000, 0.0f)->fC = func_00f21858;
    func_00148968(p, D_00F23208, 0);
    D_00F23E0C = 0;
}
