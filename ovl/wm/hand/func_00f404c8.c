/* wm.x func_00f404c8: matched by hand. */
#include "ovl.h"

typedef struct { s32 id; s32 pad[2]; f32 val; s32 pad2; s32 dir; } Sub;
typedef struct { OvlMtx a; OvlMtx b; OvlMtx c; u8 pad[0x540 - 0xC0]; Sub s; u8 pad2[0x590 - 0x558]; } W;
f32 func_00f2bed0(s32);
void func_00f405d8(s32, OvlMtx, OvlMtx);
f32 func_00f62b60(s32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
f32 func_00f630c0(f32, f32, s32);
#else
f32 func_00f630c0(s32, f32, f32);
static __inline__ f32 ee_00f630c0(f32 x0, f32 x1, s32 x2) { return func_00f630c0(x2, x0, x1); }
#undef func_00f630c0
#define func_00f630c0 ee_00f630c0
#endif
extern s32 D_00F850A4;
extern W D_00F86500[];

s32 func_00f404c8(s32 arg0, s32 arg1) {
    f32 d;
    Sub *s; /* built as (i*0x590+0x540) then +base, matching the original association */
    func_00f405d8(arg0, D_00F86500[arg0].a, D_00F86500[arg0].b);
    PlatVu0UnitMatrix(D_00F86500[arg0].c);
    if (arg1 != 0) return 0;
    if (D_00F850A4 != 0) return 0;
    d = func_00f2bed0(-1) * 100.0f;
    if (d > 0.0f) {
        if (D_00F86500[arg0].s.dir == 0) {
            s = (Sub *)(arg0 * 0x590 + 0x540); s = (Sub *)((u8 *)s + (s32)D_00F86500);
            s->val = func_00f630c0(s->val, d, s->id);
            if (func_00f62b60(s->id) < s->val) return 1;
        } else {
            s = (Sub *)(arg0 * 0x590 + 0x540); s = (Sub *)((u8 *)s + (s32)D_00F86500);
            s->val = func_00f630c0(s->val, -d, s->id);
            if (s->val < 0.0f) return 1;
        }
    }
    return 0;
}
