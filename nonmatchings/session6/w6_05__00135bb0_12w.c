/* 12w off (8 bytes short): nostrict. Original ends with bnez v0/move v0,zero/li v0,1 (gcc gives sltiu for every return form tried), and around func_0012ec88 has move a1,s1 before beqz (a0 in beqz slot, a1=sp+64 in jal slot). Tried: ctx f040 above, ret var, duplicated tail, m[5][4]. */
#include "common.h"
typedef union { u64 x; struct { u32 lo; u32 x32:13; u32 b45:1; u32 x46:3; u32 b49:1; u32 hi:14; } b; } F370e;
typedef struct { u8 p0[0x40]; f32 sx, sy, sz; u8 p4c[4]; f32 f50[4]; u8 p60[0xd0-0x60]; f32 fd0[4][4]; u8 p110[0x370-0x110]; F370e f370; } Ob9;
extern f32 D_002BBFA0[4][4];
extern void func_00135b88(Ob9 *, void *);
extern void sceVu0CopyMatrix(f32 (*)[4], f32 (*)[4]);
extern void func_002675a8(f32 *, f32 *);
extern void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern s32 func_0012f040(Ob9 *, s32);
extern void func_0012ec88(Ob9 *, f32 *);
extern s32 func_0024edf0(f32 (*)[4], void *);
s32 func_00135bb0(Ob9 *o) {
    f32 m[4][4];
    f32 v[4];
    u8 buf[128];
    if (o->f370.b.b45 && o->sx * o->sy * o->sz == 0.0f) return 0;
    if (o->f370.b.b49) return 1;
    func_00135b88(o, buf);
    sceVu0CopyMatrix(m, o->fd0);
    func_002675a8(m[3], o->f50);
    m[3][3] = 1.0f;
    sceVu0MulMatrix(m, D_002BBFA0, m);
    if (func_0012f040(o, -1)) func_0012ec88(o, v);
    if (func_0024edf0(m, buf)) return 0;
    return 1;
}
