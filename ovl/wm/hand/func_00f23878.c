/* wm.x func_00f23878: matched by hand. */
#include "ovl.h"

typedef struct { s16 a; s16 b; u8 pad[16]; } T23878;
extern s32 D_00FBAA68;
extern s32 D_00FBAA6C;
extern void *D_00FBAA60;
extern void *D_00FBAA64;
extern T23878 D_00F874F8[34];
extern u64 D_00F87950[34];
extern T23878 D_00F877F8[9];
extern u64 D_00F87A68[9];
extern T23878 D_00F877D0;
extern u64 D_00F87A60;
extern char D_00FB66C0[];
extern char D_00FB66D8[];
extern char D_00FB66F0[];
s32 func_001bb500(s32, s32);
s32 func_001bb7c8(char *, s32);
void func_00f65a68(s32);
s32 func_00f65b48(s32, s32, s32);
u64 func_00f65bb8(s32, s32, s32, s32);
s32 func_001bb370(void);

void func_00f23878(void) {
    s32 i;
    s32 a;
    T23878 *e;
    D_00FBAA68 = func_001bb500(0x80000, 128);
    func_001bb7c8(D_00FB66C0, D_00FBAA68);
    func_00f65a68(D_00FBAA68);
    for (i = 0; i < 34; i++) {
        e = &D_00F874F8[i];
        a = e->a;
        D_00F87950[i] = func_00f65bb8(func_00f65b48(0x3600, D_00FBAA68, a), D_00FBAA68, a, e->b);
    }
    D_00FBAA60 = D_00F874F8;
    D_00FBAA64 = D_00F87950;
    D_00FBAA6C = func_001bb500(0x48000, 128);
    if (func_001bb370()) {
        func_001bb7c8(D_00FB66D8, D_00FBAA6C);
        func_00f65a68(D_00FBAA6C);
        for (i = 0; i < 9; i++) {
            u64 *o = &D_00F87A68[i];
            e = &D_00F877F8[i];
            a = e->a;
            *o = func_00f65bb8(func_00f65b48(0x2600, D_00FBAA6C, a), D_00FBAA6C, a, e->b);
        }
    } else {
        u64 *q = &D_00F87A60;
        func_001bb7c8(D_00FB66F0, D_00FBAA6C);
        func_00f65a68(D_00FBAA6C);
        e = &D_00F877D0;
        a = e->a;
        *q = func_00f65bb8(func_00f65b48(0x2600, D_00FBAA6C, a), D_00FBAA6C, a, e->b);
    }
}
