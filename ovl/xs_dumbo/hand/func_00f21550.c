/* xs_dumbo.x func_00f21550: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; f32 r1; f32 r2; s32 pad; OvlVec c; } Q;
typedef struct { s32 pad[3]; s32 fC; s32 pad2[4]; } R;
typedef struct { u8 pad[0x30]; OvlVec p; } Node;
typedef struct { u8 pad[0x10]; OvlVec pos; } Obj;
typedef struct { u8 pad[0x20]; s32 f20; } Tgt;
typedef struct { f32 f0; s32 f4; s32 f8; f32 *fC; } G;
typedef struct { s32 f0; s32 f4; } H;
s32 func_00123158(s32, s32);
s32 func_0015bd78(Q *, s32, R *);
Tgt *func_001354b8(Obj *, s32);
void func_00f21460(s32, f32 *, f32);
extern f32 D_00F2BAB4;
extern G D_00F44A90;
extern Obj *D_00F2320C;
extern s32 D_00F23200;
extern H D_002E31B0;
void func_00f21550(Node *nd, s32 arg1, s32 cnt) {
    Q q;
    R res;
    s32 i;
    s32 e;
    Tgt *t;
    q.f0 = 1;
    for (i = 0; i < cnt; i++, nd++) {
        q.r1 = q.r2 = D_00F2BAB4 * D_00F44A90.fC[i];
        PlatVu0CopyVector(q.c, nd->p);
        PlatVu0CopyVector(D_00F2320C->pos, nd->p);
        e = 0;
        while ((e = func_00123158(D_00F23200, e)) != 0) {
            if (func_0015bd78(&q, e, &res)) {
                t = func_001354b8(D_00F2320C, e);
                if (t != 0) {
                    func_00f21460(e, q.c, q.r1);
                    if (D_002E31B0.f0 == e) {
                        t->f20 = D_002E31B0.f4 + 100;
                    } else {
                        t->f20 = res.fC;
                    }
                }
            }
        }
    }
}
