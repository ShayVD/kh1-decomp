#include "common.h"
/* func_0010cf38: matches with -fno-gcse -fno-optimize-sibling-calls (session 7 flag sweep; the function has no tail call, the flag only changes how the return paths are laid out). */
typedef struct {
    u16 x0; u16 x2; u8 pad4[4]; f32 x8; u8 padc[0x1810 - 0xc]; f32 t[16]; f32 v[16];
} Seq;
extern void func_0010cd40(Seq *, void *);
extern s32 func_0010cf20(void);
extern void func_0010ced0(void *, s32);

void func_0010cf38(Seq *o, void *a) {
    s32 i, n;
    f32 v;

    o->x8 += 2.0f;
    if (o->x2 == 0) return;
    n = o->x2;
    for (i = 0; i < n; i++) {
        f32 *p = &o->t[i];
        if (p[0] == 0.0f) continue;
        if (!(p[0] <= o->x8)) continue;
        o->x8 = p[0];
        func_0010cd40(o, a);
        if (func_0010cf20() && p[16] < 1000000.0f) goto clr;
        v = p[16];
        if (v == 123456.0f) return;
        if (v >= 2000000.0f) {
            func_0010ced0(a, o->x0);
            v = p[16] - 2000000.0f;
        } else if (v >= 1000000.0f) {
            v -= 1000000.0f;
        }
        if (v <= 0.0f) {
clr:
            p[0] = 0.0f;
        } else {
            p[16] -= 1.0f;
        }
        return;
    }
}


