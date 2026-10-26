/* wm.x func_00f3fb28: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
void func_001bef40(char *, void *, void *);
void func_001bb7c8(char *, s32);
void func_00f64b88(s32);
s32 func_00f64c38(s32, s32);
void func_00f62b38(s32);
s32 func_00f64c10(s32);
void func_00f65a68(s32);
void func_00f3f998(s32);
s32 func_00f62b70(s32);
void func_00f20950(s32);
void func_00f3f5a0(s32);
void func_00f442d8(s32);
extern W D_00F86500[];
extern s32 D_00F87020;
extern s32 D_00F87024;
extern s32 D_00F8704C;
extern s32 D_00F87050;
extern char D_00FB7238[];

void func_00f3fb28(s32 arg0, char *arg1) {
    char path[64];
    s32 i, n;
    s32 *p;
    Sub *s; /* built as (i*0x590+0x540) then +base, matching the original association */
    func_001bef40(path, arg1, D_00FB7238);
    func_001bb7c8(path, D_00F87050);
    func_00f64b88(D_00F87050);
    D_00F86500[arg0].s.id = func_00f64c38(0, D_00F87050);
    func_00f62b38(D_00F86500[arg0].s.id);
    D_00F87024 = func_00f64c38(1, D_00F87050);
    func_00f64b88(D_00F87024);
    n = func_00f64c10(D_00F87024);
    for (i = 0; i < n; i++) {
        func_00f65a68(func_00f64c38(i, D_00F87024));
    }
    D_00F87020 = func_00f64c38(2, D_00F87050);
    func_00f64b88(D_00F87020);
    func_00f3f998(D_00F87020);
    p = &D_00F8704C;
    *p = func_00f64c38(3, D_00F87050);
    func_00f64b88(*p);
    { s32 b = (s32)D_00F86500; s = (Sub *)((u8 *)(Sub *)(arg0 * 0x590 + 0x540) + b); }
    if (func_00f62b70(s->id) & 3) {
        func_00f20950((func_00f62b70(s->id) & 3) - 1);
    }
    func_00f3f5a0(s->id);
    func_00f442d8(arg0);
}
