/* wm.x func_00f452f8: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; s32 c; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x55C]; } W;
typedef struct { s16 a; s16 b; } E;
typedef struct { u8 pad[6]; u16 flag; } K;
s32 func_00f62b90(s32);
K *func_00f62b98(s32, s32);
s32 func_00f62c60(s32, s32);
extern W *D_00F864C0;
extern E D_00F8AA88[];

void func_00f452f8(s32 arg0, s32 arg1) {
    s32 a = D_00F8AA88[arg0].a;
    s32 b = D_00F8AA88[arg0].b;
    s32 i, n;
    K *k;
    if (a < 0 || b < 0) return;
    if (D_00F864C0->s.c != a) return;
    n = func_00f62b90(D_00F864C0->s.id);
    for (i = 0; i < n; i++) {
        if (b == func_00f62c60(i, D_00F864C0->s.id)) {
            k = func_00f62b98(i, D_00F864C0->s.id);
            if (arg1 != 0) {
                if (k->flag & 1) k->flag ^= 1;
            } else {
                if (!(k->flag & 1)) k->flag |= 1;
            }
        }
    }
}
