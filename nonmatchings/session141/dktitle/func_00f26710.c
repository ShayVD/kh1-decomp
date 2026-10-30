/* 7 words differ, score 5 (this void-decl version; the session132 s32 draft is 2 words, score 5). With s32 func_0011ef10 the diff is lui v0 vs lui v1 for D_00F26E30 after the call; declaring it void moves the diff to li v0,-1 scheduled before the ori a0/addiu a1 arg setup (still 5). Tried: greedy permutation of the E3C/C894/C898/7214 stores and of the //{ //} block, 10 min permuter (only found k = 0x2bf84 temp after the func_0024dd98 call, still 5). */
#include "ovl.h"

void func_00109278(void);
void func_0011ef10(s32, void *);
void func_0020b968(void);
s32 func_0024b778(s32);
void *func_0024b7a0(s32, u8 *, s32);
s32 func_0024dd98(s32 *);
typedef struct { void (*f0)(void); void (*f1)(void); s32 (*f2)(void *, s32, s32); } Ops;
extern u8 D_00BA0000[];
extern u8 *D_00F26E30;
extern s32 D_00F26E34;
extern s32 D_00F26E38;
extern s32 D_00F26E3C;
extern s32 D_00F26E40;
extern u8 *D_00F26E44;
extern u8 *D_00F26E48;
extern Ops *D_00F26E4C;
extern s32 D_00F26E64;
extern s32 D_00F26E6C;
extern s32 D_00F27214;
extern s32 D_00F2C894;
extern s32 D_00F2C898;
extern s32 D_00F2C89C;
extern s32 D_00F2C8A4;
extern s32 D_00F2C8A8;
extern s32 D_00F2C8AC;
extern s32 D_00F2C8B0;
extern s32 D_00F2C8B4;
extern s32 D_00F2C8D4;
extern s32 D_00F2C8D8;
extern s32 D_00F2C8E0[3];
extern void func_00f24b60(void);
extern s32 func_00f26578(void);

void func_00f26710(s32 arg0) {
    u8 *p = D_00BA0000;
    s32 h;
    s32 n;
    Ops *o;
    func_00109278();
    func_0020b968();
    D_00F2C8B4 = 0;
    D_00F2C8D4 = 0;
    D_00F2C8E0[0] = 0;
    D_00F2C8E0[1] = 0;
    D_00F2C8D8 = 0;
    D_00F2C8E0[2] = 0;
    D_00F2C8B0 = 0;
    D_00F2C8A8 = 0;
    D_00F2C8AC = 0;
    D_00F26E64 = 1;
    D_00F26E6C = 0;
    D_00F2C89C = 0;
    h = func_0024dd98(&arg0);
    D_00F26E3C = 0;
    D_00F2C894 = -1;
    D_00F2C898 = 0;
    D_00F27214 = 0;
    func_0011ef10(0x2bf84, func_00f26578);
    //{
    D_00F26E30 = p;
    D_00F26E34 = 1;
    p += 0x20000;
    D_00F26E40 = arg0;
    D_00F26E38 = h;
    D_00F26E48 = p + 0x80000;
    D_00F26E44 = p;
    p += 0x100000;
    //}
    n = func_0024b778(2);
    o = func_0024b7a0(1, p, 0);
    p += n;
    D_00F26E4C = o;
    o->f2(func_00f24b60, 1, 0);
    D_00F2C8A4 = (s32)(p + 63) & ~63;
}
