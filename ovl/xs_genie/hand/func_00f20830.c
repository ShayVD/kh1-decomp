/* xs_genie.x func_00f20830: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; OvlVec pos; u8 pad2[0x54]; s32 f74; s32 f78; } Obj;
typedef struct { s32 a; s32 b; } Ent;
typedef struct { s32 cnt; Ent *list; } Tbl;
typedef struct { s32 a; s32 b; s32 pad[2]; } R;
s32 func_00122ff8(s32);
void func_00123030(Obj *, s32, s32);
void func_0012ec60(s32, s32, f32 *);
void func_00130340(Obj *, s32, f32);
void func_00130578(Obj *, s32, f32);
s32 func_00137618(Obj *);
void func_001376e8(Obj *, f32 *);
void func_00157910(Obj *, s32, s32);
f32 func_00176850(void);
CONTEXT_ONLY void func_00f200a0(s32 a) {}
s32 func_00f21820(R *);
s32 func_00f21a98(void);
void func_00f22a58(s32, R *);
extern Tbl D_00FC0D60[];
extern s32 D_00FC0D90;
extern s32 D_00F22E94;
void func_00f20830(Obj *o) {
    R r;
    OvlVec t;
    s32 n;
    Tbl *tb;
    Ent *e;
    if (func_00122ff8(o->f74)) {
        func_0012ec60(o->f74, o->f78, t);
        PlatVu0SubVector(t, t, o->pos);
        func_001376e8(o, t);
    }
    if (func_00137618(o) == 0) {
        return;
    }
    if (func_00f21820(&r)) {
        n = 0;
        if (D_00FC0D90 != 0) {
            n = 3;
            if (func_00f21a98()) {
                n = (D_00FC0D90 & 1) ? 2 : 1;
            }
        }
        e = &D_00FC0D60[n].list[(s32)(func_00176850() * D_00FC0D60[n].cnt)];
        func_00130340(o, e->a | 0x1000000, 4.0f);
        func_00130578(o, 0x40000000, 0.0f);
        func_00157910(o, e->b, 3);
        if (func_00122ff8(r.a)) {
            func_00123030(o, r.a, r.b);
        } else {
            func_00123030(o, 0, 0);
        }
        func_00f22a58(D_00F22E94, &r);
        D_00FC0D90++;
    } else {
        func_00123030(o, 0, 0);
        func_00f200a0(0);
    }
}
