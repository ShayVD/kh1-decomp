/* wm.x func_00f35980: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
typedef struct { f32 f0; u8 kind; u8 pad; u16 flag; } K;
typedef struct { u16 a; u16 b; } C;
typedef struct { u8 pad[4]; s32 k; u8 pad2[0x14]; C *c; } E;
s32 func_00f3b480(void);
E *func_00f3b460(s32);
K *func_00f3f260(s32, s32);
extern W *D_00F864C0;
s32 func_00f35980(f32 x) {
    s32 i;
    E *e;
    K *k;
    f32 d;
    for (i = 0; i < func_00f3b480(); i++) {
        e = func_00f3b460(i);
        k = func_00f3f260(e->k, D_00F864C0->s.id);
        if (k->kind >= 2 && k->kind < 4 && !(k->flag & 1) && e->c->b == 5) {
            d = k->f0 - x;
            if (d > -500.0f && d < 500.0f) return 1;
        }
    }
    return 0;
}
