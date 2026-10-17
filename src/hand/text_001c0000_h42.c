#include "common.h"

/* Script VM context (same layout as h15/h16): pc at +0x17c, sp at +0x180,
   value stack at +0x184, flags at +0x328. */
typedef struct {
    s32 x0;
    s32 x4;
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

typedef struct { u8 pad[0x7c]; s32 a[1]; u8 pad80[0x2f8-0x80]; s32 b[8]; } P;
P *func_001e98d0(s32, s32);
s32 func_001c1980(P *, s32, s32);

s32 func_001c19f8(VM *vm, s32 k) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    P *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->flags >> 5) & 1, a);
    func_001c1980(p, b, p->a[k]);
    return 2;
}

s32 func_001c1aa8(VM *vm) {
    s32 a = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    P *p;
    if (b < 0) b = 0;
    else if (b >= 8) b = 7;
    p = func_001e98d0((s32)(vm->flags >> 5) & 1, a);
    if (p->b[b] != -1) {
        vm->pc -= 2;
        return 4;
    }
    return 2;
}

s32 func_001c1ce8(s32, s32);
s32 func_001c1cf8(s32, s32);
extern s32 (*D_0037A198[])(VM *, s32);

void func_001c1d20(VM *vm, s32 k) {
    s32 saved = vm->pc;
    s32 op, arg, r;
    vm->pc = vm->lbl[k];
    for (;;) {
        op = func_001c1ce8(vm->code, vm->pc);
        arg = func_001c1cf8(vm->code, vm->pc);
        if (op == 5) break;
        r = D_0037A198[op](vm, arg);
        if (r & 2) vm->pc++;
        if (r & 4) goto out;
        if (r & 8) goto out;
    }
out:
    vm->pc = saved;
}
typedef struct { s32 id; u8 pad[12]; f32 c[4]; f32 s[4]; } Box;
typedef struct {
    u8 pad0[0x3178];
    s32 nbox;
    u8 pad317c[4];
    Box box[1];
} Big;
extern Big D_00389C90;
typedef struct { u8 pad[16]; f32 pos[4]; } Obj;
extern Obj *D_002E26A0;
void func_002675a8(f32 *, f32 *);
s32 func_001c1e30(void) {
    f32 mn[4], mx[4], p[4];
    s32 i;
    if (D_002E26A0 == 0) return 0;
    func_002675a8(p, D_002E26A0->pos);
    for (i = 0; i < D_00389C90.nbox; i++) {
        mn[0] = D_00389C90.box[i].c[0] - D_00389C90.box[i].s[0] * 0.5f;
        mn[1] = D_00389C90.box[i].c[1] - D_00389C90.box[i].s[1] * 0.5f;
        mn[2] = D_00389C90.box[i].c[2] - D_00389C90.box[i].s[2] * 0.5f;
        mx[0] = D_00389C90.box[i].c[0] + D_00389C90.box[i].s[0] * 0.5f;
        mx[1] = D_00389C90.box[i].c[1] + D_00389C90.box[i].s[1] * 0.5f;
        mx[2] = D_00389C90.box[i].c[2] + D_00389C90.box[i].s[2] * 0.5f;
        if (mn[0] <= p[0] && p[0] <= mx[0] && mn[1] <= p[1] && p[1] <= mx[1] && mn[2] <= p[2] && p[2] <= mx[2])
            return D_00389C90.box[i].id;
    }
    return 0;
}
