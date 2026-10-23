/* src/vm/script_vm.c's functions that need -fno-strict-aliasing (flag mode
 * nostrict; docs/modules.md "Flags"), in address order. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"
#include "vm/vm_mgr.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_003B4DA0.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002C5958.h"

extern VmMgr D_00389C90;
extern s32 D_0039A570, D_003A7980, D_003B4D90, D_003C21A0;
extern s32 D_002BCDE4, D_002BCC90;
extern u8 D_003DE570[];

void *func_0011ef10(s32, void *);

/* func_001c48c8's view of what p[11] points at */
typedef struct {
    u8 pad0[4];
    s32 x4;
    u8 pad8[0x3c];
    s32 x44;
    u8 pad48[0x24];
    s32 x6c;
} Q48;

/* Jump VM `v` to `pc` at return level `lvl`: a lower level saves the current
 * pc on the return stack first. */
s32 func_001c1980(VmRec *v, s32 lvl, s32 pc) {
    if (lvl < v->rsp) {
        v->x2f4 = 0;
        v->ret[v->rsp] = v->pc;
        v->rsp = lvl;
        v->pc = pc;
        v->fl.x &= ~4;
    } else if (lvl == v->rsp) {
        v->pc = pc;
        v->x2f4 = 0;
        v->fl.x &= ~4;
    }
    v->ret[lvl] = pc;
    return 1;
}

void func_001c3770(s8 *p, s32 a1) {
    s32 done = 0;
    VmRec *e, *e2;
    s32 h0;
    s32 *cnt;
    s32 i, j, k;
    s32 op, arg, r;
    D_00389C90.f3070.x &= ~0x10000000000ULL;
    h0 = ((s32 *)p)[0];
    { u32 n = (a1 + (((s32 *)p)[1] + h0)) * 4; p += *(s32 *)((u32)p + n + 16); }
    p += 12;
    if (a1 == 0) { e = D_003A7990; cnt = &D_003B4D90; }
    else { e = D_003B4DA0; cnt = &D_003C21A0; }
    *cnt = *p++;
    for (i = 0; i < *cnt; i++, e++) {
        e->x0 = 0;
        e->obj = 0;
        e->code = p + 4;
        e->n = *p;
        e->pc = 0;
        e->sp = -1;
        e->x78 = 0;
        e->x2f0 = 0;
        e->rsp = 7;
        for (j = 7; j >= 0; j--) e->ret[j] = -1;
        p += 4;
        e->ret[7] = e->pc;
        e->fl.b.b0 = 0; e2 = e; e2->fl.b.b1 = 0; e->fl.b.b2 = 0; e->fl.b.b3 = 0; e->fl.b.b4 = 0;
        e->fl.b.b5 = 1;
        e->fl.b.b6 = 0; e->fl.b.b7 = 0; e2->fl.b.b8 = 0; e2->fl.b.b9 = 0;
        k = 0;
        for (j = 0; j < e2->n; j++) {
            e2->lbl[j] = k;
            while (p[3] != 5) { p += 4; k++; }
            p += 4; k++;
        }
    }
    if (a1 == 0) { e = D_003A7990; cnt = &D_003B4D90; }
    else { e = D_003B4DA0; cnt = &D_003C21A0; }
    for (i = 0; i < *cnt; i++, e++) {
        e->pc = e->lbl[0];
        while (1) {
            op = func_001c1ce8(e->code, e->pc);
            arg = func_001c1cf8(e->code, e->pc);
            if (op == 5) break;
            r = D_0037A198[op](e, arg);
            if (r & 2) e->pc++;
            if (r & 8) {
                done = 1;
                D_002C5958 &= ~8;
                D_002C5958 &= ~4;
                break;
            }
        }
        e->x78 = 1;
        e->pc = e->lbl[1];
    }
    if (done == 0) {
        if (!((D_00389C90.f3070.x >> 42) & 1)) {
            func_0011ef10(50001, func_001c3408);
            D_00389C90.f3070.x |= 0x40000000000ULL;
        }
        D_00389C90.x3038 = a1;
    } else {
        D_00389C90.x3038 = 0;
    }
}

void func_001c4808(s32 a, u32 b) {
    if (((u32)D_0037A378 >> 1) & 1) return;
    if ((s32)(D_00389C90.f3070.x >> 40) & 1) return;
    if ((s32)(D_00389C90.f3078.x >> 7) & 1) return;
    D_00389C90.x303c = a;
    if (b == 0) return;
    if (b < 100) {
        if (D_00389C90.x3034 != b) {
            func_001c2ec8((s8 *)D_002BCDE4, b);
            D_00389C90.f3078.x |= 64;
        }
    } else if (D_00389C90.x3038 == 0) {
        func_001c3770((s8 *)D_002BCC90, b - 100);
    }
}

void func_001c48c8(s32 id, u32 kind, s32 *p) {
    VmRec *vm;
    VmRec *e;
    s32 n, i;
    if (!((s32)(D_00389C90.f3070.x >> 59) & 1)) return;
    if ((((u32)D_0037A378) >> 2) & 1) return;
    if (D_002C5958 & 0x12000) return;
    if (D_00389C90.x3034 == 0) {
        vm = D_0038D170;
        n = D_0039A570;
    } else {
        n = D_003A7980;
        vm = D_0039A580;
    }
    for (i = 0; i < n; i++) {
        if (vm[i].x0 == id) break;
    }
    if (i >= n && kind != 5) return;
    switch (kind) {
    case 0:
        e = &vm[i];
        if (func_001c1ce8(e->code, e->lbl[5]) == 5) return;
        if ((u32)e->pc >= (u32)e->lbl[5] && (u32)e->pc < (u32)e->lbl[6]) return;
        D_002C5958 |= 0x1000;
        D_00389C90.f3078.x |= 0x800;
        vm->stk[++vm->sp] = 3;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 5); return;

    case 1:
        if (func_001c1ce8(vm[i].code, vm[i].lbl[6]) == 5) return;
        vm->stk[++vm->sp] = 2;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 6); return;

    case 2: {
        Q48 *q;
        e = &vm[i];
        if (func_001c1ce8(e->code, e->lbl[4]) == 5) return;
        q = (Q48 *)p[11];
        vm->stk[++vm->sp] = 2;
        vm->stk[++vm->sp] = i;
        e->x31c = q->x6c;
        e->x320 = q->x4;
        e->x324 = q->x44;
        func_001c19f8(vm, 4); return;

    }
    case 3:
        if (func_001c1ce8(vm[i].code, vm[i].lbl[7]) == 5) return;
        vm->stk[++vm->sp] = 4;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 7); return;

    case 4:
        if (func_001c1ce8(vm[i].code, vm[i].lbl[3]) == 5) return;
        vm->stk[++vm->sp] = 3;
        vm->stk[++vm->sp] = i;
        func_001c19f8(vm, 3); return;

    case 5:
        {
        s32 c, d;
        D_00389C90.x3158[0] = p[0];
        D_00389C90.x3158[1] = p[1];
        c = p[2];
        D_00389C90.x3158[2] = c;
        d = p[3];
        D_00389C90.x3158[3] = d;
        D_00389C90.x3158[4] = p[4];
        if (c == 5) { func_001c4198((s8 *)D_003DE570, d); return; }
        func_001c4198((s8 *)D_003DE570, 0);
        }

    }
}
