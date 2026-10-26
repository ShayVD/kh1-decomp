/* wm.x func_00f3f478: matched by hand. */
#include "ovl.h"

void func_001bef40(char *, void *, ...);
void func_001bb7c8(char *, s32);
void func_00162058(s32);
void func_00162070(s32, s32, s32, s32);
void func_001623d0(s32, s32);
extern char *D_00F9B230[];
extern char D_00FB71F8[], D_00FB7200[], D_00FB7210[];
s32 func_00f3f478(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    char path[64];
    char name[32];
    char **p = &D_00F9B230[arg0];
    if (*p != 0) {
    func_001bef40(name, *p, D_00FB71F8);
    func_001bef40(path, D_00FB7200, name);
    func_001bb7c8(path, arg1);
    func_001bef40(name, *p, D_00FB7210);
    func_001bef40(path, D_00FB7200, name);
    func_001bb7c8(path, arg2);
    func_00162058(arg1);
    func_00162058(arg2);
    func_00162070(arg1, arg3, arg4, arg5);
    func_001623d0(arg2, arg4);
    return 1;
    }
    return 0;
}
