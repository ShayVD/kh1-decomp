/* wm.x func_00f3f8d0: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 a; s32 b; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx m0; OvlMtx m1; OvlMtx m2; OvlMtx m3[16]; OvlMtx m4[2]; Sub s; u8 pad2[0x590 - 0x558]; } W;
void func_001bef40(OvlMtx, void *, void *);
void func_001bb7c8(OvlMtx, s32);
void func_00f64b88(s32);
void func_00f65a68(s32);
void func_00f29810(s32, OvlMtx, void *);
extern W D_00F86500[];
extern s32 D_00FB7228;
extern s32 D_00FB7230;

void func_00f3f8d0(s32 arg0, void *arg1) {
    OvlMtx m;
    Sub *s; /* built as (i*0x590+0x540) then +base, matching the original association */
    func_001bef40(m, arg1, &D_00FB7228);
    s = (Sub *)(arg0 * 0x590 + 0x540); s = (Sub *)((u8 *)s + (s32)D_00F86500);
    func_001bb7c8(m, s->a);
    func_00f64b88(s->a);
    func_001bef40(m, arg1, &D_00FB7230);
    func_001bb7c8(m, s->b);
    func_00f65a68(s->b);
    func_00f29810(s->a, D_00F86500[arg0].m3[0], D_00F86500[arg0].m4);
    PlatVu0UnitMatrix(D_00F86500[arg0].m2);
}
