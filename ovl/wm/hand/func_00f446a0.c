/* wm.x func_00f446a0: matched by hand. */
#include "ovl.h"

typedef struct { char *p[8]; } N446a0;
s32 func_001bef40(char *, const char *, ...);
s32 func_001bb7c8(void *, s32);
void func_00162058(s32);
void func_00162070(s32, s32 *, s32 *, s32 *);
void func_001623d0(s32, s32 *);
void func_00167f68(s32, s32);
void func_001bfac8(void);
extern N446a0 D_00FB7450;
extern char D_00FB7470[];
extern char D_00FB7480[];
extern char D_00FB7488[];
extern s32 D_00F9B328;
extern s32 D_01080830;
extern s32 D_01080834;
extern s32 D_01080838[2];
extern s32 D_010808E8[];
extern s32 D_010808F8[];
extern s32 D_01080800[];
extern s32 D_01080810[];
extern u8 D_01080820[];

void func_00f446a0(s32 slot, s32 n, void (*cb)(void)) {
    char name[32];
    char path[64];
    N446a0 names = D_00FB7450;
    s32 tmp;

    D_00F9B328 = 1;
    tmp = 0;
    while ((D_01080838[0] == slot && D_01080830 != 0) || (D_01080838[1] == slot && D_01080834 != 0)) {
        func_001bfac8();
    }
    func_001bfac8();
    func_001bef40(name, D_00FB7470, names.p[n]);
    func_001bef40(path, name, D_00FB7480);
    func_001bb7c8(path, D_010808E8[slot]);
    func_001bef40(path, name, D_00FB7488);
    func_001bb7c8(path, D_010808F8[slot]);
    func_00162058(D_010808E8[slot]);
    func_00162058(D_010808F8[slot]);
    func_00162070(D_010808E8[slot], &tmp, &D_01080800[slot], &D_01080810[slot]);
    func_001623d0(D_010808F8[slot], &D_01080800[slot]);
    func_00167f68(D_01080810[slot], D_010808F8[slot]);
    D_01080820[slot] = n;
    D_00F9B328 = 0;
    cb();
}
