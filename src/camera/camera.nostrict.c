/* The event camera: the script functions that need -fno-strict-aliasing
 * (docs/modules.md "Flags"; the rest of the module is camera.c):
 *
 * - func_001c6d08, func_001c71e8, func_001c7700, func_001c7c18: load
 *   camera path k of the script file into D_0037A380 and play it, with
 *   VmMgr.x3058 = 0-3 the objects func_001c5168 follows;
 * - func_001c8c90, func_001c8d98, func_001c9ca8, func_001ca060: start the
 *   linear / curved tweens of channels 2 and 3 (f120, f124). */
#include "common.h"
#include "camera/camera.h"
#include "vm/vm_mgr.h"
#include "vm/vm_find.h"
#include "data/types/vm_rec.h"
#include "data/pieces/D_0037A380.h"

extern VmMgr D_00389C90;
extern CamState D_003C5510;
extern s32 D_003C5500;

typedef Elem_37A380 Elem;
void func_0011ef10(s32, void *);

/* Shared loader body inlined into the four functions below. The split tE
   load and the "p += 2; p += 2;" step are needed for the match (loop insn
   count / sched1 order). */
static inline void inl_load(u32 k) {
    u8 *p;
    s32 i;
    Elem *e;
    f32 tE;
    p = (u8 *)D_00389C90.x3040 + D_00389C90.x304c[k];
    D_0037A380.scn.n = *(s32 *)p;
    p += 4;
    for (i = 0; i < D_0037A380.scn.n; i++) {
        e = &D_0037A380.scn.arr[i];
        __builtin_memcpy(&e->a, p, 4); p += 4;
        __builtin_memcpy(&e->b, p, 4); p += 4;
        e->c = *(s32 *)p; p += 4;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[0], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[1], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[2], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[3], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[4], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[5], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[6], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[7], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[8], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[9], p, 16); p += 16;
        __builtin_memcpy(&D_0037A380.scn.arr[i].m[10], p, 16); p += 16;
        D_0037A380.scn.arr[i].f[0] = *(f32 *)p; p += 2; p += 2;
        D_0037A380.scn.arr[i].f[1] = *(f32 *)p; p += 4;
        D_0037A380.scn.arr[i].f[2] = *(f32 *)p; p += 4;
        D_0037A380.scn.arr[i].f[3] = *(f32 *)p; p += 4;
        D_0037A380.scn.arr[i].f[4] = *(f32 *)p; p += 4;
        D_0037A380.scn.arr[i].f[5] = *(f32 *)p; p += 4;
        if (i == 0) {
            D_0037A380.scn.arr[i].prev = 0;
            D_0037A380.scn.arr[i].next = 0;
        } else {
            D_0037A380.scn.arr[i - 1].next = e;
            e->next = 0;
            e->prev = &D_0037A380.scn.arr[i - 1];
        }
    }
    D_0037A380.scn.x0 = D_0037A380.scn.arr[0].c;
    D_0037A380.scn.first = &D_0037A380.scn.arr[0];
    D_0037A380.scn.last = &D_0037A380.scn.arr[D_0037A380.scn.n - 1];
    tE = D_0037A380.scn.arr[0].f[5];
    D_003C5500 = D_0037A380.scn.n + 1;
    __builtin_memcpy(&D_0037A380.scn.q10, &D_0037A380.scn.arr[0].m[5], 16);
    __builtin_memcpy(&D_0037A380.scn.q20, &D_0037A380.scn.arr[0].m[6], 16);
    __builtin_memcpy(&D_0037A380.scn.q30, &D_0037A380.scn.arr[0].m[7], 16);
    __builtin_memcpy(&D_0037A380.scn.q40, &D_0037A380.scn.arr[0].m[10], 16);
    D_0037A380.scn.x60 = D_0037A380.scn.arr[0].f[2];
    D_0037A380.scn.xE0F4 = tE;
    D_0037A380.scn.q50[0] = 0.0f;
    D_0037A380.scn.q50[1] = 0.0f;
    D_0037A380.scn.q50[2] = 0.0f;
    D_0037A380.scn.q50[3] = 0.0f;
    func_001c53c8(D_0037A380.scn.x0);
    __builtin_memcpy(D_003C5510.pos, &D_0037A380.scn.q10, 16);
    __builtin_memcpy(D_003C5510.rot, &D_0037A380.scn.q40, 16);
    __builtin_memcpy(&D_003C5510.rx, &D_0037A380.scn.q50, 16);
    __builtin_memcpy(D_003C5510.v110, &D_0037A380.scn.q30, 16);
    __builtin_memcpy(D_003C5510.v100, &D_0037A380.scn.q20, 16);
    D_003C5510.f120 = D_0037A380.scn.x60;
    D_003C5510.f124 = D_0037A380.scn.xE0F4;
    func_001c6a20();
    func_0011ef10(99999, func_001c5b88);
    D_00389C90.f3070.x |= 0x2000000000ULL;
}

/* Play camera path k (VmMgr.x3048 of them). */
s32 func_001c6d08(VmRec *vm) {
    u32 k = vm->stk[vm->sp];
    if (k < D_00389C90.x3048) {
        D_00389C90.x3058 = 0;
        inl_load(k);
    }
    vm->sp--;
    return 2;
}

/* ... moving with VM b's object. */
s32 func_001c71e8(VmRec *vm) {
    u32 k = vm->stk[vm->sp - 1];
    VmRec *r = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (k < D_00389C90.x3048) {
        D_00389C90.x3058 = 1;
        if (r) D_00389C90.x306c = (s32)r->obj;
        inl_load(k);
    }
    vm->sp -= 2;
    return 2;
}

/* ... moving and turning with VM b's object. */
s32 func_001c7700(VmRec *vm) {
    u32 k = vm->stk[vm->sp - 1];
    VmRec *r = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (k < D_00389C90.x3048) {
        D_00389C90.x3058 = 2;
        if (r) D_00389C90.x306c = (s32)r->obj;
        inl_load(k);
    }
    vm->sp -= 2;
    return 2;
}

/* ... between the objects of VMs b and c. */
s32 func_001c7c18(VmRec *vm) {
    u32 k = vm->stk[vm->sp - 2];
    if (k < D_00389C90.x3048) {
        VmRec *r;
        D_00389C90.x3058 = 3;
        r = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp - 1]);
        if (r) D_00389C90.x306c = (s32)r->obj;
        r = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
        if (r) D_00389C90.f3070.i[0] = (s32)r->obj;
        inl_load(k);
    }
    vm->sp -= 3;
    return 2;
}

/* Start channel 2, linear: f120 to v in n frames. */
s32 func_001c8c90(VmRec *v) {
    CamState *p;
    s32 sp;
    f32 a, b;
    func_001c6890();
    p = &D_003C5510;
    p->fl.x |= 4;
    p->p0[2][0] = p->f120;
    sp = v->sp;
    p->t[2] = 0.0f;
    a = v->stk[sp - 1];
    b = v->stk[sp];
    v->sp = sp - 2;
    p->p1[2][0] = b;
    p->fl.s.dur[2] = a * 2.0f;
    return 2;
}

/* Start channel 3, linear: f124 to v in n frames. */
s32 func_001c8d98(VmRec *v) {
    CamState *p;
    s32 sp;
    f32 a, b;
    func_001c6890();
    p = &D_003C5510;
    p->fl.x |= 8;
    p->p0[2][1] = p->f124;
    sp = v->sp;
    p->t[3] = 0.0f;
    a = v->stk[sp - 1];
    b = v->stk[sp];
    v->sp = sp - 2;
    p->p1[2][1] = b;
    p->fl.s.dur[3] = a * 2.0f;
    return 2;
}

/* Start channel 2, curved: f120 to v, mode, in n frames. */
s32 func_001c9ca8(VmRec *v) {
    CamState *p;
    s32 sp, m;
    f32 d, e;
    func_001c6890();
    p = &D_003C5510;
    p->fl.x |= 64;
    p->p0[2][0] = p->f120;
    sp = v->sp;
    p->t[2] = 0.0f;
    m = v->stk[sp - 1];
    d = (f32)v->stk[sp - 2] * 2.0f;
    p->mode[2] = m;
    e = v->stk[v->sp];
    v->sp -= 3;
    p->fl.s.dur[2] = d;
    p->p1[2][0] = e;
    return 2;
}

/* Start channel 3, curved: f124 to v, mode, in n frames (t[3] is not
 * reset, as in the original). */
s32 func_001ca060(VmRec *v) {
    CamState *p;
    s32 sp, m;
    f32 d, e;
    func_001c6890();
    p = &D_003C5510;
    p->fl.x |= 128;
    p->p0[2][1] = p->f124;
    sp = v->sp;
    m = v->stk[sp - 1];
    d = (f32)v->stk[sp - 2] * 2.0f;
    p->mode[3] = m;
    e = v->stk[v->sp];
    v->sp -= 3;
    p->fl.s.dur[3] = d;
    p->p1[2][1] = e;
    return 2;
}
