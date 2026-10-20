#include "common.h"
#include "data/bss_004E.h"
extern s32 D_002C1390;
extern s32 D_002C1388;
extern s32 D_004E3444;
extern void (*D_004E3434)(void);
CONTEXT_ONLY void func_0011e528(void) { D_002C1390 = 0; }
CONTEXT_ONLY void func_0011e610(void) { D_002C1390 = 1; }
void func_0011e758(void) {
    s32 *p = &D_002C1388;
    if (*p == 0) func_0011e528();
    if (D_004E3444 == 0 && *p == 0) func_0011e610();
    if (D_004E3434) D_004E3434();
}
extern s32 D_002C1368[];
extern s32 D_002C1378[];
extern s32 D_004E3438, D_004E343C, D_004E3440, D_004E3444, D_004E3448;
extern void (*D_004E3434)(void);

void func_0011c7c0(s32, s32, s32);
void func_001ed520(s32);
CONTEXT_ONLY void func_0011c7d8(s32 a) { func_001ed520(a); }
typedef struct { char c[13]; } Str13;
extern char D_0048D110[];
extern Str13 D_0048D118;
extern char D_0048D128[];
int sprintf(char *, const char *, ...);
char *strcat(char *, const char *);
CONTEXT_ONLY void func_0011ca68(s32 a0, char *a1) {
    char buf[80];
    sprintf(buf, D_0048D110, a0);
    if (buf[0] == ' ') {
        buf[0] = '0';
        if (buf[1] == ' ') buf[1] = '0';
    }
    *(Str13 *)a1 = D_0048D118;
    strcat(a1, buf);
    strcat(a1, D_0048D128);
}
void func_0011e7f8(void);
void func_0011e8a0(void);
s32 func_00120748(char *, s32, void (*)(void), s32);

void func_0011e8d0(s32 a0, s32 a1, s32 a2, void (*a3)(void), s32 a4, s32 a5) {
    char buf[64];
    D_004E3434 = a3;
    D_004E3438 = a1;
    D_004E343C = a2;
    D_004E3440 = a0;
    D_004E3444 = a4;
    D_004E3448 = a5;
    if (D_002C1368[1] != D_002C1378[1] && D_002C1378[1] != 0) {
        if (D_002C1368[1] == -2) func_0011c7d8(0);
        else func_0011c7c0(1, 0, 100);
        func_0011ca68(D_002C1378[1], buf);
        func_00120748(buf, D_004E3448, func_0011e8a0, 0);
        return;
    }
    func_0011e7f8();
}
extern s32 D_002C1368[];
extern void (*D_004E3430)(void);
s32 func_001ed128(s32, s32);
void func_001ed460(s32, s32, s32);
s32 func_0011cba0(void);
void func_0011ef10(s32, s32 (*)(void));
void func_0011eb88(s32 a0, s32 a1, s32 a2, void (*a3)(void)) {
    D_002C1368[a0] = -1;
    D_004E3430 = a3;
    func_001ed128(1, a0);
    func_001ed460(a0, a1, a2);
    func_0011ef10(10000, func_0011cba0);
}
