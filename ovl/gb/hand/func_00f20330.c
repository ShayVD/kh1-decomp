/* gb.x func_00f20330: matched by hand. */
#include "ovl.h"

#include "ovl.h"

extern s32 D_002B6774;
extern s32 D_002BBE0C;
extern s32 D_00F56D94;
extern s32 D_00F56D9C;
extern u64 *D_00F56DC8;
extern s32 D_00F60BF8;
extern s32 D_00F707EC;
extern char D_00F71480[];
extern char D_00F71498[];
extern s32 D_00F74200;
extern s32 D_00F74204;
extern s32 D_00F7421C;
extern s32 D_00F74220;
void func_00114820(void);
void func_0011ef10(s32, void *);
s32 func_001bb500(s32, s32);
void func_001bb7c8(char *, s32);
void func_001bfac8(void);
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
void func_00f200c8(void);
void func_00f20290(s32);
void func_00f20718(void);
void func_00f21410(void);
void func_00f21ea0(void);
void func_00f22338(s32, s32, s32, s32);
void func_00f25cb0(void);
void func_00f25ed8(void);
void func_00f261e8(void);
void func_00f3dfe0(s32);
u64 *func_00f40200(s32, s32, s32, u64 *);
void func_00f43330(s32);

void func_00f20330(void) {
    s32 done;
    D_00F74200 = 0;
    func_00114820();
    if (D_00F60BF8 != 0)
        func_00f25cb0();
    if (D_00F56D94 == 0) {
        D_00F707EC = func_001bb500(0x40000, 16);
        func_001bb7c8(D_00F71480, D_00F707EC);
        func_001bb7c8(D_00F71498, D_00F74204);
        func_00f43330(D_00F74204);
        func_00f20718();
        func_00f261e8();
        func_00f25ed8();
        D_00F56D94 = 1;
    }
    func_00f21410();
    func_00f22338(0, 0, 0, 0);
    while (D_002B6774 != 0)
        func_001bfac8();
    func_001bfac8();
    func_001bfac8();
    D_002BBE0C = 0;
    func_001c00e8(2, func_00f21ea0, KH1_Q(0));
    func_00f20290(10);
    if (D_00F56D94 < 2)
        func_0011ef10(0x2BFE8, func_00f200c8);
    D_00F56D94 = 2;
    func_00f22338(0, 0, 0, 0);
    func_00f3dfe0(0);
    D_00F56D9C = 0;
    done = 0;
    while (1) {
        if (!done) {
            done = 1;
            D_00F56DC8 = func_00f40200(10001, 0x2600, D_00F7421C, D_00F56DC8);
            D_00F56DC8 = func_00f40200(10002, 0x2A00, D_00F74220, D_00F56DC8);
        }
        func_001bfac8();
        D_00F56D9C++;
    }
}
