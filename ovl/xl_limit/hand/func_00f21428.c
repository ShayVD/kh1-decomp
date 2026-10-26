/* xl_limit.x func_00f21428: matched by hand. */
#include "ovl.h"

void func_00f20130(void *);
void func_0014f830(s32, s32, void *, void *, void *, s32, void *, void *, s32);
void func_0014f658(void *, s32);
void func_00130340(void *, s32, f32);
void *func_00130578(void *, s32, f32);
s32 func_00148968(void *, s32, s32);
s32 func_00149678(void);
void func_00f21170(void);
void func_00f211b0(void);
void func_00f21328(void);
void func_00f21358(void);
void func_00f212f0(void);
extern void *D_002E26A0;
extern s32 D_00F23208;
extern u8 D_00F23240[];
extern s32 D_00F23E04;
extern s32 D_00F23E08;
void func_00f21428(void) {
    void *p;
    s32 n;
    s32 *q;
    func_00f20130(D_00F23240);
    p = D_002E26A0;
    func_0014f830(0x20, 4, func_00f21170, func_00f211b0, func_00f21328, 0, func_00f21358, func_00f212f0, 0);
    func_0014f658(p, 0x20);
    func_00130340(p, 0x010000D2, 8.0f);
    func_00130578(p, 0x40000000, 0.0f);
    func_00148968(p, D_00F23208, 0);
    switch (func_00149678()) {
    case 0:
        n = 5;
        break;
    case 1:
        n = 3;
        break;
    default:
        n = 4;
        break;
    }
    q = &D_00F23E08;
    *q = func_00148968(p, D_00F23208, n);
    D_00F23E04 = 0;
}
