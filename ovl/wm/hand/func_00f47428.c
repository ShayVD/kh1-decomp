/* wm.x func_00f47428: matched by hand. */
#include "ovl.h"

extern s32 D_002B6774;
extern s32 D_002BBE0C;
extern s32 D_00F9B514;
extern s32 D_00F9B51C;
extern u64 *D_00F9B548;
extern s32 D_00FA5378;
extern s32 D_00FB4F6C;
extern char D_00FB7530[];
extern char D_00FB7548[];
extern s32 D_010809B8;
extern s32 D_010809BC;
extern s32 D_010809D4;
extern s32 D_010809D8;
void func_00114820(void);
void func_0011ef10(s32, void *);
s32 func_001bb500(s32, s32);
void func_001bb7c8(char *, s32);
void func_001bfac8(void);
s32 func_001c00e8(s32 prio, void *fn, kh1_u128 q);
void func_00f471c0(void);
void func_00f47388(s32);
void func_00f47810(void);
void func_00f48508(void);
void func_00f48f98(void);
void func_00f49430(s32, s32, s32, s32);
void func_00f4cda8(void);
void func_00f4cfd0(void);
void func_00f4d2e0(void);
void func_00f650d8(s32);
u64 *func_00f672f8(s32, s32, s32, u64 *);
void func_00f6a428(s32);

void func_00f47428(void) {
    s32 done;
    D_010809B8 = 0;
    func_00114820();
    if (D_00FA5378 != 0)
        func_00f4cda8();
    if (D_00F9B514 == 0) {
        D_00FB4F6C = func_001bb500(0x40000, 16);
        func_001bb7c8(D_00FB7530, D_00FB4F6C);
        func_001bb7c8(D_00FB7548, D_010809BC);
        func_00f6a428(D_010809BC);
        func_00f47810();
        func_00f4d2e0();
        func_00f4cfd0();
        D_00F9B514 = 1;
    }
    func_00f48508();
    func_00f49430(0, 0, 0, 0);
    while (D_002B6774 != 0)
        func_001bfac8();
    func_001bfac8();
    func_001bfac8();
    D_002BBE0C = 0;
    func_001c00e8(2, func_00f48f98, 0);
    func_00f47388(10);
    if (D_00F9B514 < 2)
        func_0011ef10(0x2BFE8, func_00f471c0);
    D_00F9B514 = 2;
    func_00f49430(0, 0, 0, 0);
    func_00f650d8(0);
    D_00F9B51C = 0;
    done = 0;
    while (1) {
        if (!done) {
            done = 1;
            D_00F9B548 = func_00f672f8(10001, 0x2600, D_010809D4, D_00F9B548);
            D_00F9B548 = func_00f672f8(10002, 0x2A00, D_010809D8, D_00F9B548);
        }
        func_001bfac8();
        D_00F9B51C++;
    }
}
