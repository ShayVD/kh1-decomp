/* wm.x func_00f5bba0: matched by hand (session 141, wwm1 round 17): a CONTEXT_ONLY func_00f5ae10 (and gb func_00f34aa8's v[0..3] store order) above it. A call to a function defined earlier in the file is nothrow, which changes reorg's branch-likely choice (docs/overlays.md, "Branch-likely vs plain branch"). */
#include "ovl.h"
typedef struct { u8 p[4]; u16 kind; u16 fl; u8 q[4]; } Typ5bba0;
typedef struct { u8 pad[0xA4]; u16 ntyp; u8 pad2[0x110 - 0xA6]; Typ5bba0 typ[1]; } W5bba0;
CONTEXT_ONLY void func_00f5ae10(f32 (*a0)[4], s32 a1) {}
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, f32 (*)[4], f32 *, s32);
extern W5bba0 *D_00F9B540;
extern s32 D_00F9B568;

void func_00f5bba0(void) {
    f32 m[4][4];
    f32 s[4];
    s32 i;

    s[0] = -1.0f;
    s[1] = 1.0f;
    s[2] = 1.0f;
    s[3] = 1.0f;
    for (i = 0; i < D_00F9B540->ntyp; i++) {
        switch (D_00F9B540->typ[i].kind - 1) {
        case 44:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(56, 1, m, NULL, D_00F9B568), 6);
            break;
        case 45:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(56, 1, m, s, D_00F9B568), 6);
            break;
        case 46:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(57, 1, m, NULL, D_00F9B568), 6);
            break;
        case 47:
            func_00f5ae10(m, i);
            func_00f5ae98(func_00f68770(57, 1, m, s, D_00F9B568), 6);
            break;
        }
    }
}
