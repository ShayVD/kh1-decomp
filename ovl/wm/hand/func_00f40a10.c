/* wm.x func_00f40a10: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { u64 btn; s32 flag; } Pad;
Pad *func_001ba488(s32);
void func_001bfac8(void);
void func_00f29810(s32, OvlMtx, OvlMtx *);
s32 func_00f2b7d0(void);
void func_00f309d0(s32);
void func_00f46cb8(s32, s32);
void func_00f7f628(s32, s32);
extern s32 D_00F850A4;
extern s32 D_00F850B0;
extern s32 D_00F850B4;
extern W *D_00F864C0;

void func_00f40a10(void) {
    s32 go = 0;
    s32 f;
    D_00F850A4 = 1;
    func_00f29810(D_00F864C0->s.a, D_00F864C0->m3[0], D_00F864C0->m4);
    while (1) {
        if (go) {
            f = func_001ba488(0)->flag;
            if (f & 1) {
                func_00f309d0(0);
                D_00F850A4 = 0;
                return;
            }
            if (f & 0x4000) {
                D_00F850B0 ^= 1;
                D_00F850B4 ^= 1;
            }
            if (f & 0x100) {
                D_00F850A4 = 0;
                func_00f46cb8(66, -1);
                func_00f309d0(0);
                D_00F850A4 = 0;
                return;
            }
            if (f & 2) func_00f7f628(256, func_00f2b7d0());
        }
        func_001bfac8();
        go = 1;
    }
}
