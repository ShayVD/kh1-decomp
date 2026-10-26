/* wm.x func_00f2f8e0: matched by hand. */
#include "ovl.h"

#include "ovl.h"

typedef struct { u8 a; u8 pad[13]; u16 h; } P;
void func_001bfac8(void);
P *func_00f2cae8(void);
void func_00f2d480(void);
s32 func_00f680c0(s32);
void func_00f68ab0(s32);
extern f32 D_002BBDEC;
extern s32 D_00F8C1EC;
extern s32 D_00FBB5C0;
extern f32 D_00FBBA64;

void func_00f2f8e0(void) {
    P *p;
    f32 f;
    s32 i, n, h;
    p = func_00f2cae8();
    if (p == 0) return;
    f = 80.0f / D_002BBDEC;
    for (i = 0; i < (s32)f && D_00FBB5C0 == 0 && D_00F8C1EC != 0 && p->a != 0; i++) {
        D_00FBBA64 = -(f32)i / f + 1.0f;
        func_001bfac8();
    }
    if (p->a == 0) return;
    D_00FBBA64 = 0.0f;
    h = p->h;
    func_00f68ab0(h);
    if (D_00F8C1EC != 0) func_00f2d480();
    while (func_00f680c0(h) != 0) func_001bfac8();
    p->a = 0;
    D_00F8C1EC = 0;
}
