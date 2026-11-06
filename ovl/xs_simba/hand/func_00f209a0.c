/* xs_simba.x func_00f209a0: matched by hand. */
#include "ovl.h"

typedef struct { s32 act; s32 id; s32 pad; } Ent;
typedef struct { u8 pad[0x20]; s32 f20; } Obj;
s32 func_00122ff8(s32);
#ifdef KH1_PS2
void func_0012ec60(s32, s32, OvlVec);
#else /* the definition returns f32: an x86 caller that drops it unbalances the x87 stack */
f32 func_0012ec60(s32, s32, OvlVec);
#endif
s32 func_00147ed8(void *, s32, s32, OvlVec);
Obj *func_001354b8(s32, s32);
void func_00f20188(void);
void func_0014aab0(s32);
extern f32 D_002BBDFC;
extern void *D_00F21C44;
extern Ent D_00FA6A9C[];
extern s32 D_00FA6F18;
extern s32 D_00FA6F1C;
extern s32 D_00FA6F20;
extern f32 D_00FA6F24;
extern s32 D_00FA6F28;
s32 func_00f209a0(void) {
    OvlVec v;
    Ent *e;
    Obj *o;
    f32 *t = &D_00FA6F24;
    s32 *c;
    *t -= D_002BBDFC;
    if (*t > 0.0f) {
        return 0;
    }
    *t = 8.0f;
    e = &D_00FA6A9C[D_00FA6F1C];
    if (func_00122ff8(e->act) != 0) {
        func_0012ec60(e->act, e->id, v);
        func_00147ed8(D_00F21C44, D_00FA6F20, 20000, v);
        o = func_001354b8(D_00FA6F28, e->act);
        if (o != 0) {
            o->f20 = e->id;
        }
    }
    c = &D_00FA6F1C;
    (*c)++;
    if (*c >= D_00FA6F18) {
        func_00f20188();
        func_0014aab0(D_00FA6F28);
        return 4;
    }
    return 0;
}
