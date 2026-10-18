#include "common.h"
/* func_001c95f8 (s11w1, hand strict, no context): from s9 r2_3 (15w, sibling style of func_001c8878). dur0 (offset 4, inside the u64 flags word) is stored through an f32 pointer, `{ f32 *p = &D_003C5510.u.s.dur0; *p = d; }`, so the store has the f32 alias set instead of the union member alias set 0; `((f32 *)&D_003C5510)[1] = d;` matches too. That frees the p70 cvt loads to issue z first in sched1 (z f1, x f2, y f3). */
typedef struct {
    s32 x0;
    void *ent;
    u8 pad8[0x68];
    s32 code;
    u8 pad74[8];
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[92];
    u8 pad2f4[0x34];
    u64 flags;
} VM;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct {
    union {
        u64 flags;
        struct { s32 lo; f32 dur0; f32 dur1; } s;
    } u;
    u8 pad10[8];
    f32 t0;
    f32 t1;
    u8 pad20[0xc];
    s32 x2c;
    u8 pad30[0x10];
    V4 p40;
    V4 p50;
    V4 p60;
    V4 p70;
    V4 p80;
    u8 pad90[0x30];
    V4 v0;
    V4 a, b, c, d, e;
    f32 f50;
    f32 f54;
} CamOut;
extern CamOut D_003C5510;
void func_001c6890(void);
s32 func_001c95f8(VM *vm) {
    f32 d;
    func_001c6890();
    D_003C5510.u.flags |= 0x10;
    D_003C5510.p40.x = D_003C5510.a.x;
    D_003C5510.p40.y = D_003C5510.a.y;
    D_003C5510.p40.z = D_003C5510.a.z;
    d = vm->stk[vm->sp - 4] * 2.0f;
    D_003C5510.x2c = vm->stk[vm->sp - 3];
    D_003C5510.t0 = 0.0f;
    D_003C5510.p70.x = vm->stk[vm->sp - 2];
    D_003C5510.p70.y = vm->stk[vm->sp - 1];
    D_003C5510.p70.z = vm->stk[vm->sp];
    vm->sp -= 5;
    { f32 *p = &D_003C5510.u.s.dur0; *p = d; }
    return 2;
}
