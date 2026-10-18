/* 001c95f8 15w, hand (same count as w6 s9 draft, but sibling style from matched func_001c8878 in src/hand/text_001c0000_h42.c: no x/y/z/m locals, `D_003C5510.p70.x = vm->stk[vm->sp - 2];` etc, CamOut type from h42 + s32 x2c). Order d, x2c, t0, p70 x/y/z, sp -= 5, dur0. Left: the three p70 cvt loads get f1/f2/f3 in x,y,z order, orig z f1, x f2, y f3. Finding (r2_3): sched2 always moves the source-last load (the one on the t0 base) first, so the final order says nothing about sched1; local-alloc needs z born first in sched1 (or a shorter life) while z stays source-last. In the sibling, z has one insn less of life because the sp store and other work sit between x/y and z there; here the x2c store forces an sp reload, so all three loads issue back to back (LUID order) with equal lives (5). All 12 load-order x sp/dur0 permutations, with or without locals, stay at 15 (the source-last load always gets the t0 base and goes first in the final code). */
#include "common.h"
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
    D_003C5510.u.s.dur0 = d;
    return 2;
}
