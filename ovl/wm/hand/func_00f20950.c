/* wm.x func_00f20950: matched by hand. */
#include "ovl.h"

typedef struct { char *p[2]; } N20950;
s32 func_001bef40(char *, char *, char *);
s32 func_001bb7c8(void *, s32);
void func_00162058(s32);
void func_00162070(s32, s32 *, s32 *, s32 *);
void func_001623d0(s32, s32 *);
void func_001763f0(s32);
extern N20950 D_00FB65B0;
extern char D_00FB65B8[];
extern char D_00FB65C0[];
extern char D_00FB65C8[];
extern char D_00FB65E8[];
extern char D_00FB6600[];
extern s32 D_00F850E4;
extern s32 D_00F850E8;
extern s32 D_00F850EC;
extern s32 D_00F850F0;
extern s32 D_00F87058;
extern s32 D_00F8705C;
extern s32 D_00FBA838;
extern s32 D_00FBA83C;

void func_00f20950(s32 n) {
    N20950 names = D_00FB65B0;
    char buf[64];

    D_00F850F0 = n;
    func_001bef40(buf, names.p[n], D_00FB65B8);
    func_001bb7c8(buf, D_00FBA838);
    func_001bef40(buf, names.p[n], D_00FB65C0);
    func_001bb7c8(buf, D_00FBA83C);
    func_00162058(D_00FBA838);
    func_00162058(D_00FBA83C);
    func_00162070(D_00FBA838, &D_00F850E4, &D_00F850E8, &D_00F850EC);
    func_001623d0(D_00FBA83C, &D_00F850E8);
    func_001bb7c8(D_00FB65C8, D_00F87058);
    func_001763f0(D_00F87058);
    if (n == 0) {
        func_001bb7c8(D_00FB65E8, D_00F8705C);
    } else {
        func_001bb7c8(D_00FB6600, D_00F8705C);
    }
}
