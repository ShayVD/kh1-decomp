/* Opcode 24 of the script VM: the library of script functions
 * (docs/modules.md "Session 32").
 *
 * func_001dcad0 is the handler D_0037A198[24]: it calls entry k of
 * D_003D9FE0 with the VM and returns its result (2 / 4 / 6, as the other
 * handlers).  The table has 763 entries, from 0x001c6d08 to 0x001ec678.
 * 547 of them lie in 0x001cd238-0x001dcad0, numbered mostly in address order
 * (an increasing run of 480), and the last-numbered entry (762,
 * func_001dca48) is the last one before func_001dcad0: the library functions
 * there and this dispatcher are probably one file, and this file is meant to
 * grow upward with them (src/vm/vm_lib.c from 0x001cd238; see "Next module
 * moves").  The other entries belong to other modules: the camera
 * (src/camera/, 32), the message windows (src/msgwin/, 30) and 154 functions
 * after 0x001dcad0 (0x001ddc78-0x001ec678). */
#include "common.h"
#include "vm/vm_obj.h"
#include "data/types/vm_rec.h"
#include "vm/script_vm.h"
#include "vm/vm_mgr.h"
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_002BBE04.h"
#include "data/pieces/D_002BC080.h"
#include "data/pieces/D_002BC098.h"
#include "data/pieces/D_003DABD0.h"
#include "data/data_002B.h"
#include "data/data_002E.h"
#include "data/data_0038.h"
#include "data/data_003C.h"
#include "data/data_003D.h"
#include "data/pieces/D_00388CC4.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_003DABCC.h"
#include "data/pieces/D_003DABD4.h"
#include "data/data_002A.h"
#include "data/data_0039.h"
#include "data/data_003A.h"
#include "data/data_003B.h"
#include "data/data_0042.h"
#include "data/data_0049.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002C5AD0.h"
#include "data/pieces/D_002C6440.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0038D170.h"
#include "data/pieces/D_0039A580.h"
#include "data/pieces/D_003A7990.h"
#include "data/pieces/D_003C3A70.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_00490630.h"
#include "platform/math.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0062.h"


extern VmMgr D_00389C90;

/* A library function: takes the VM, returns the handler result.  The table
 * is declared here, before the library: gcc's cse hashes a symbol by the
 * address of its name, so naming D_003D9FE0 first keeps the dispatcher's
 * code (lw D_003D9FE0(k)) from depending on how many names the functions
 * above it add. */
typedef s32 (*VmLibFn)();
extern VmLibFn D_003D9FE0[];
extern u64 D_0038CD00;
extern VmFx *D_0038CD3C[];

/* The VM (of table k, 0 or 1) whose id is id. */
VmRec *func_001e98d0(s32 k, s32 id);

void func_001c6720(void);
void *func_001559f0(s32, s32);
s32 func_001336b8();
s32 func_0011e340(s32);
s32 func_00106780(s32);
s32 func_00106880(s32);
s32 func_00106978(s32);
s32 func_00106a58(s32);
void func_001ec7c0(s32);
void func_00242bd0(void);

/* ---- 0x001cd238-0x001cdf98 ---- */

void func_001cd238(void) {
    D_003DABD0[0] = func_001559f0(0x34, 4);
    D_003DABD0[1] = func_001559f0(0x38, 4);
}

s32 func_001cd280(VmRec *vm) {
    vm->fl.x |= 4;
    vm->x2f4 = vm->stk[vm->sp] * 2.0f;
    vm->sp--;
    return 6;
}

s32 func_001cd2c0(VmRec *vm) {
    vm->sp = vm->sp - 1;
    return 2;
}

/* func_001cd2d8 is in vm_lib.nofill.c. */

/* func_001cd600 is in vm_lib.nostrict.c. */

s32 func_001cd6b8(VmRec *vm) {
    VmMsg m;
    m.type = 5;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

s32 func_001cd740(void) {
    return 2;
}

s32 func_001cd748(void) {
    D_0037A378 |= 2;
    func_001336b8();
    return 2;
}

s32 func_001cd778(VmRec *vm) {
    VmMsg m;
    m.type = 0;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    func_001c6720();
    D_00389C90.f3078.x |= 0x400;
    return 2;
}

s32 func_001cd7e0(void) {
    return 2;
}

s32 func_001cd7e8(void) {
    if (func_0011e340(0) == 0) {
        D_0037A378 &= ~2;
        return 2;
    }
    return 4;
}

s32 func_001cd830(VmRec *vm) {
    VmMsg m;
    m.type = 1;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    D_00389C90.f3070.x &= ~0x2000000000ULL;
    D_00389C90.f3078.x &= ~0x400ULL;
    return 2;
}

s32 func_001cd8b0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->obj->pos[0];
    return 2;
}

s32 func_001cd8e0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->obj->pos[1];
    return 2;
}

s32 func_001cd910(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->obj->pos[2];
    return 2;
}

s32 func_001cd940(VmRec *vm) {
    VmMsg m;
    m.type = 3;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2];
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    m.v[3] = 1.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cd9e8(VmRec *vm) {
    u64 f = vm->fl.x;
    if ((f & 0xa41) && !((s32)(f >> 4) & 1)) return 4;
    return 2;
}

s32 func_001cda18(VmRec *vm) {
    VmMsg m;
    m.type = 6;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cda60(VmRec *vm) {
    VmMsg m;
    m.type = 7;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdaa8(VmRec *vm) {
    VmMsg m;
    m.type = 8;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdaf0(VmRec *vm) {
    VmMsg m;
    m.type = 9;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdb38(VmRec *vm) {
    VmMsg m;
    m.type = 10;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdb80(VmRec *vm) {
    VmMsg m;
    m.type = 11;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdbc8(VmRec *vm) {
    VmMsg m;
    m.type = 12;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = 0.0f;
    m.v[1] = vm->stk[vm->sp];
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

s32 func_001cdc58(VmRec *vm) {
    VmMsg m;
    m.type = 15;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdcb8(VmRec *vm) {
    VmMsg m;
    m.type = 16;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cdd18(VmRec *vm) {
    func_00106780(vm->stk[vm->sp]);
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001cdd60(VmRec *vm) {
    func_00106880(vm->stk[vm->sp]);
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001cdda8(VmRec *vm) {
    func_00106a58(vm->stk[vm->sp]);
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001cddf0(VmRec *vm) {
    func_00106978(vm->stk[vm->sp]);
    vm->sp = vm->sp - 1;
    return 2;
}

s32 func_001cde38(void) {
    D_002BBE04 = 1;
    D_002BC080[0] = 128;
    D_002BC080[1] = 128;
    D_002BC080[2] = 128;
    D_002BC080[3] = 64;
    D_002BC090 = 256;
    D_002BC094 = 192;
    D_002BC098 = 0;
    D_002BC09C = 1;
    D_002BC0A0 = 0;
    D_002BC0A4 = 0;
    return 2;
}

s32 func_001cdea8(void) {
    if (D_002BBE04 == 1) {
        D_002BBE04 = 4;
    }
    return 2;
}

s32 func_001cded0(void) {
    D_002BBE04 = 0;
    func_001ec7c0(0);
    func_00242bd0();
    return 2;
}

s32 func_001cdf00(VmRec *vm) {
    VmMsg m;
    m.type = 17;
    m.val = (u32)vm->stk[vm->sp - 1];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 2;
    return 2;
}

/* ---- 0x001cdf98-0x001cfff8 ---- */

void func_00112b48(s32, s32, s32, s32);
void func_00112b80(s32, s32, s32, s32);
void func_00112bb8(s32);
void func_00108180(s32);
void func_001081a0(s32);
s32 func_00123618(s32);
f32 func_00176850(void);
VmFx *func_001226f0(s32, s32, s32);
void func_00122768(VmFx *);
void func_00104300(s32);
void func_001043f8(s32);
void func_00155be0(void *p);
void func_00120748(char *, void *, void *, s32);
void func_00131498(void *, void *);
void func_00131500(struct VmObj *);
void func_00135978(void *, s32, s32);
void func_001359c0(void *, s32, s32);
s32 func_00131b08(void *);
void func_00109df8(void);
void func_00109f48(s32);

s32 func_001cdf98(VmRec *vm) {
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, -1);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}

s32 func_001ce020(VmRec *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, d);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}

s32 func_001ce0b8(VmRec *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b80(a, b, c, d);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}

s32 func_001ce150(VmRec *vm) {
    s32 a = vm->stk[vm->sp--];
    func_00112bb8(a);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}

s32 func_001ce1a8(VmRec *vm) {
    s32 d = vm->stk[vm->sp--];
    s32 c = vm->stk[vm->sp--];
    s32 b = vm->stk[vm->sp--];
    s32 a = vm->stk[vm->sp--];
    func_00112b48(a, b, c, d);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}

s32 func_001ce240(VmRec *vm) {
    s32 a = vm->stk[vm->sp--];
    func_00112bb8(a);
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 10;
}

s32 func_001ce298(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = func_00123618(D_0038CCCC);
    return 2;
}

s32 func_001ce2e8(VmRec *vm) {
    func_00108180(vm->stk[vm->sp--]);
    return 2;
}

s32 func_001ce320(VmRec *vm) {
    func_001081a0(vm->stk[vm->sp--]);
    return 2;
}

/* The story flags D_00388CC4[2048..]: set, clear, increment, decrement the
 * one named by stk[32]. */
s32 func_001ce358(VmRec *vm) {
    s32 i = vm->stk[32];
    vm->sp--;
    if (i >= 2048) D_00388CC4[i] = 1;
    return 2;
}

s32 func_001ce390(VmRec *vm) {
    s32 i = vm->stk[32];
    vm->sp--;
    if (i >= 2048) D_00388CC4[i] = 0;
    return 2;
}

s32 func_001ce3c0(VmRec *vm) {
    s32 i = vm->stk[32];
    vm->sp--;
    if (i >= 2048) D_00388CC4[i]++;
    return 2;
}

s32 func_001ce400(VmRec *vm) {
    s32 i = vm->stk[32];
    vm->sp--;
    if (i >= 2048) D_00388CC4[i]--;
    return 2;
}

/* Scale stk[sp] by a random fraction (rounded). */
s32 func_001ce440(VmRec *vm) {
    s32 v = vm->stk[vm->sp];
    vm->stk[vm->sp] = func_00176850() * (f32)v + 0.5f;
    return 2;
}

/* func_001ce4b8, func_001ce5f0, func_001ce750 and func_001ce880 are in
 * vm_lib.nostrict_nofill.c. */

/* The effects D_0038CD3C[i]: create, set x0, the two positions, the fade. */
s32 func_001ce9b0(VmRec *vm) {
    s32 i = vm->stk[vm->sp];
    VmFx *p = func_001226f0(2, 0, i);
    D_0038CD3C[i] = p;
    vm->sp--;
    p->v30[3] = p->v30[2] = p->v30[1] = p->v30[0] = 1.0f;
    return 2;
}

s32 func_001cea38(VmRec *vm) {
    s32 i = vm->stk[vm->sp];
    VmFx *p = func_001226f0(2, 1, i);
    D_0038CD3C[i] = p;
    vm->sp--;
    p->v30[3] = p->v30[2] = p->v30[1] = p->v30[0] = 1.0f;
    return 2;
}

s32 func_001ceac0(VmRec *vm) {
    D_0038CD3C[vm->stk[vm->sp - 1]]->x0 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

s32 func_001ceb08(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 3];
    f32 x = vm->stk[sp - 2];
    f32 y = vm->stk[sp - 1];
    f32 z = vm->stk[sp];
    VmFx *p;
    vm->sp = sp - 4;
    p = D_0038CD3C[i];
    p->v10[0] = x;
    p->v10[1] = y;
    p->v10[2] = z;
    p->v10[3] = 1.0f;
    return 2;
}

s32 func_001ceb78(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 3];
    f32 x = vm->stk[sp - 2];
    f32 y = vm->stk[sp - 1];
    f32 z = vm->stk[sp];
    VmFx *p;
    vm->sp = sp - 4;
    p = D_0038CD3C[i];
    p->v20[0] = x;
    p->v20[1] = y;
    p->v20[2] = z;
    p->v20[3] = 1.0f;
    return 2;
}

/* The per-frame step of func_001cec68's colour fade. */
void func_001cebe8(void) {
    VmFx *p;
    if (--D_00389C90.fxn <= 0) D_00389C90.f3070.x &= ~0x80000000000ULL;
    p = D_00389C90.fx[D_00389C90.fxk];
    p->v30[0] += D_00389C90.fxd[0];
    p->v30[1] += D_00389C90.fxd[1];
    p->v30[2] += D_00389C90.fxd[2];
}

/* Fade effect fx[stk[sp-4]] to the colour stk[sp-3..sp-1] / 255 in stk[sp] frames. */
s32 func_001cec68(VmRec *vm) {
    VmFx *e;
    s32 n;
    f32 x, y, z, fn;
    D_00389C90.fxk = vm->stk[vm->sp - 4];
    e = D_00389C90.fx[D_00389C90.fxk];
    n = vm->stk[vm->sp];
    D_00389C90.fxn = n;
    fn = n;
    x = vm->stk[vm->sp - 3] / 255.0f;
    y = vm->stk[vm->sp - 2] / 255.0f;
    z = vm->stk[vm->sp - 1] / 255.0f;
    D_00389C90.fxd[0] = (x - e->v30[0]) / fn;
    D_00389C90.fxd[1] = (y - e->v30[1]) / fn;
    D_00389C90.fxd[2] = (z - e->v30[2]) / fn;
    if (n == 0) {
        e->v30[0] = x;
        e->v30[1] = y;
        e->v30[2] = z;
        e->v30[3] = 1.0f;
    } else {
        D_00389C90.f3070.x |= 0x80000000000ULL;
    }
    vm->sp -= 5;
    return 2;
}

s32 func_001ceda0(VmRec *vm) {
    s32 sp = vm->sp;
    s32 i = vm->stk[sp - 1];
    f32 v = vm->stk[sp];
    vm->sp = sp - 2;
    D_0038CD3C[i]->f0c = v;
    return 2;
}

/* func_001cede8 is in vm_lib.nofill.c. */

s32 func_001cee90(VmRec *vm) {
    func_00122768(D_0038CD3C[vm->stk[vm->sp]]);
    vm->sp--;
    return 2;
}

s32 func_001ceee8(void) {
    func_00104300(0x10);
    D_00389C90.f3078.x |= 1;
    return 2;
}

s32 func_001cef20(VmRec *vm) {
    func_00104300(vm->stk[vm->sp]);
    D_00389C90.f3078.x |= 1;
    vm->sp--;
    return 2;
}

s32 func_001cef80(void) {
    func_001043f8(0x10);
    D_00389C90.f3078.x &= ~1;
    return 2;
}

s32 func_001cefb8(VmRec *vm) {
    func_001043f8(vm->stk[vm->sp]);
    D_00389C90.f3078.x &= ~1ULL;
    vm->sp--;
    return 2;
}

s32 func_001cf018(VmRec *vm) {
    VmMsg m;
    m.type = 19;
    m.val = (u32)vm->stk[vm->sp - 2];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 1];
    m.v[1] = vm->stk[vm->sp] * 2.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cf0c8(VmRec *vm) {
    VmMsg m;
    m.type = 20;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cf110(VmRec *vm) {
    VmMsg m;
    m.type = 23;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 4] / 255.0f;
    m.v[1] = vm->stk[vm->sp - 3] / 255.0f;
    m.v[2] = vm->stk[vm->sp - 2] / 255.0f;
    m.v[3] = vm->stk[vm->sp - 1] * 0.0078125f;
    func_001c4640(&m);
    vm->sp -= 5;
    return 2;
}

s32 func_001cf210(VmRec *vm) {
    VmMsg m;
    if (vm->obj != 0) {
        m.type = 23;
        m.val = (u32)(vm->stk[vm->sp] * 2);
        m.x = vm->x0;
        m.v[0] = vm->obj->f370.col[0] * 0.0078125f;
        m.v[1] = vm->obj->f370.col[1] * 0.0078125f;
        m.v[2] = vm->obj->f370.col[2] * 0.0078125f;
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    vm->sp--;
    return 2;
}

s32 func_001cf300(VmRec *vm) {
    VmMsg m;
    m.type = 24;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

/* func_001cf348 is in vm_lib.nostrict.c. */
void func_001cf348(void);

/* The callback of the second file func_001cf478 / func_001cf5d0 load: t is
 * copied from base at the loop top and killed (t = 0) after the call: two
 * sets in the loop stop loop.c hoisting the copy / strength-reducing
 * t->off[i], and the mention outside the loop makes cse keep t (not base) as
 * the canonical register.  The copy at the top fills sched2's cycle-0 slot
 * (sll; addu; addiu order); reorg steals it into bnez. */
void func_001cf3e0(void) {
    s32 i;
    s32 n;
    Tbl_3dabd4 *base;
    Tbl_3dabd4 *t;
    D_00389C90.f3070.x &= ~0x400000000ULL;
    base = D_003DABD4;
    n = base->n;
    t = base;
    for (i = 0; i < n; i++) {
        t = base;
        func_00155be0((u8 *)t + *(s32 *)((u8 *)t + i * 4 + 8));
        t = 0;
    }
}

/* Load file stk[sp] of the table D_003C58E0 (func_001cf478) or D_003D97E0
 * (func_001cf5d0) into slot stk[sp-1] (1 or 2) of D_003DABD0. */
s32 func_001cf478(VmRec *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 1:
        D_003DABD0[0] = func_001559f0(52, 4);
        func_00120748(D_003C58E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf348, 0);
        D_00389C90.f3070.x |= 0x200000000ULL;
        break;
    case 2:
        D_003DABD0[1] = func_001559f0(56, 4);
        func_00120748(D_003C58E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf3e0, 0);
        D_00389C90.f3070.x |= 0x400000000ULL;
        break;
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001cf5d0(VmRec *vm) {
    switch (vm->stk[vm->sp - 1]) {
    case 1:
        D_003DABD0[0] = func_001559f0(52, 4);
        func_00120748(D_003D97E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf348, 0);
        D_00389C90.f3070.x |= 0x200000000ULL;
        break;
    case 2:
        D_003DABD0[1] = func_001559f0(56, 4);
        func_00120748(D_003D97E0[vm->stk[vm->sp]], D_003DABD0[vm->stk[vm->sp - 1] - 1], func_001cf3e0, 0);
        D_00389C90.f3070.x |= 0x400000000ULL;
        break;
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001cf728(VmRec *vm) {
    s32 f;
    switch (vm->stk[vm->sp]) {
    case 1:
        f = (s32)(D_0038CD00 >> 33) & 1;
        if (f == 1) return 4;
        vm->sp--;
        return 2;
    case 2:
        f = (s32)(D_0038CD00 >> 34) & 1;
        if (f == 1) return 4;
        vm->sp--;
        return 2;
    }
    return 4;
}

s32 func_001cf7a0(VmRec *vm) {
    if (vm->fl.b.b7 != 1) {
        Tbl *t;
        s32 sp = vm->sp;
        vm->fl.x |= 0x80;
        t = D_003DABCC[vm->stk[sp - 1]];
        func_00131498(vm->obj, (u8 *)t + ((s32 *)t)[vm->stk[sp] + 2]);
        vm->sp -= 2;
        return 2;
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001cf838(VmRec *vm) {
    if (vm->fl.b.b7 == 1) {
        func_00131500(vm->obj);
        vm->fl.x &= ~0x80;
    }
    return 2;
}

s32 func_001cf890(VmRec *vm) {
    func_00135978(vm->obj, vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001cf8e8(VmRec *vm) {
    func_001359c0(vm->obj, vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001cf940(VmRec *vm) {
    return ((s32)(vm->fl.x >> 1) & 1) ? 4 : 2;
}

/* func_001cf960 (s11w1, hand strict): from s8 w4.  The VM flags at 0x328 are
 * u64 bit-fields directly in the VM struct, which also has an f32 (x2f4): the
 * bit-field store `vm->b1 = 1` gets the VM struct alias set, so sd flags
 * still conflicts with the f32 pos loads (stays after them) but ld flags no
 * longer conflicts with the VmMsg stores in sched2.  So it keeps this view of
 * VmRec. */
typedef struct {
    s32 x0;
    struct VmObj *obj;
    u8 pad8[0x178];
    s32 sp;
    s32 stk[92];
    f32 x2f4;
    u8 pad2f8[0x30];
    u64 b0:1, b1:1, rest:62;
    u8 pad330[0x20];
} __attribute__((aligned(8))) VmRecW;

s32 func_001cf960(VmRecW *vm) {
    VmMsg m;
    m.type = 4;
    m.val = (u32)vm->stk[vm->sp] * 2;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 3] - vm->obj->pos[0];
    m.v[1] = vm->stk[vm->sp - 2] - vm->obj->pos[1];
    m.v[2] = vm->stk[vm->sp - 1] - vm->obj->pos[2];
    m.v[3] = 1.0f;
    vm->b1 = 1;
    func_001c4640(&m);
    vm->sp -= 4;
    return 2;
}

s32 func_001cfa58(void) {
    func_00109df8();
    return 2;
}

s32 func_001cfa78(VmRec *vm) {
    if (!(D_0037A378 & 1)) {
        func_00109f48(vm->stk[vm->sp]);
    }
    vm->sp--;
    return 2;
}

s32 func_001cfad0(VmRec *vm) {
    return func_00131b08(vm->obj) ? 2 : 4;
}

s32 func_001cfb00(VmRec *vm) {
    VmMsg m;
    m.type = 27;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cfb48(VmRec *vm) {
    VmMsg m;
    m.type = 28;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001cfb90(VmRec *vm) {
    VmMsg m;
    m.type = 5;
    m.val = (u32)(vm->stk[vm->sp] | 0x10000);
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp--;
    return 2;
}

/* func_001cfc28: MATCHED (session 19, s19m1), hand.  `f32 one = 1.0f;` at
 * the top (update_equiv_regs moves the li.s next to its use after sched1)
 * plus volatile type and v3 in the message, which put the li.s after the
 * dsll as in the original.  The c*2.0f chain is a local register variable
 * `register f32 t asm("$f0")` set by `t = (f32)c; t = t + t;`, so
 * local-alloc can no longer give f0 to the moved 1.0 (it gets f1 as in the
 * original).  FLAGGED: two volatile fields in the stack message (without them
 * 6w) and the pin (`t = c * 2.0f` in one statement: 6w). */
typedef struct {
    volatile u8 type;
    u64 val:24;
    s32 x;
    s32 a8;
    s32 ac;
    f32 v[3]; volatile f32 v3;
} VmMsgV;

s32 func_001cfc28(VmRec *vm) {
    VmMsgV m; f32 one = 1.0f;
    s32 a = vm->stk[vm->sp - 2];
    s32 b = vm->stk[vm->sp - 1];
    s32 c = vm->stk[vm->sp];
    VmRec *r = func_001e98d0(vm->fl.b.b5, a);
    if (r == 0) {
        vm->sp -= 3;
        return 2;
    }
    if (r->obj) {
        if (vm) m.x = r->obj->x4; else m.x = r->obj->x4;
        m.type = 29;
        m.val = (u32)b;
        {
            register f32 t asm("$f0");
            t = (f32)c;
            t = t + t;
            m.v[0] = t;
        }
        m.v[1] = 0;
        m.v[2] = 0;
        m.v3 = one;
        func_001c4640((VmMsg *)&m);
    }
    vm->sp -= 3;
    return 2;
}

s32 func_001cfd30(VmRec *vm) {
    VmMsg m;
    m.type = 17;
    m.val = (u32)(vm->stk[vm->sp - 1] | 0x10000);
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 2;
    return 2;
}

s32 func_001cfdd8(VmRec *vm) {
    VmMsg m;
    m.type = 19;
    m.val = (u32)(vm->stk[vm->sp - 2] | 0x10000);
    m.v[0] = vm->stk[vm->sp - 1];
    m.v[1] = vm->stk[vm->sp] * 2.0f;
    m.x = vm->x0;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

s32 func_001cfe98(void) {
    D_002C5958 &= ~8;
    return 2;
}

s32 func_001cfeb8(void) {
    D_002C5958 |= 8;
    return 2;
}

s32 func_001cfed8(void) {
    D_002C5958 = (s32)D_002C5958 & ~4 & 0xF7FFFFFF;
    return 2;
}

s32 func_001cff08(void) {
    D_002C5958 |= 4;
    return 2;
}

/* The per-frame step of func_001cff80's alpha fade. */
void func_001cff28(void) {
    if (--D_00389C90.an <= 0) D_00389C90.f3070.x &= ~0x4000000000ULL;
    D_002BC080[3] += D_00389C90.ad;
}

/* Fade the alpha D_002BC080[3] (D_002BC08C) to stk[sp-1] in stk[sp] frames. */
s32 func_001cff80(VmRec *vm) {
    s32 base = D_002BC08C;
    s32 n = vm->stk[vm->sp];
    D_00389C90.an = n;
    D_00389C90.ad = (vm->stk[vm->sp - 1] - base) / n;
    D_00389C90.f3070.x |= 0x4000000000ULL;
    vm->sp -= 2;
    return 2;
}

/* ---- 0x001cfff8-0x001d17d0 ---- */

void func_00111600(s32, s32, s32);
void func_001065a8(s32, s32, s32, s32);
void func_00106648(s32, s32, s32, s32);
void func_001066f8(void);
void func_001057b8(s32, s32);
s8 *func_00232cc0(s32);
void func_0013df40(void *, s32);
void func_0013dfa0(void *);
s32 func_00125a28(s32);
s32 D_00F20000(s32, s32);
void func_001560f8(s32, void (*)(void));
void func_00124218(s32);
struct VmObj *func_00123488(s32);
extern s32 D_002C5BB4;
extern s32 D_002C5BB8;

/* The per-frame step of func_001d0070's colour fade. */
void func_001cfff8(void) {
    if (--D_00389C90.rgbn <= 0) D_00389C90.f3070.x &= ~0x8000000000ULL;
    D_002BC080[0] += D_00389C90.rgbd[0];
    D_002BC080[1] += D_00389C90.rgbd[1];
    D_002BC080[2] += D_00389C90.rgbd[2];
}

/* Fade the colour D_002BC080[0..2] to stk[sp-3..sp-1] in stk[sp] frames. */
s32 func_001d0070(VmRec *vm) {
    s32 n = vm->stk[vm->sp];
    D_00389C90.rgbn = n;
    D_00389C90.rgbd[0] = (vm->stk[vm->sp - 3] - D_002BC080[0]) / n;
    D_00389C90.rgbd[1] = (vm->stk[vm->sp - 2] - D_002BC080[1]) / n;
    D_00389C90.rgbd[2] = (vm->stk[vm->sp - 1] - D_002BC080[2]) / n;
    D_00389C90.f3070.x |= 0x8000000000ULL;
    vm->sp -= 4;
    return 2;
}

s32 func_001d0138(VmRec *vm) {
    s32 sp = vm->sp;
    D_002BC090 = (vm->stk[sp] + 0x200) / 2;
    vm->sp = sp - 1;
    return 2;
}

s32 func_001d0170(VmRec *vm) {
    s32 sp = vm->sp;
    D_002BC094 = (vm->stk[sp] + 0x180) / 2;
    vm->sp = sp - 1;
    return 2;
}

s32 func_001d01a8(void) {
    ((s32 *)D_002C6440)[1] |= 4;
    return 2;
}

s32 func_001d01c8(void) {
    ((s32 *)D_002C6440)[1] &= ~4;
    return 2;
}

s32 func_001d01e8(VmRec *vm) {
    VmMsg m;
    m.type = 30;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 3] / 100.0f;
    m.v[1] = vm->stk[vm->sp - 2] / 100.0f;
    m.v[2] = vm->stk[vm->sp - 1] / 100.0f;
    func_001c4640(&m);
    vm->sp -= 4;
    return 2;
}

s32 func_001d02d0(VmRec *vm) {
    VmMsg m;
    m.type = 31;
    m.val = (u32)vm->stk[vm->sp];
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2] * 2.0f;
    m.v[1] = vm->stk[vm->sp - 1] * 2.0f;
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

/* Run script stk[sp] (< 100: of the field file D_002BCDE4, else - 100 of
 * D_002BCC90).  The flag test + return tail is written in both branches
 * (jump2 cross-jumps them back); with one shared tail it needs
 * -fno-sched-interblock (session 7, w3). */
s32 func_001d0380(VmRec *vm) {
    s32 a, b, n;
    b = D_00389C90.x3038;
    a = D_00389C90.x3034;
    n = vm->stk[vm->sp];
    if (n < 100) {
        func_001c2ec8((s8 *)D_002BCDE4, n);
        if ((vm->fl.b.b5 == 1 && b) || (vm->fl.b.b5 != 1 && a)) goto r8;
        vm->sp--;
        return 10;
    } else {
        n -= 100;
        func_001c3770((s8 *)D_002BCC90, n);
        if ((vm->fl.b.b5 == 1 && b) || (vm->fl.b.b5 != 1 && a)) goto r8;
        vm->sp--;
        return 10;
    }
r8:
    return 8;
}

s32 func_001d0440(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002BC128;
    return 2;
}

s32 func_001d0468(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002BC130;
    return 2;
}

s32 func_001d0490(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002BC134;
    return 2;
}

s32 func_001d04b8(VmRec *vm) {
    func_001057b8(vm->stk[vm->sp], 0);
    vm->sp--;
    return 2;
}

s32 func_001d0500(VmRec *vm) {
    func_001057b8(vm->stk[vm->sp], 1);
    vm->sp--;
    return 2;
}

s32 func_001d0548(VmRec *vm) {
    func_00111600(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}

s32 func_001d05a0(VmRec *vm) {
    func_001065a8(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001d0600(VmRec *vm) {
    func_00106648(vm->stk[vm->sp - 3], vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 4;
    return 2;
}

s32 func_001d0660(void) {
    func_001066f8();
    return 2;
}

s32 func_001d0680(VmRec *vm) {
    func_00232cc0(1);
    vm->sp--;
    return 2;
}

s32 func_001d06b8(VmRec *vm) {
    func_00232cc0(1);
    vm->sp--;
    return 2;
}

/* Bit stk[sp] (< 3072, from the top of each byte) of save block 1. */
s32 func_001d06f0(VmRec *vm) {
    s32 v = vm->stk[vm->sp];
    s32 q = v / 8;
    s32 sh = 7 - v % 8;
    if (v >= 3072) {
        vm->sp--;
        return 2;
    }
    vm->stk[vm->sp] = (func_00232cc0(1)[q] >> sh) & 1;
    return 2;
}

s32 func_001d07a8(void) {
    func_00104300(1);
    D_00389C90.f3078.x |= 1;
    return 2;
}

s32 func_001d07e0(void) {
    func_001043f8(1);
    D_00389C90.f3078.x &= ~1;
    return 2;
}

s32 func_001d0818(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_0013df40(o, vm->stk[vm->sp]);
    }
    vm->sp--;
    return 2;
}

/* The same for the three party members D_002E26A0[0..2]. */
s32 func_001d0868(VmRec *vm) {
    if (D_002E26A0[0] != 0) {
        func_0013df40(D_002E26A0[0], vm->stk[vm->sp]);
    }
    if (D_002E26A0[1] != 0) {
        func_0013df40(D_002E26A0[1], vm->stk[vm->sp]);
    }
    if (D_002E26A0[2] != 0) {
        func_0013df40(D_002E26A0[2], vm->stk[vm->sp]);
    }
    vm->sp--;
    return 2;
}

s32 func_001d0908(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_0013dfa0(o);
    }
    return 2;
}

s32 func_001d0938(void) {
    if (D_002E26A0[0] != 0) {
        func_0013dfa0(D_002E26A0[0]);
    }
    if (D_002E26A0[1] != 0) {
        func_0013dfa0(D_002E26A0[1]);
    }
    if (D_002E26A0[2] != 0) {
        func_0013dfa0(D_002E26A0[2]);
    }
    return 2;
}

/* The callback of func_001d09d8's load: the overlay's entry. */
s32 func_001d09a0(void) {
    D_00389C90.f3078.x &= ~0x2000ULL;
    return D_00F20000(0, 0);
}

s32 func_001d09d8(void) {
    func_00120748((char *)&D_00490620, D_00F20000, func_001d09a0, 0);
    D_00389C90.f3078.x |= 0x2000;
    return 2;
}

s32 func_001d0a28(void) {
    D_00425BC4 = 0;
    return 2;
}

s32 func_001d0a38(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = func_00125a28(1);
    return 2;
}

s32 func_001d0a80(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = func_00125a28(2);
    return 2;
}

s32 func_001d0ac8(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = func_00125a28(4);
    return 2;
}

s32 func_001d0b10(VmRec *vm) {
    vm->stk[vm->sp] = func_00125a28(vm->stk[vm->sp]);
    return 2;
}

s32 func_001d0b68(void) {
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 8;
}

/* Send message 13 (func_001d0b90) or 14 (func_001d0dd0) to every VM of the
 * running table whose entity exists. */
s32 func_001d0b90(VmRec *vm) {
    VmMsg m;
    s32 i;
    m.type = 13;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    if (D_00389C90.x316c) {
        for (i = 0; i < D_003C54F0; i++) {
            if (func_00123488(D_003C3A70[i].x0)) { m.x = D_003C3A70[i].x0; func_001c4640(&m); }
        }
    } else if (((s32)(vm->fl.x >> 5) & 1) == 1U) {
        if (D_00389C90.x3038 == 0) {
            for (i = 0; i < D_003B4D90; i++) {
                if (func_00123488(D_003A7990[i].x0)) { m.x = D_003A7990[i].x0; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].x0)) { m.x = D_0039A580[i].x0; func_001c4640(&m); }
            }
        }
    } else {
        if (D_00389C90.x3034 == 0) {
            for (i = 0; i < D_0039A570; i++) {
                if (func_00123488(D_0038D170[i].x0)) { m.x = D_0038D170[i].x0; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].x0)) { m.x = D_0039A580[i].x0; func_001c4640(&m); }
            }
        }
    }
    return 2;
}

s32 func_001d0dd0(VmRec *vm) {
    VmMsg m;
    s32 i;
    m.type = 14;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    if (D_00389C90.x316c) {
        for (i = 0; i < D_003C54F0; i++) {
            if (func_00123488(D_003C3A70[i].x0)) { m.x = D_003C3A70[i].x0; func_001c4640(&m); }
        }
    } else if (((s32)(vm->fl.x >> 5) & 1) == 1U) {
        if (D_00389C90.x3038 == 0) {
            for (i = 0; i < D_003B4D90; i++) {
                if (func_00123488(D_003A7990[i].x0)) { m.x = D_003A7990[i].x0; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].x0)) { m.x = D_0039A580[i].x0; func_001c4640(&m); }
            }
        }
    } else {
        if (D_00389C90.x3034 == 0) {
            for (i = 0; i < D_0039A570; i++) {
                if (func_00123488(D_0038D170[i].x0)) { m.x = D_0038D170[i].x0; func_001c4640(&m); }
            }
        } else {
            for (i = 0; i < D_003A7980; i++) {
                if (func_00123488(D_0039A580[i].x0)) { m.x = D_0039A580[i].x0; func_001c4640(&m); }
            }
        }
    }
    return 2;
}

/* Push 1 if the VM's entity exists (and set obj), else 0. */
s32 func_001d1010(VmRec *vm) {
    struct VmObj *o;
    vm->sp++;
    o = func_00123488(vm->x0);
    vm->obj = o;
    if (o != 0) {
        vm->stk[vm->sp] = 1;
        return 2;
    }
    vm->stk[vm->sp] = 0;
    return 2;
}

/* func_001d1080 is in vm_lib.nofill.c. */

/* Start a move (flag bit 6, stepped by func_001d1080) from the entity's
 * position to stk[sp-2..sp] at speed stk[sp-3]. */
s32 func_001d1230(VmRec *vm) {
    s32 sp = vm->sp;
    vm->fl.x |= 0x40;
    vm->f20 = vm->stk[sp - 3];
    vm->f14[0] = vm->stk[sp - 2];
    vm->f14[1] = vm->stk[sp - 1];
    vm->f14[2] = vm->stk[sp];
    vm->sp = sp - 4;
    vm->p[0] = vm->obj->pos[0];
    vm->p[1] = vm->obj->pos[1];
    vm->p[2] = vm->obj->pos[2];
    return 2;
}

s32 func_001d12b8(VmRec *vm) {
    s32 sp = vm->sp;
    vm->fl.x |= 0x40;
    vm->f20 = vm->stk[sp - 3] * D_002BBDFC;
    vm->f14[0] = vm->stk[sp - 2];
    vm->f14[1] = vm->stk[sp - 1];
    vm->f14[2] = vm->stk[sp];
    vm->sp = sp - 4;
    vm->p[0] = vm->obj->pos[0];
    vm->p[1] = vm->obj->pos[1];
    vm->p[2] = vm->obj->pos[2];
    return 2;
}

s32 func_001d1348(VmRec *vm) {
    D_00389C90.x3148 |= vm->stk[vm->sp];
    vm->sp--;
    return 2;
}

s32 func_001d1380(VmRec *vm) {
    D_00389C90.x3148 &= ~vm->stk[vm->sp];
    vm->sp--;
    return 2;
}

s32 func_001d13c0(void) {
    D_002C5958 |= 0x10;
    return 2;
}

s32 func_001d13e0(void) {
    D_002C5958 &= ~0x10;
    return 2;
}

s32 func_001d1400(void) {
    D_002A61F4 = 1;
    return 2;
}

s32 func_001d1418(void) {
    D_002A61F4 = 0;
    return 2;
}

s32 func_001d1428(VmRec *vm) {
    s32 sp = vm->sp;
    D_002A61F8 = vm->stk[sp];
    vm->sp = sp - 1;
    return 2;
}

s32 func_001d1450(VmRec *vm) {
    s32 sp = vm->sp;
    D_002A61FC = vm->stk[sp];
    vm->sp = sp - 1;
    return 2;
}

s32 func_001d1478(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002C5BB4;
    return 2;
}

s32 func_001d14a0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002C5AD4;
    return 2;
}

s32 func_001d14c8(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002C5BB8;
    return 2;
}

/* Turn towards the entity of VM stk[sp] (message 4) at speed stk[sp-1]. */
s32 func_001d14f0(VmRec *vm) {
    VmMsg m;
    s32 b = vm->stk[vm->sp - 1];
    VmRec *p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    if (p) {
        m.type = 4;
        m.val = (u32)(b * 2);
        m.x = vm->x0;
        m.v[0] = p->obj->pos[0] - vm->obj->pos[0];
        m.v[1] = p->obj->pos[1] - vm->obj->pos[1];
        m.v[2] = p->obj->pos[2] - vm->obj->pos[2];
        m.v[3] = 1.0f;
        vm->fl.x |= 2;
        func_001c4640(&m);
    }
    vm->sp -= 2;
    return 2;
}

void func_001d1610(void) {
    D_00389C90.f3070.x &= ~0x200000000000ULL;
}

s32 func_001d1640(VmRec *vm) {
    D_00389C90.f3070.x |= 0x200000000000ULL;
    func_001560f8(vm->stk[vm->sp], func_001d1610);
    vm->sp--;
    return 2;
}

s32 func_001d16a8(void) {
    return ((s32)(D_0038CD00 >> 45) & 1) ? 4 : 2;
}

s32 func_001d16c8(VmRec *vm) {
    func_00124218(vm->stk[vm->sp]);
    vm->obj = func_00123488(vm->x0);
    vm->sp--;
    return 2;
}

s32 func_001d1728(VmRec *vm) {
    s32 sp = vm->sp;
    D_002BC09C = vm->stk[sp - 1];
    D_002BC098 = vm->stk[sp] * 3.1415928f / 180.0f;
    vm->sp = sp - 2;
    return 2;
}

s32 func_001d1790(VmRec *vm) {
    s32 sp = vm->sp;
    D_002BC0A0 = vm->stk[sp - 1];
    D_002BC0A4 = vm->stk[sp];
    vm->sp = sp - 2;
    return 2;
}

/* ---- 0x001d17d0-0x001d3610 ---- */

/* func_001d17d0 .. func_001d1df0 (the distances) are in vm_lib.nofill.c. */

s32 func_0012ccf8(s32);
void func_001e0d68(s32);
void func_001e1088(s32);
void func_001e10c8(s32);
void func_001e13e8(s32);
void func_001e1418(s32, s32);
void func_001e1438(s32, s32);
void func_00131c28(struct VmObj *, f32);
void func_001e9fe8(f32 *, f32 *);
void sceVu0UnitMatrix(f32 (*)[4]);
void func_00267768(f32 (*)[4], f32 (*)[4], f32);
void func_00267810(f32 (*)[4], f32 (*)[4], f32);
void func_002672f8(V4 *, f32 (*)[4], V4 *);
void func_001315c0(struct VmObj *, s32, f32 *, f32);
void func_00267518(f32 *, f32 *, f32 *);
void func_0014f9b0(struct VmObj *, void *, f32);
void func_0014fa38(struct VmObj *, f32);
void func_002673b8(f32 *, f32 *);
void func_00111d90(s32);
void func_00111ef0(s32, void (*)(void));
void func_00111f58(void);
void func_00111f70(void);
s32 func_00111f88(void);
void func_00111fa0(s32);
void func_00111fb8(s32);
void func_00111fd0(s32);
void func_00111fe0(s32);
void func_001e58c0(s32);
void func_001e74b0(s32);
void func_00137330(struct VmObj *, s32, s32);
extern s32 D_0038CCC4;

s32 func_001d1ef0(VmRec *vm) {
    vm->stk[vm->sp] = func_0012ccf8(vm->stk[vm->sp]);
    return 2;
}

/* func_001d1f48, func_001d1fb0 and func_001d2018 are in vm_lib.nofill.c. */

s32 func_001d2080(void) {
    return 2;
}

s32 func_001d2088(void) {
    return 2;
}

/* func_001d2090 and func_001d2270 are in vm_lib.nofill.c. */

s32 func_001d2468(VmRec *vm) {
    func_001e0d68(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d24b0(VmRec *vm) {
    func_001e1088(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d24f8(VmRec *vm) {
    func_001e10c8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d2540(VmRec *vm) {
    func_001e13e8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d2588(VmRec *vm) {
    func_001e1418(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d25d8(VmRec *vm) {
    func_001e1438(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d2628(VmRec *vm) {
    s32 sp = vm->sp;
    f32 v = vm->stk[sp];
    vm->sp = sp - 1;
    D_0038CDDC = v / 100.0f;
    return 2;
}

s32 func_001d2668(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        func_00131c28(o, vm->stk[vm->sp - 1] / 100.0f);
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001d2708(VmRec *vm) {
    vm->sp--;
    return 2;
}

s32 func_001d2720(VmRec *vm) {
    (*(Cam0_2BC0F0 *)&D_002BC0F0).f20 = vm->stk[vm->sp - 1];
    (*(Cam0_2BC0F0 *)&D_002BC0F0).f24 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

/* Messages 7, 11, 28 (func_001d2768) or 6, 10, 27 (func_001d2860) to VM
 * stk[sp], and its flag bit 8. */
s32 func_001d2768(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    if (e) {
        m.type = 7;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 11;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 28;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        e->fl.x |= 0x100;
    }
    vm->sp--;
    return 2;
}

s32 func_001d2860(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    if (e) {
        m.type = 6;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 10;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 27;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        e->fl.x &= ~0x100ULL;
    }
    vm->sp--;
    return 2;
}

s32 func_001d2958(VmRec *vm) {
    V4 v;
    f32 rot[4];
    f32 out[4];
    f32 t[4];
    f32 m[4][4] __attribute__((aligned(16)));
    struct VmObj *e;
    v = D_00490630;
    e = vm->obj;
    if (e) {
        rot[0] = vm->stk[vm->sp - 2] * 3.1415928f / 180.0f;
        rot[1] = vm->stk[vm->sp - 1] * 3.1415928f / 180.0f + vm->obj->f3c;
        rot[2] = 0.0f;
        func_001e9fe8(out, rot);
        sceVu0UnitMatrix(m);
        func_00267768(m, m, out[0]);
        func_00267810(m, m, out[1]);
        func_002672f8(&v, m, &v);
        func_001315c0(vm->obj, 0, t, 0.0f);
        func_00267518(v.x, t, v.x);
        func_0014f9b0(vm->obj, &v, vm->stk[vm->sp] * 2.0f);
    }
end:
    vm->sp -= 3;
    return 2;
}

s32 func_001d2ab8(VmRec *vm) {
    f32 v[4];
    if (vm->obj) {
        v[3] = 1.0f;
        v[0] = vm->stk[vm->sp - 3];
        v[1] = vm->stk[vm->sp - 2];
        v[2] = vm->stk[vm->sp - 1];
        func_0014f9b0(vm->obj, v, (f32)vm->stk[vm->sp] * 2);
    }
    vm->sp -= 4;
    return 2;
}

s32 func_001d2b58(VmRec *vm) {
    f32 t[4];
    VmRec *p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp - 1]);
    if (vm->obj != 0 && p != 0) {
        func_001315c0(p->obj, 0, t, 0.0f);
        func_0014f9b0(vm->obj, t, 2.0f * (f32)vm->stk[vm->sp]);
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001d2c08(VmRec *vm) {
    if (vm->obj) {
        func_0014fa38(vm->obj, (f32)vm->stk[vm->sp] * 2);
    }
    vm->sp -= 1;
    return 2;
}

/* func_001d2c68's message: as VmMsg, but 16-aligned with a u32 bit-field
 * header (b10). */
typedef struct {
    u32 type:8, id:24;
    s32 x4;
    u8 pad8[8];
    f32 x, y, z;
    f32 ang;
} __attribute__((aligned(16))) VmMsgA;
typedef f32 VmVec4[4] __attribute__((aligned(16)));

/* Jump to stk[sp-2..sp] with height stk[sp-3] (messages 4 and 12); just
 * place the entity (message 3) while D_0037A378 bit 0 is set. */
s32 func_001d2c68(VmRec *vm) {
    VmVec4 v;
    VmMsgA m;
    f32 a, t, r, s, dx, dz;
    if ((*(Bits_37a378 *)&D_0037A378).b0) {
        m.type = 3;
        m.id = 0;
        m.x4 = vm->x0;
        m.x = vm->stk[vm->sp - 2];
        m.y = vm->stk[vm->sp - 1];
        m.z = vm->stk[vm->sp];
        m.ang = 1.0f;
        func_001c4640((VmMsg *)&m);
        vm->sp -= 4;
        return 6;
    }
    a = vm->stk[vm->sp - 3];
    t = D_002BBDFC;
    r = PlatSqrtf(a * t / 0.48469386f);
    r = (r + PlatSqrtf((a + (vm->obj->pos[1] - (f32)vm->stk[vm->sp - 1])) * t / 0.48469386f)) * 0.5f;
    dx = (f32)vm->stk[vm->sp - 2] - vm->obj->pos[0];
    dz = (f32)vm->stk[vm->sp] - vm->obj->pos[2];
    s = PlatSqrtf(dx * dx + dz * dz) / r;
    m.type = 4;
    m.id = 0;
    m.x4 = vm->x0;
    m.x = -(vm->obj->pos[0] - (f32)vm->stk[vm->sp - 2]);
    m.y = 0.0f;
    m.z = -(vm->obj->pos[2] - (f32)vm->stk[vm->sp]);
    m.ang = 1.0f;
    vm->fl.b.b1 = 1;
    func_001c4640((VmMsg *)&m);
    m.type = 12;
    m.id = 0;
    m.x4 = vm->x0;
    m.x = -(vm->obj->pos[0] - (f32)vm->stk[vm->sp - 2]);
    m.y = a;
    m.z = -(vm->obj->pos[2] - (f32)vm->stk[vm->sp]);
    m.ang = 1.0f;
    v[0] = -(vm->obj->pos[0] - (f32)vm->stk[vm->sp - 2]);
    v[1] = 0.0f;
    v[2] = -(vm->obj->pos[2] - (f32)vm->stk[vm->sp]);
    v[3] = 1.0f;
    func_002673b8(v, v);
    m.x = v[0] = v[0] * s;
    m.z = v[2] = v[2] * s;
    func_001c4640((VmMsg *)&m);
    vm->f20 = s;
    vm->fl.b.b2 = 1;
    vm->f14[0] = vm->stk[vm->sp - 2];
    vm->f14[1] = vm->stk[vm->sp - 1];
    vm->f14[2] = vm->stk[vm->sp];
    vm->sp -= 4;
    vm->x2f4 = r * (2.0f - D_002BBDFC + 2.0f);
    return 6;
}

/* The three screen points (stk[sp-1] + 256, stk[sp] + 192), flag bits 47-49. */
s32 func_001d2fd8(VmRec *vm) {
    D_00389C90.f3070.x |= 0x800000000000ULL;
    D_00389C90.f3078.b.hi = vm->stk[vm->sp - 1] + 256;
    D_00389C90.py0 = vm->stk[vm->sp] + 192;
    vm->sp -= 2;
    return 2;
}

s32 func_001d3040(void) {
    D_00389C90.f3070.x &= ~0x800000000000ULL;
    return 2;
}

s32 func_001d3078(VmRec *vm) {
    D_00389C90.f3070.x |= 0x1000000000000ULL;
    D_00389C90.px1 = vm->stk[vm->sp - 1] + 256;
    D_00389C90.py1 = vm->stk[vm->sp] + 192;
    vm->sp -= 2;
    return 2;
}

s32 func_001d30e0(void) {
    D_00389C90.f3070.x &= ~0x1000000000000ULL;
    return 2;
}

s32 func_001d3118(VmRec *vm) {
    func_00111d90(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

/* The callback of func_001d31d8: push 1, 0 on the running field VM and
 * call its handler 2. */
void func_001d3160(void) {
    VmRec *vm;
    if (D_0038CCC4 == 0) {
        vm = D_0038D170;
    } else {
        vm = D_0039A580;
    }
    vm->sp++;
    vm->stk[vm->sp] = 1;
    vm->sp++;
    vm->stk[vm->sp] = 0;
    func_001c19f8(vm, 2);
}

s32 func_001d31d8(VmRec *vm) {
    func_00111ef0(vm->stk[vm->sp], func_001d3160);
    vm->sp--;
    return 2;
}

s32 func_001d3228(void) {
    func_00111f58();
    return 2;
}

s32 func_001d3248(void) {
    func_00111f70();
    return 2;
}

s32 func_001d3268(VmRec *vm) {
    s32 v = func_00111f88();
    vm->sp++;
    vm->stk[vm->sp] = v;
    return 2;
}

s32 func_001d32a8(VmRec *vm) {
    func_00111fa0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d32f0(VmRec *vm) {
    func_00111fb8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d3338(VmRec *vm) {
    func_00111fe0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d3380(VmRec *vm) {
    func_00111fd0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d33c8(VmRec *vm) {
    D_00389C90.f3070.x |= 0x2000000000000ULL;
    D_00389C90.px2 = vm->stk[vm->sp - 1] + 256;
    D_00389C90.py2 = vm->stk[vm->sp] + 192;
    vm->sp -= 2;
    return 2;
}

s32 func_001d3430(void) {
    D_00389C90.f3070.x &= ~0x2000000000000ULL;
    return 2;
}

s32 func_001d3468(VmRec *vm) {
    D_0038CDE4 = (s32)vm;
    D_0037A378 |= 8;
    return 2;
}

s32 func_001d3490(void) {
    D_0037A378 &= ~8;
    return 2;
}

s32 func_001d34b0(VmRec *vm) {
    switch (vm->stk[vm->sp]) {
    case 0:
        func_001e58c0(0);
        break;
    case 1:
        func_001e58c0(1);
        break;
    case 2:
        func_001e58c0(2);
        break;
    case 3:
        func_001e58c0(3);
        break;
    }
    vm->sp--;
    return 2;
}

s32 func_001d3558(VmRec *vm) {
    func_001e74b0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d35a0(VmRec *vm) {
    func_00137330(func_00123488(vm->stk[vm->sp - 1]), 0, vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

/* ---- 0x001d3610-0x001d4000 ---- */

s32 func_00105960(struct VmObj *, s32);
s32 func_001059d0(void *);
void func_00176ba8(s8 *, s32);
void func_00176c60(s32);
void func_00135848(struct VmObj *);
void func_00135870(struct VmObj *);
f32 *func_0014f370(struct VmObj *);
void func_0014f398(struct VmObj *);
void func_0013c7d8(s32);
void func_0013c840(s32);
void func_00112d80(void);
void func_0011c710(void);
void func_00111380(void);
void func_00232d60(void);
void func_001d3e30(VmRec *vm);

/* How many of item stk[sp] the party (func_001d3610: all four members,
 * func_001d3710: the first three) has equipped, plus the stock. */
s32 func_001d3610(VmRec *vm) {
    s32 n = 0;
    s32 i, j, c;
    s32 k = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) {
        c = D_00304BE8->x48e[i];
        if (c < 20) {
            for (j = 0; j < ((u8 *)D_00304BE8)[c * 0x74 + 0x25]; j++) { if (D_00304BE8->m[c].sub.x22[j] == k) n++; }
            
        }
    }
    n += D_00304BE8->items[k];
    vm->stk[vm->sp] = n;
    return 2;
}

s32 func_001d3710(VmRec *vm) {
    s32 n = 0;
    s32 i, j, c;
    s32 k = vm->stk[vm->sp];
    for (i = 0; i < 4; i++) { if (i == 3) break;
        c = D_00304BE8->x48e[i];
        if (c < 20) {
            for (j = 0; j < ((u8 *)D_00304BE8)[c * 0x74 + 0x25]; j++) { if (D_00304BE8->m[c].sub.x22[j] == k) n++; }
        }
    }
    n += D_00304BE8->items[k];
    vm->stk[vm->sp] = n;
    return 2;
}

s32 func_001d3828(VmRec *vm) {
    /* the byte table at D_00304BE8 + 0x499, added as an s32 address */
    vm->stk[vm->sp] = *(u8 *)(vm->stk[vm->sp] + (s32)D_00304BE8 + 0x499);
    return 2;
}

/* Add stk[sp] to the stock of item stk[sp-1], clamped to 0-99. */
s32 func_001d3858(VmRec *vm) {
    s32 v = D_00304BE8->items[vm->stk[vm->sp - 1]] + vm->stk[vm->sp];
    if (v >= 100) D_00304BE8->items[vm->stk[vm->sp - 1]] = 99;
    else if (v < 0) D_00304BE8->items[vm->stk[vm->sp - 1]] = 0;
    else D_00304BE8->items[vm->stk[vm->sp - 1]] += vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

s32 func_001d38d0(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        vm->stk[vm->sp] = func_00105960(o, vm->stk[vm->sp]);
    } else {
        vm->stk[vm->sp] = 0;
    }
    return 2;
}

s32 func_001d3948(VmRec *vm) {
    void *d = D_002E26A0[0];
    vm->sp++;
    if (d) vm->stk[vm->sp] = func_001059d0(d);
    else vm->stk[vm->sp] = 0;
    return 2;
}

/* Play the sound of the script file's table entry stk[sp] (not while
 * D_0037A378 bit 0 is set). */
s32 func_001d39b0(VmRec *vm) {
    s8 *x = D_00389C90.x3040 + D_00389C90.x3060[vm->stk[vm->sp]];
    if (!(D_0037A378 & 1)) {
        func_00176ba8(x, 0);
    }
    vm->sp--;
    return 2;
}

s32 func_001d3a28(void) {
    func_00176c60(0);
    return 2;
}

s32 func_001d3a48(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00135848(o);
    }
    return 2;
}

s32 func_001d3a78(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00135870(o);
    }
    return 2;
}

/* Send the entity to its home position p50 (message 3). */
s32 func_001d3aa8(VmRec *vm) {
    VmMsg m;
    struct VmObj *o = vm->obj;
    if (o) {
        m.type = 3;
        m.val = 0;
        m.x = vm->x0;
        m.v[0] = o->p50[0];
        m.v[1] = o->p50[1];
        m.v[2] = o->p50[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    return 2;
}

s32 func_001d3b20(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_0014f370(o)[2] = vm->stk[vm->sp];
    }
    vm->sp--;
    return 2;
}

s32 func_001d3b80(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_0014f398(o);
    }
    return 2;
}

s32 func_001d3bb0(VmRec *vm) {
    if (vm->obj) {
        vm->obj->f130->f18 = vm->stk[vm->sp];
    }
    vm->sp--;
    return 2;
}

s32 func_001d3be8(VmRec *vm) {
    vm->sp++;
    if (vm->obj) {
        vm->stk[vm->sp] = vm->obj->f130->f18;
    }
    return 2;
}

s32 func_001d3c28(VmRec *vm) {
    func_0013c7d8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d3c70(VmRec *vm) {
    func_0013c840(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

/* func_001d3cb8, func_001d3d08 and func_001d3d58 are in vm_lib.nofill.c. */

s32 func_001d3da8(void) {
    func_00112d80();
    D_00389C90.f3070.x |= 0x10000000000ULL;
    return 8;
}

s32 func_001d3de8(void) {
    func_0011c710();
    return 2;
}

s32 func_001d3e08(void) {
    func_00111380();
    func_00232d60();
    return 2;
}

/* func_001d3e30 is in vm_lib.nofill.c. */

/* Start a move (flag bit 9, stepped by func_001d3e30) to stk[sp-2..sp] at
 * speed stk[sp-3] / 50, and take the first step. */
s32 func_001d3ff0(VmRec *vm) {
    vm->fl.x |= 0x200;
    vm->f14[0] = vm->stk[vm->sp - 2];
    vm->f14[1] = vm->stk[vm->sp - 1];
    vm->f20 = vm->stk[vm->sp - 3] / 50.0f;
    vm->f14[2] = vm->stk[vm->sp];
    vm->p[0] = vm->obj->pos[0];
    vm->p[1] = vm->obj->pos[1];
    vm->p[2] = vm->obj->pos[2];
    func_001d3e30(vm);
    vm->sp -= 4;
    return 2;
}

/* ---- 0x001d4000-0x001d4c08 ---- */

VmRec *func_001e9b98(s32 k, s32 id);
void func_001008d8(f32);

/* Party member stk[sp] (< 4) of D_00304BE8. */
s32 func_001d40b0(VmRec *vm) {
    s32 i = vm->stk[vm->sp];
    if (i < 4) vm->stk[vm->sp] = D_00304BE8->x48e[i];
    return 2;
}

/* The position x / y / z, the heading (degrees), rsp and f16c / 2 of the
 * entity of VM stk[sp]. */
s32 func_001d40f0(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        vm->stk[vm->sp] = o->pos[0];
    }
    return 2;
}

s32 func_001d4168(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        vm->stk[vm->sp] = o->pos[1];
    }
    return 2;
}

s32 func_001d41e0(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        vm->stk[vm->sp] = o->pos[2];
    }
    return 2;
}

s32 func_001d4258(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        vm->stk[vm->sp] = o->f3c * 180.0f / 3.1415928f;
    }
    return 2;
}

s32 func_001d42f0(VmRec *vm) {
    VmRec *e = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    vm->stk[vm->sp] = e->rsp;
    return 2;
}

s32 func_001d4358(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        vm->stk[vm->sp] = o->f16c * 0.5f;
    }
    return 2;
}

s32 func_001d43d8(VmRec *vm) {
    VmRec *e = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    vm->stk[vm->sp] = e->obj->f6c->f3c;
    return 2;
}

s32 func_001d4448(VmRec *vm) {
    VmRec *e = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    vm->stk[vm->sp] = e->obj->f6c->f44;
    return 2;
}

/* The position x / y / z of party member stk[sp] (D_002E26A0). */
s32 func_001d44b8(VmRec *vm) {
    void *t = D_002E26A0[vm->stk[vm->sp]];
    struct VmObj *a = t;
    if (a != 0) {
        vm->stk[vm->sp] = a->pos[0];
    }
    return 2;
}

s32 func_001d44f8(VmRec *vm) {
    void *t = D_002E26A0[vm->stk[vm->sp]];
    struct VmObj *a = t;
    if (a != 0) {
        vm->stk[vm->sp] = a->pos[1];
    }
    return 2;
}

s32 func_001d4538(VmRec *vm) {
    void *t = D_002E26A0[vm->stk[vm->sp]];
    struct VmObj *a = t;
    if (a != 0) {
        vm->stk[vm->sp] = a->pos[2];
    }
    return 2;
}

/* The heading (degrees), rsp and f16c / 2 of party member stk[sp]'s entity. */
s32 func_001d4578(VmRec *vm) {
    struct VmObj *o = func_00123488(D_00304BE8->x48e[vm->stk[vm->sp]]);
    if (o != 0) {
        vm->stk[vm->sp] = o->f3c * 180.0f / 3.1415928f;
    }
    return 2;
}

s32 func_001d4610(VmRec *vm) {
    VmRec *e = func_001e9b98((s32)(vm->fl.x >> 5) & 1, D_00304BE8->x48e[vm->stk[vm->sp]]);
    if (e) vm->stk[vm->sp] = e->rsp;
    return 2;
}

s32 func_001d4690(VmRec *vm) {
    struct VmObj *o = func_00123488(D_00304BE8->x48e[vm->stk[vm->sp]]);
    if (o != 0) {
        vm->stk[vm->sp] = o->f16c * 0.5f;
    }
    return 2;
}

/* Stop the moves (flag bits 0, 6, 9) and send message 18. */
s32 func_001d4710(VmRec *vm) {
    VmMsg m;
    vm->fl.x &= ~1ULL;
    vm->fl.x &= ~0x40ULL;
    vm->fl.x &= ~0x200ULL;
    m.type = 18;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    return 2;
}

/* func_001d4798 is in vm_lib.nofill.c. */

s32 func_001d4ac8(VmRec *vm) {
    func_001008d8(vm->stk[vm->sp] * 3.1415928f / 180.0f);
    vm->sp--;
    return 2;
}

s32 func_001d4b38(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CDE0;
    return 2;
}

s32 func_001d4b60(VmRec *vm) {
    VmMsg m;
    m.type = 32;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = vm->stk[vm->sp - 2];
    m.v[3] = 1.0f;
    m.v[1] = vm->stk[vm->sp - 1];
    m.v[2] = vm->stk[vm->sp];
    func_001c4640(&m);
    vm->sp -= 3;
    return 2;
}

/* ---- 0x001d4c08-0x001d5408 ---- */

/* func_001d4c08 and func_001d4cb8 are in vm_lib.nofill.c. */

s32 func_00135838(struct VmObj *);
struct VmObj *func_00123220(struct VmObj *);
void func_00103988(s32);
void func_001038b0(s32);
void func_0011ef10(s32, s32 (*)(void));

s32 func_001d4d68(VmRec *vm) {
    struct VmObj *o = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp])->obj;
    if (o != 0) {
        vm->stk[vm->sp] = func_00135838(o);
    }
    return 2;
}

s32 func_001d4de0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_002C5958 & 1;
    return 2;
}

s32 func_001d4e10(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->x31c;
    return 2;
}

s32 func_001d4e38(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->x320;
    return 2;
}

/* Messages 7 and 9 (func_001d4e60) or 6 and 8 (func_001d4f10) to every
 * entity in the list func_00123220 walks. */
s32 func_001d4e60(VmRec *vm) {
    VmMsg m;
    struct VmObj *p;
    for (p = func_00123220(0); p; p = func_00123220(p)) {
        m.type = 7;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
        m.type = 9;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
    }
    return 2;
}

s32 func_001d4f10(VmRec *vm) {
    VmMsg m;
    struct VmObj *p;
    for (p = func_00123220(0); p; p = func_00123220(p)) {
        m.type = 6;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
        m.type = 8;
        m.val = 0;
        m.x = p->x4;
        func_001c4640(&m);
    }
    return 2;
}

s32 func_001d4fc0(VmRec *vm) {
    D_002A61F0 = 0;
    func_00103988(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d5010(VmRec *vm) {
    D_002A61F0 = 0;
    func_001038b0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

/* The countdown func_001d5090 starts. */
s32 func_001d5060(void) {
    s32 n = D_0062A210 - 1;
    D_0062A210 = n;
    if (n < 0) {
        D_002A61F0 = 0;
        return 4;
    }
    return 0;
}

s32 func_001d5090(VmRec *vm) {
    D_002A61F0 = 1;
    func_00103988(vm->stk[vm->sp]);
    D_0062A210 = vm->stk[vm->sp];
    func_0011ef10(50000, func_001d5060);
    vm->sp--;
    return 2;
}

s32 func_001d5118(VmRec *vm) {
    D_002A61F0 = 1;
    func_001038b0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

/* func_001d5168 is in vm_lib.nofill.c. */

s32 func_001d5278(VmRec *vm) {
    VmMsg m;
    m.type = 33;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d52c0(VmRec *vm) {
    VmMsg m;
    m.type = 34;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d5308(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        o->x0 &= 0xFDFFFFFF;
    }
    return 2;
}

s32 func_001d5330(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        o->x0 |= 0x02000000;
    }
    return 2;
}

s32 func_001d5350(VmRec *vm) {
    vm->sp++;
    if (vm->obj) vm->stk[vm->sp] = vm->obj->f164;
    return 2;
}

s32 func_001d5388(VmRec *vm) {
    VmRec *p = func_001e98d0((s32)(vm->fl.x >> 5) & 1, vm->stk[vm->sp]);
    if (p != 0) {
        struct VmObj *o = p->obj;
        if (o != 0) {
            vm->stk[vm->sp] = o->f164;
        }
    }
    return 2;
}

/* ---- 0x001d5408-0x001d5b58 ---- */

s32 func_00141468(struct VmObj *, s32);
s32 func_00141540(struct VmObj *, s32);
s32 func_0012cac8(s32, s32);
s32 func_0013c6a8(s32);
s32 func_00123298(void);
struct VmObj *func_001230a0(struct VmObj *);
void func_0013c638(s32, s32);
void func_0013c778(s32, s32, s32);

s32 func_001d5408(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00141468(o, vm->stk[vm->sp]);
    }
    vm->sp--;
    return 2;
}

s32 func_001d5458(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00141540(o, vm->stk[vm->sp]);
    }
    vm->sp--;
    return 2;
}

s32 func_001d54a8(VmRec *vm) {
    if (func_00123298() <= 0) return 2;
    return 4;
}

s32 func_001d54d8(void) {
    func_0012cac8(0, 0);
    return 2;
}

s32 func_001d5500(void) {
    func_0012cac8(0, 1);
    return 2;
}

s32 func_001d5528(void) {
    func_0012cac8(1, 0);
    return 2;
}

s32 func_001d5550(void) {
    func_0012cac8(1, 1);
    return 2;
}

s32 func_001d5578(void) {
    func_0012cac8(2, 0);
    return 2;
}

s32 func_001d55a0(void) {
    func_0012cac8(2, 1);
    return 2;
}

s32 func_001d55c8(void) {
    func_0012cac8(6, 0);
    return 2;
}

s32 func_001d55f0(void) {
    func_0012cac8(6, 1);
    return 2;
}

/* Push how many entities in the list have func_00123618 kind 0xcd. */
s32 func_001d5618(VmRec *vm) {
    s32 n = 0;
    struct VmObj *p;
    for (p = func_001230a0(0); p; p = func_00123220(p)) {
        if (func_00123618(p->x4) == 0xcd) n++;
    }
    vm->sp++;
    vm->stk[vm->sp] = n;
    return 2;
}

s32 func_001d56a8(VmRec *vm) {
    vm->sp++;
    if (D_002E27A8 == 2) vm->stk[vm->sp] = 1;
    else vm->stk[vm->sp] = 0;
    return 2;
}

s32 func_001d56f0(VmRec *vm) {
    VmMsg m;
    m.type = 37;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d5738(VmRec *vm) {
    VmMsg m;
    m.type = 38;
    m.val = 0;
    m.x = vm->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001d5780(VmRec *vm) {
    func_0013c638(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d57d0(VmRec *vm) {
    vm->stk[vm->sp] = func_0013c6a8(vm->stk[vm->sp]);
    return 2;
}

s32 func_001d5828(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CDEC;
    return 2;
}

s32 func_001d5850(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CDF0;
    return 2;
}

s32 func_001d5878(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CDF4;
    return 2;
}

s32 func_001d58a0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CDF8;
    return 2;
}

/* func_001d58c8 is in vm_lib.nofill.c. */

s32 func_001d5978(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CDE8;
    return 2;
}

/* Message 14 (func_001d59a0) or 13 (func_001d5a50) to every entity whose
 * flag bits 37-38 are 2. */
s32 func_001d59a0(VmRec *vm) {
    VmMsg m;
    struct VmObj *p;
    m.type = 14;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (((s32)(p->f370.flags >> 37) & 3) == 2) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}

s32 func_001d5a50(VmRec *vm) {
    VmMsg m;
    struct VmObj *p;
    m.type = 13;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (((s32)(p->f370.flags >> 37) & 3) == 2) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}

s32 func_001d5b00(VmRec *vm) {
    func_0013c778(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}

/* ---- 0x001d5b58-0x001d6000 ---- */

/* func_001d5b58 is in vm_lib.nofill.c. */

void func_0014ec10(s32);

s32 func_001d5ed8(VmRec *vm) {
    s32 sp = vm->sp;
    D_002BBE00 = (f32)vm->stk[sp] / 100.0f;
    vm->sp = sp - 1;
    return 2;
}

s32 func_001d5f18(VmRec *vm) {
    s32 sp = vm->sp;
    D_002A6200 = (f32)vm->stk[sp] / 100.0f;
    vm->sp = sp - 1;
    return 2;
}

s32 func_001d5f58(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CE00;
    return 2;
}

s32 func_001d5f80(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038CE04;
    return 2;
}

s32 func_001d5fa8(VmRec *vm) {
    D_00389C90.x3170 = vm->stk[vm->sp - 1];
    D_00389C90.x3174 = vm->stk[vm->sp];
    vm->sp -= 2;
    return 2;
}

s32 func_001d5ff0(VmRec *vm) {
    func_0014ec10(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

/* ---- 0x001d6000-0x001d6d60 ---- */

void func_0014ec38(s32);
s32 func_00145080(s32, s32);
s32 func_00145138();
s32 func_00112e90();
s32 func_00141b10(s32, void *);
s32 func_00111778(s32);
s32 func_001eac68();
s32 func_0024d418();
s32 func_0024d490(void);
s32 func_00104288();
s32 func_00100ab0();
s32 func_00100ae0();
s32 func_0017f078(s32);
s32 func_0017f110();
s32 func_00135a10(struct VmObj *, s32);
s32 func_00135a38(struct VmObj *, s32);
s32 func_002414a8(s32, s32);
s32 func_00105ce0(s32);
void func_00105d38(s32, s32);
s32 func_001118a0();
s32 func_001118b0();
void func_001248e8(s32);
extern s32 D_002BD110;

s32 func_001d6038(VmRec *vm) {
    func_0014ec38(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d6080(void) {
    s32 i;
    for (i = 1; i < 0x20; i++) {
        func_0014ec10(i);
    }
    return 2;
}

s32 func_001d60c0(void) {
    s32 i;
    for (i = 1; i < 0x20; i++) {
        func_0014ec38(i);
    }
    return 2;
}

s32 func_001d6100(VmRec *vm) {
    s32 sp = vm->sp;
    D_002BBAB0 = vm->stk[sp];
    vm->sp = sp - 1;
    return 2;
}

/* Push how many of the four party slots x48e[] hold a member (< 20). */
s32 func_001d6128(VmRec *vm) {
    s32 i = 3, n = 0;
    u8 *p = D_00304BE8->x48e;
    do {
        n += *p++ < 20;
        i--;
    } while (i >= 0);
    vm->sp++;
    vm->stk[vm->sp] = n;
    return 2;
}

s32 func_001d6180(VmRec *vm) {
    func_00145080(0, vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d61c8(VmRec *vm) {
    func_00145080(1, vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d6210(void) {
    func_00145138();
    return 2;
}

s32 func_001d6230(void) {
    func_00112e90();
    return 2;
}

/* Add trigger box nbox: id stk[sp-6], centre stk[sp-5..sp-3], size
 * stk[sp-2..sp]. */
s32 func_001d6250(VmRec *vm) {
    s32 n = D_00389C90.nbox;
    D_00389C90.box[n].id = vm->stk[vm->sp - 6];
    D_00389C90.box[n].c[0] = vm->stk[vm->sp - 5];
    D_00389C90.box[n].c[1] = vm->stk[vm->sp - 4];
    D_00389C90.box[n].c[2] = vm->stk[vm->sp - 3];
    D_00389C90.box[n].s[0] = vm->stk[vm->sp - 2];
    D_00389C90.box[n].s[1] = vm->stk[vm->sp - 1];
    D_00389C90.box[n].s[2] = vm->stk[vm->sp];
    D_00389C90.nbox++;
    vm->sp -= 7;
    return 2;
}

/* How many entities of kind stk[sp] are in the list. */
s32 func_001d6348(VmRec *vm) {
    s32 n = 0;
    struct VmObj *p;
    for (p = func_001230a0(0); p; p = func_00123220(p)) {
        if (func_00123618(p->x4) == vm->stk[vm->sp]) n++;
    }
    vm->stk[vm->sp] = n;
    return 2;
}

/* Remove the trigger boxes with id stk[sp]. */
s32 func_001d63e8(VmRec *vm) {
    s32 i, j, k;
    for (i = 0; i < D_00389C90.nbox; i = k) {
        if (D_00389C90.box[i].id == vm->stk[vm->sp]) {
            k = i + 1;
            if (k < D_00389C90.nbox) {
                for (j = k; j < D_00389C90.nbox; j++) D_00389C90.box[j - 1] = D_00389C90.box[j];
                k = i;
                D_00389C90.nbox--;
            } else D_00389C90.nbox--;
        } else k = i + 1;
    }
    vm->sp--;
    return 2;
}

s32 func_001d64f8(VmRec *vm) {
    s32 buf[60];
    func_00141b10(vm->stk[vm->sp], buf);
    vm->stk[vm->sp] = buf[15];
    return 2;
}

s32 func_001d6558(VmRec *vm) {
    s32 buf[60];
    func_00141b10(vm->stk[vm->sp], buf);
    vm->stk[vm->sp] = buf[17];
    return 2;
}

s32 func_001d65b8(VmRec *vm) {
    func_00111778(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d6600(void) {
    func_001eac68();
    func_0024d418();
    return 2;
}

s32 func_001d6628(VmRec *vm) {
    if (!func_0024d490()) return 4;
    return 2;
}

/* func_001d6658 is in vm_lib.nofill.c. */

s32 func_001d66b8(void) {
    func_00104288();
    return 2;
}

s32 func_001d66d8(void) {
    func_00100ab0();
    return 2;
}

s32 func_001d66f8(void) {
    func_00100ae0();
    return 2;
}

s32 func_001d6718(VmRec *vm) {
    func_0017f078(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d6760(void) {
    func_0017f110();
    return 2;
}

s32 func_001d6780(VmRec *vm) {
    func_00135a10(vm->obj, vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d67c8(VmRec *vm) {
    func_00135a38(vm->obj, vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d6810(VmRec *vm) {
    func_002414a8(vm->stk[vm->sp], 1);
    vm->sp--;
    return 2;
}

s32 func_001d6858(VmRec *vm) {
    func_002414a8(vm->stk[vm->sp], 3);
    vm->sp--;
    return 2;
}

s32 func_001d68a0(VmRec *vm) {
    func_002414a8(vm->stk[vm->sp], 1);
    vm->sp--;
    return 2;
}

s32 func_001d68e8(VmRec *vm) {
    func_002414a8(vm->stk[vm->sp], 0);
    vm->sp--;
    return 2;
}

s32 func_001d6930(void) {
    D_002C5958 &= 0xF7FFFFFF;
    return 2;
}

s32 func_001d6958(void) {
    D_002C5958 |= 0x08000000;
    return 2;
}

s32 func_001d6978(VmRec *vm) {
    vm->stk[vm->sp] = func_00105ce0(vm->stk[vm->sp]);
    return 2;
}

s32 func_001d69d0(VmRec *vm) {
    func_00105d38(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d6a20(void) {
    func_001118a0();
    return 2;
}

s32 func_001d6a40(void) {
    func_001118b0();
    return 2;
}

/* Give item stk[sp-1] to party member stk[sp]: into a free slot of its
 * x22[], else into the stock (at most 99; pushes 1 when it was full). */
s32 func_001d6a60(VmRec *vm) {
    s32 k = vm->stk[vm->sp];
    s32 item = vm->stk[vm->sp - 1];
    s32 r = 0;
    s32 j;
    for (j = 0; j < D_00304BE8->m[k].sub.x21; j++) {
        if (D_00304BE8->m[k].sub.x22[j] == 0) {
            D_00304BE8->m[k].sub.x22[j] = item;
            r = 0;
            break;
        }
    }
    if (j == D_00304BE8->m[k].sub.x21) {
        s32 v = D_00304BE8->items[item] + 1;
        if (v >= 100) {
            D_00304BE8->items[item] = 99;
            r = 1;
        } else {
            D_00304BE8->items[item] = v;
            r = 0;
        }
    }
    vm->sp--;
    vm->stk[vm->sp] = r;
    return 2;
}

/* func_001d6b70 keeps h17's volatile views of D_002C5AD0 / D_002C5BB0 (the
 * pieces' types, W29S70 / PadSt, have no fields at these offsets). */
typedef struct { s32 f0; s32 f4; s32 f8; } S5AD0;
typedef struct { s32 f0; s32 f4; s32 f8; u8 padc[0x24]; s32 a30[15]; s32 f6c; } S5BB0;
extern volatile S5BB0 D_002C5BB0;
#define D_002C5AD0V (*(volatile S5AD0 *)&D_002C5AD0)

s32 func_001d6b70(VmRec *vm) {
    if (!((s32)(D_0038CD00 >> 58) & 1)) return 4;
    D_002C5AD0V.f8 = 0;
    D_002C5AD0V.f4 = 0;
    D_002C5BB0.f6c = 0;
    D_002C5BB0.f4 = 0;
    D_002C5BB0.f8 = 0;
    D_002C5BB0.a30[0] = 0;
    D_002C5BB0.a30[1] = 0;
    D_002C5BB0.a30[2] = 0;
    D_002C5BB0.a30[3] = 0;
    D_002C5BB0.a30[4] = 0;
    D_002C5BB0.a30[5] = 0;
    D_002C5BB0.a30[6] = 0;
    D_002C5BB0.a30[7] = 0;
    D_002C5BB0.a30[8] = 0;
    D_002C5BB0.a30[9] = 0;
    D_002C5BB0.a30[10] = 0;
    D_002C5BB0.a30[11] = 0;
    D_002C5BB0.a30[12] = 0;
    D_002C5BB0.a30[13] = 0;
    D_002C5BB0.a30[14] = 0;
    return 0;
}

s32 func_001d6bf8(void) {
    D_002BD110 = 0;
    return 2;
}

s32 func_001d6c08(void) {
    D_002BD110 = 1;
    return 2;
}

s32 func_001d6c20(void) {
    D_00389C90.f3070.x |= 0x8000000000000000ULL >> 4;
    return 2;
}

s32 func_001d6c48(void) {
    D_00389C90.f3070.x &= ~(0x8000000000000000ULL >> 4);
    return 2;
}

/* Remove every entity whose flag bits 37-38 are 2 (func_001d6c80), or
 * whose kind is 300-350 (func_001d6cf0). */
s32 func_001d6c80(void) {
    struct VmObj *p;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (((p->f370.flags >> 37) & 3) == 2) {
            func_001248e8(p->x4);
        }
    }
    return 2;
}

s32 func_001d6cf0(VmRec *vm) {
    struct VmObj *p;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if (func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) func_001248e8(p->x4);
    }
    return 2;
}

/* ---- 0x001d6d60-0x001d7678 ---- */

s32 func_00141608(struct VmObj *, s32);
s32 func_00131de0(s32, s32);
void func_00124218(s32);
s32 func_00125a00(s32);
s32 func_001ef7b0(s32);
s32 func_00112c20(s32);
f32 func_001e9e58(f32 *, f32 *);
s32 func_0014e510(s32);
s32 func_001331d8(s32, s32, void *);

s32 func_001d6d60(VmRec *vm) {
    struct VmObj *o = vm->obj;
    if (o != 0) {
        func_00141608(o, vm->stk[vm->sp]);
    }
    vm->sp--;
    return 2;
}

s32 func_001d6db0(void) {
    D_002C5958 &= ~0x800;
    return 2;
}

s32 func_001d6dd0(void) {
    D_002C5958 |= 0x800;
    return 2;
}

s32 func_001d6df0(void) {
    D_002C5958 &= ~0x200;
    return 2;
}

s32 func_001d6e10(void) {
    D_002C5958 |= 0x200;
    return 2;
}

s32 func_001d6e30(void) {
    D_002C5958 &= ~0x400;
    return 2;
}

s32 func_001d6e50(void) {
    D_002C5958 |= 0x400;
    return 2;
}

/* Remove every entity func_00131de0 finds for stk[sp]. */
s32 func_001d6e70(VmRec *vm) {
    s32 i = -1;
    while ((i = func_00131de0(i, vm->stk[vm->sp])) != -1) func_00124218(i);
    vm->sp--;
    return 2;
}

s32 func_001d6ef0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = func_00125a00(1);
    return 2;
}

s32 func_001d6f38(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038D010;
    return 2;
}

s32 func_001d6f60(void) {
    D_0038D010 = 0;
    return 2;
}

s32 func_001d6f70(void) {
    D_002C5958 |= 0x1000;
    return 2;
}

s32 func_001d6f90(void) {
    D_002C5958 &= ~0x1000;
    return 2;
}

s32 func_001d6fb0(VmRec *vm) {
    func_001ef7b0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d6ff8(VmRec *vm) {
    func_00112c20(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

/* Message 7 (func_001d7040) or 6 (func_001d7118) to every entity of kind
 * 300-350 or 400-539. */
s32 func_001d7040(VmRec *vm) {
    VmMsg m;
    struct VmObj *p;
    m.type = 7;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) ||
            (func_00123618(p->x4) >= 400 && func_00123618(p->x4) < 540)) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}

s32 func_001d7118(VmRec *vm) {
    VmMsg m;
    struct VmObj *p;
    m.type = 6;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) ||
            (func_00123618(p->x4) >= 400 && func_00123618(p->x4) < 540)) {
            m.x = p->x4;
            func_001c4640(&m);
        }
    }
    return 2;
}

void func_001d71f0(void) {
    D_00389C90.f3070.x &= ~0x1000000000000000ULL;
}

s32 func_001d7220(VmRec *vm) {
    vm->sp--;
    return 2;
}

s32 func_001d7238(VmRec *vm) {
    if ((s32)(D_0038CD00 >> 60) & 1) return 4;
    return 2;
}

/* Message 39 with the point 20 below the entity. */
s32 func_001d7258(VmRec *vm) {
    VmMsg m;
    struct VmObj *o = vm->obj;
    if (o) {
        m.x = vm->x0;
        m.type = 39;
        m.val = 0;
        m.v[0] = o->pos[0];
        m.v[1] = o->pos[1] - 20.0f;
        m.v[2] = o->pos[2];
        m.v[3] = 1.0f;
        func_001c4640(&m);
    }
    return 2;
}

s32 func_001d72e0(VmRec *vm) {
    vm->fl.x |= 0x4000;
    vm->f330 = (f32)vm->stk[vm->sp] * 2;
    vm->sp--;
    return 2;
}

/* Push the distance to the nearest entity of kind 300-350 or 400-539 (-1
 * if none). */
s32 func_001d7320(VmRec *vm) {
    struct VmObj *p;
    s32 found = 0;
    f32 best = -1.0f;
    f32 d;
    for (p = func_001230a0(0); p; p = func_001230a0(p)) {
        if ((func_00123618(p->x4) >= 300 && func_00123618(p->x4) < 351) ||
            (func_00123618(p->x4) >= 400 && func_00123618(p->x4) < 540)) {
            if (!found) {
                found = 1;
                best = func_001e9e58(vm->obj->pos, p->pos);
            } else {
                d = func_001e9e58(vm->obj->pos, p->pos);
                if (d < best) best = d;
            }
        }
    }
    vm->sp++;
    vm->stk[vm->sp] = best;
    return 2;
}

/* Give the entity a slot (free or its own) of the eight at 0x3384: snd and
 * x10 (func_001d7438), or h (func_001d74b8).  Kept h17's view of the slots
 * with obj as a pointer: a pointer store does not alias vm->sp (VmSlot's
 * s32 obj loads sp after the store), and a cast of &e[i].obj folds the
 * slot base into one constant. */
typedef struct { struct VmObj *obj; s32 x4, snd, ret, x10, h; } VmSlotP;
typedef struct { u8 pad0[0x3384]; VmSlotP e[8]; } VmMgrSlotP;
#define SLOT(i) (((VmMgrSlotP *)&D_00389C90)->e[i])
s32 func_001d7438(VmRec *vm) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (SLOT(i).obj == 0 || SLOT(i).obj == vm->obj) {
            SLOT(i).obj = vm->obj;
            SLOT(i).snd = vm->stk[vm->sp - 1];
            SLOT(i).x10 = vm->stk[vm->sp];
            break;
        }
    }
    vm->sp -= 2;
    return 2;
}

s32 func_001d74b8(VmRec *vm) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (SLOT(i).obj == 0 || SLOT(i).obj == vm->obj) {
            SLOT(i).obj = vm->obj;
            SLOT(i).h = vm->stk[vm->sp];
            break;
        }
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001d7520(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = D_0038D0D4;
    return 2;
}

s32 func_001d7548(VmRec *vm) {
    vm->stk[vm->sp] = func_0014e510(vm->stk[vm->sp]);
    return 2;
}

void func_001d75a0(void) {
    D_00389C90.f3070.x &= ~0x2000000000000000ULL;
}

s32 func_001d75d0(VmRec *vm) {
    if (func_001331d8(vm->stk[vm->sp - 1], vm->stk[vm->sp], func_001d75a0)) {
        D_00389C90.f3070.x &= ~0x2000000000000000ULL;
    } else {
        D_00389C90.f3070.x |= 0x2000000000000000ULL;
    }
    vm->sp -= 2;
    return 2;
}

/* ---- 0x001d7678-0x001d8680 ---- */

void func_0013c108(s32, s32);
s32 func_0013c188(s32, s32);
s32 func_00132fe0(s32);
void func_00131f40(s32, void *);
s32 func_001566a8(s32);
s32 func_00156678(s32);

s32 func_001d7678(VmRec *vm) {
    func_0013c108(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d76c8(void) {
    if ((s32)(D_0038CD00 >> 61) & 1) return 4;
    return 2;
}

s32 func_001d76e8(VmRec *vm) {
    if (func_0013c188(0, vm->stk[vm->sp]) == 0) {
        vm->stk[vm->sp] = 0;
    } else {
        vm->stk[vm->sp] = func_00132fe0(vm->stk[vm->sp]);
    }
    return 2;
}

void func_001d7768(void) {
    D_00389C90.f3070.x &= ~0x4000000000000000ULL;
}

s32 func_001d7798(VmRec *vm) {
    if (func_0011e340(0) == 0) {
        D_00389C90.f3070.x |= 0x4000000000000000ULL;
        func_00131f40(vm->stk[vm->sp], func_001d7768);
    } else {
        return 4;
    }
    vm->sp--;
    return 2;
}

s32 func_001d7820(void) {
    if ((s32)(D_0038CD00 >> 62) & 1) return 4;
    return 2;
}

/* Set ret of the entity's slots to stk[sp]. */
s32 func_001d7840(VmRec *vm) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if ((s32)vm->obj == D_00389C90.e[i].obj) {
            D_00389C90.e[i].ret = vm->stk[vm->sp];
        }
    }
    vm->sp--;
    return 2;
}

/* func_001d7898 and func_001d7b88 are in vm_lib.nofill.c. */

/* Save block 1's four lists at 0xa80 (10, 10, 10 and 50 bytes; 0 is a free
 * entry). */
typedef struct { u8 pad[0xa80]; u8 l0[10]; u8 l1[10]; u8 l2[10]; u8 l3[50]; } VmSave1;

/* Free entry stk[sp] - 1 of list stk[sp-1]: if an earlier entry is free,
 * nothing; else close the gaps and open one at that place. */
#define D7EF8_BODY(B, N) \
    for (i = 0; i < N; i++) { \
        if (B[i] == 0 && vm->stk[vm->sp] - 1 >= i) { vm->sp -= 2; return 2; } \
    } \
    for (i = 0; i < N; i++) { \
        if (B[i] == 0) { \
            for (k = i; k < N - 1; k++) B[k] = B[k + 1]; \
        } \
    } \
    for (i = 0; i < N; i++) { \
        if (i == vm->stk[vm->sp] - 1) { \
            for (k = N - 1; i < k; k--) B[k] = B[k - 1]; \
            B[i] = 0; \
            break; \
        } \
    } \
    break;

s32 func_001d7ef8(VmRec *vm) {
    VmSave1 *r = (VmSave1 *)func_00232cc0(1);
    s32 sp = vm->sp;
    s32 i, k;

    switch (vm->stk[sp - 1]) {
    case 0: D7EF8_BODY(r->l0, 10)
    case 1: D7EF8_BODY(r->l1, 10)
    case 2: D7EF8_BODY(r->l2, 10)
    case 3: D7EF8_BODY(r->l3, 50)
    }
    vm->sp -= 2;
    return 2;
}

/* Push the first free entry (1-based) of list stk[sp]. */
s32 func_001d8400(VmRec *vm) {
    VmSave1 *p = (VmSave1 *)func_00232cc0(1);
    s32 i;
    switch (vm->stk[vm->sp]) {
    case 0:
        for (i = 0; i < 10; i++) if (!p->l0[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    case 1:
        for (i = 0; i < 10; i++) if (!p->l1[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    case 2:
        for (i = 0; i < 10; i++) if (!p->l2[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    case 3:
        for (i = 0; i < 50; i++) if (!p->l3[i]) { vm->stk[vm->sp] = i + 1; break; }
        break;
    }
    return 2;
}

s32 func_001d85a8(VmRec *vm) {
    func_001566a8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d85f0(VmRec *vm) {
    func_00156678(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8638(void) {
    D_002C5958 &= 0xFFFF7FFF;
    return 2;
}

s32 func_001d8660(void) {
    D_002C5958 |= 0x8000;
    return 2;
}

/* ---- 0x001d8680-0x001d8f38 ---- */

s32 func_001586d8(s32);
s32 func_0013c250(s32);
s32 func_0013c260(s32);
s32 func_0013c1b8(s32);
s32 func_00149eb8(s32);
s32 func_00114800();
s32 func_00114810();
s32 func_00112e08();
s32 func_00111090(void);
s32 func_00111020(s32);
s32 func_00111060();
void func_001116b0(s32, s32);
s32 func_001422b0(s32);
void func_0013c2a0(s32, s32);
s32 func_0013c2f0(s32);
s32 func_00156c28(s32);
void func_001054d0(s32, s32, s32);
void func_00105710(s32, s32);
void func_00105760(s32, s32);
s32 func_001ee200();
s32 func_001124c0();
s32 func_001124d8();

/* Message 40 to this VM (func_001d8680), or with no target (func_001d86e0). */
s32 func_001d8680(VmRec *vm) {
    VmMsg m;
    m.type = 40;
    m.val = 0;
    m.x = vm->x0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    return 2;
}

s32 func_001d86e0(void) {
    VmMsg m;
    m.type = 40;
    m.val = 0;
    m.v[0] = 0.0f;
    m.v[1] = 0.0f;
    m.v[2] = 0.0f;
    m.v[3] = 1.0f;
    func_001c4640(&m);
    return 2;
}

s32 func_001d8738(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = vm->x324;
    return 2;
}

s32 func_001d8760(VmRec *vm) {
    vm->stk[vm->sp] = func_001586d8(vm->stk[vm->sp]);
    return 2;
}

s32 func_001d87b8(void) {
    D_00389C90.f3078.x |= 1;
    return 2;
}

s32 func_001d87d8(void) {
    D_00389C90.f3078.x &= ~1;
    D_0037A378 &= ~1;
    D_002BBE00 = 1.0f;
    D_002C5958 &= ~0x400;
    return 2;
}

/* Remove the entities func_00131de0 finds for stk[sp] that exist. */
s32 func_001d8838(VmRec *vm) {
    s32 r = -1;
    while ((r = func_00131de0(r, vm->stk[vm->sp])) != -1) {
        if (func_00123488(r) != 0) func_001248e8(r);
    }
    vm->sp--;
    return 2;
}

s32 func_001d88c8(VmRec *vm) {
    func_0013c250(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8910(VmRec *vm) {
    func_0013c260(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8958(VmRec *vm) {
    func_0013c1b8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d89a0(VmRec *vm) {
    if (vm->stk[vm->sp] != 0) {
        func_0012cac8(3, 1);
    } else {
        func_0012cac8(3, 0);
    }
    vm->sp--;
    return 2;
}

s32 func_001d8a00(VmRec *vm) {
    if (vm->stk[vm->sp] != 0) {
        func_0012cac8(4, 1);
    } else {
        func_0012cac8(4, 0);
    }
    vm->sp--;
    return 2;
}

s32 func_001d8a60(VmRec *vm) {
    if (vm->stk[vm->sp] != 0) {
        func_0012cac8(5, 1);
    } else {
        func_0012cac8(5, 0);
    }
    vm->sp--;
    return 2;
}

s32 func_001d8ac0(VmRec *vm) {
    func_00149eb8(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8b08(void) {
    func_00114800();
    return 2;
}

s32 func_001d8b28(void) {
    func_00114810();
    return 2;
}

s32 func_001d8b48(void) {
    func_00112e08();
    return 2;
}

s32 func_001d8b68(void) {
    if (func_00111090() == 2) return 2;
    return 4;
}

s32 func_001d8b98(VmRec *vm) {
    func_00111020(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8be0(void) {
    func_00111060();
    return 2;
}

s32 func_001d8c00(void) {
    if (func_00111090() != 4) return 4;
    return 2;
}

s32 func_001d8c30(VmRec *vm) {
    func_001116b0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d8c80(VmRec *vm) {
    func_001422b0(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8cc8(VmRec *vm) {
    func_0013c2a0(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d8d18(VmRec *vm) {
    vm->stk[vm->sp] = func_0013c2f0(vm->stk[vm->sp]);
    return 2;
}

s32 func_001d8d70(VmRec *vm) {
    func_00156c28(vm->stk[vm->sp]);
    vm->sp--;
    return 2;
}

s32 func_001d8db8(VmRec *vm) {
    func_001054d0(vm->stk[vm->sp - 2], vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 3;
    return 2;
}

s32 func_001d8e10(VmRec *vm) {
    func_00105710(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d8e60(VmRec *vm) {
    func_00105760(vm->stk[vm->sp - 1], vm->stk[vm->sp]);
    vm->sp -= 2;
    return 2;
}

s32 func_001d8eb0(VmRec *vm) {
    vm->sp++;
    vm->stk[vm->sp] = func_001ee200();
    return 2;
}

s32 func_001d8ef8(void) {
    func_001124c0();
    return 2;
}

s32 func_001d8f18(void) {
    func_001124d8();
    return 2;
}

/* ---- 0x001d8f38-0x001d9480 ---- */

/* Step the camera tween func_001d9100 starts: D_002BC0F0 from c0 to c1
 * over cdur. */
void func_001d8f38(void) {
    VmMgr *g = &D_00389C90;
    f32 r, t;
    t = g->ct + D_002BBDFC;
    g->ct = t;
    if (g->cdur < t) {
        D_002BC0F0.camS = g->c1;
        g->f3078.x &= ~2ULL;
        return;
    }
    r = g->ct / g->cdur;
    D_002BC0F0.camS.b[0] = g->c0.b[0] + (g->c1.b[0] - g->c0.b[0]) * r;
    g->ct += D_002BBDFC;
    D_002BC0F0.camS.b[1] = g->c0.b[1] + (g->c1.b[1] - g->c0.b[1]) * r;
    D_002BC0F0.camS.b[2] = g->c0.b[2] + (g->c1.b[2] - g->c0.b[2]) * r;
    D_002BC0F0.camS.a[0] = g->c0.a[0] + (g->c1.a[0] - g->c0.a[0]) * r;
    D_002BC0F0.camS.a[1] = g->c0.a[1] + (g->c1.a[1] - g->c0.a[1]) * r;
    D_002BC0F0.camS.a[2] = g->c0.a[2] + (g->c1.a[2] - g->c0.a[2]) * r;
    D_002BC0F0.camS.a[3] = g->c0.a[3] + (g->c1.a[3] - g->c0.a[3]) * r;
    if (g->cdur < g->ct) {
        D_002BC0F0.camS = g->c1;
        g->f3078.x &= ~2ULL;
    }
}

/* Start a camera tween to stk[sp-6..sp] over stk[sp-7] frames. */
s32 func_001d9100(VmRec *vm) {
    VmMgr *g = &D_00389C90;
    g->c1 = g->c0 = D_002BC0F0.camS;
    g->ct = 0.0f;
    g->cdur = vm->stk[vm->sp - 7] * 2.0f;
    g->c1.b[0] = vm->stk[vm->sp - 6];
    g->c1.b[1] = vm->stk[vm->sp - 5];
    g->c1.b[2] = vm->stk[vm->sp - 4];
    g->c1.a[0] = vm->stk[vm->sp - 2];
    g->c1.a[1] = vm->stk[vm->sp - 3];
    g->c1.a[2] = vm->stk[vm->sp - 1];
    g->c1.a[3] = vm->stk[vm->sp];
    if (g->cdur < 2.0f) {
        D_002BC0F0.camS.b[0] = g->c1.b[0];
        D_002BC0F0.camS.b[1] = g->c1.b[1];
        D_002BC0F0.camS.b[2] = g->c1.b[2];
        D_002BC0F0.camS.a[0] = g->c1.a[0];
        D_002BC0F0.camS.a[1] = g->c1.a[1];
        D_002BC0F0.camS.a[2] = g->c1.a[2];
        D_002BC0F0.camS.a[3] = g->c1.a[3];
        g->f3078.x &= ~2ULL;
    } else {
        g->f3078.x |= 2;
    }
    vm->sp -= 8;
    return 2;
}

/* Start a tween from D_002BC0F0 to D_002BC0C0 over stk[sp] frames.  Kept
 * s8_w1's view of D_00389C90 (the camera settings as B48 unions, the flags
 * as a union): the unions alias vm->sp, which keeps it after the copies;
 * through VmMgr (a cast of &c0 / &c1) the copy addresses fold into
 * constants. */
typedef struct {
    u8 pad0[0x3078];
    union { u64 x; s32 i[2]; } flags;
    u8 pad3080[0x3460 - 0x3080];
    f32 cdur;
    f32 ct;
    u8 pad3468[8];
    B48_2BC0C0 c0;
    B48_2BC0C0 c1;
} VmMgrB48;
#define MGRB (*(VmMgrB48 *)&D_00389C90)

s32 func_001d9268(VmRec *vm) {
    f32 x;
    s32 i;
    MGRB.c1 = D_002BC0C0.b48;
    MGRB.c0 = D_002BC0F0.b48;
    i = vm->sp;
    MGRB.ct = 0;
    x = vm->stk[i] * 2.0f;
    MGRB.flags.x |= 2;
    vm->sp--;
    MGRB.cdur = x;
    return 2;
}

/* func_001d9348 is in vm_lib.nofill.c. */

/* ---- the table and the dispatcher ---- */



s32 func_001c6d08();
s32 func_001c71e8();
s32 func_001c7700();
s32 func_001c7c18();
s32 func_001c8168();
s32 func_001c8260();
s32 func_001c8308();
s32 func_001c83c8();
s32 func_001c8420();
s32 func_001c8478();
s32 func_001c84c8();
s32 func_001c8518();
s32 func_001c8568();
s32 func_001c85d8();
s32 func_001c8648();
s32 func_001c86b8();
s32 func_001c8708();
s32 func_001c8878();
s32 func_001c8a00();
s32 func_001c8c90();
s32 func_001c8d98();
s32 func_001c91e8();
s32 func_001c92e8();
s32 func_001c9db0();
s32 func_001c9e20();
s32 func_001ca0f8();
s32 func_001ca368();
s32 func_001ca5f8();
s32 func_001ca680();
s32 func_001ca708();
s32 func_001ca790();
s32 func_001ca7c8();
s32 func_001cac98();
s32 func_001cae00();
s32 func_001cae78();
s32 func_001cb120();
s32 func_001cb3c0();
s32 func_001cb440();
s32 func_001cb738();
s32 func_001cb7d0();
s32 func_001cb960();
s32 func_001cbbd0();
s32 func_001cbfc0();
s32 func_001cc170();
s32 func_001cc1c0();
s32 func_001cc210();
s32 func_001cc260();
s32 func_001cc2c8();
s32 func_001cc330();
s32 func_001cc380();
s32 func_001cc3d0();
s32 func_001cc420();
s32 func_001cc470();
s32 func_001cc508();
s32 func_001cc548();
s32 func_001cc628();
s32 func_001cc640();
s32 func_001ccbd8();
s32 func_001ccbf8();
s32 func_001cccf0();
s32 func_001ccda8();
s32 func_001ccdf0();
s32 func_001cd280();
s32 func_001cd2c0();
s32 func_001cd2d8();
s32 func_001cd600();
s32 func_001cd6b8();
s32 func_001cd740();
s32 func_001cd748();
s32 func_001cd778();
s32 func_001cd7e0();
s32 func_001cd7e8();
s32 func_001cd830();
s32 func_001cd8b0();
s32 func_001cd8e0();
s32 func_001cd910();
s32 func_001cd940();
s32 func_001cd9e8();
s32 func_001cda18();
s32 func_001cda60();
s32 func_001cdaa8();
s32 func_001cdaf0();
s32 func_001cdb38();
s32 func_001cdb80();
s32 func_001cdbc8();
s32 func_001cdc58();
s32 func_001cdcb8();
s32 func_001cdd18();
s32 func_001cdd60();
s32 func_001cdda8();
s32 func_001cddf0();
s32 func_001cde38();
s32 func_001cdea8();
s32 func_001cded0();
s32 func_001cdf00();
s32 func_001cdf98();
s32 func_001ce020();
s32 func_001ce0b8();
s32 func_001ce150();
s32 func_001ce1a8();
s32 func_001ce240();
s32 func_001ce298();
s32 func_001ce2e8();
s32 func_001ce320();
s32 func_001ce358();
s32 func_001ce390();
s32 func_001ce3c0();
s32 func_001ce400();
s32 func_001ce440();
s32 func_001ce5f0();
s32 func_001ce750();
s32 func_001ce880();
s32 func_001ce9b0();
s32 func_001cea38();
s32 func_001ceac0();
s32 func_001ceb08();
s32 func_001ceb78();
s32 func_001cec68();
s32 func_001ceda0();
s32 func_001cede8();
s32 func_001cee90();
s32 func_001ceee8();
s32 func_001cef20();
s32 func_001cef80();
s32 func_001cefb8();
s32 func_001cf018();
s32 func_001cf0c8();
s32 func_001cf110();
s32 func_001cf210();
s32 func_001cf300();
s32 func_001cf478();
s32 func_001cf5d0();
s32 func_001cf728();
s32 func_001cf7a0();
s32 func_001cf838();
s32 func_001cf890();
s32 func_001cf8e8();
s32 func_001cf940();
s32 func_001cf960();
s32 func_001cfa58();
s32 func_001cfa78();
s32 func_001cfad0();
s32 func_001cfb00();
s32 func_001cfb48();
s32 func_001cfb90();
s32 func_001cfc28();
s32 func_001cfd30();
s32 func_001cfdd8();
s32 func_001cfe98();
s32 func_001cfeb8();
s32 func_001cfed8();
s32 func_001cff08();
s32 func_001cff80();
s32 func_001d0070();
s32 func_001d0138();
s32 func_001d0170();
s32 func_001d01a8();
s32 func_001d01c8();
s32 func_001d01e8();
s32 func_001d02d0();
s32 func_001d0380();
s32 func_001d0440();
s32 func_001d0468();
s32 func_001d0490();
s32 func_001d04b8();
s32 func_001d0500();
s32 func_001d0548();
s32 func_001d05a0();
s32 func_001d0600();
s32 func_001d0660();
s32 func_001d0680();
s32 func_001d06b8();
s32 func_001d06f0();
s32 func_001d07a8();
s32 func_001d07e0();
s32 func_001d0818();
s32 func_001d0868();
s32 func_001d0908();
s32 func_001d0938();
s32 func_001d09d8();
s32 func_001d0a28();
s32 func_001d0a38();
s32 func_001d0a80();
s32 func_001d0ac8();
s32 func_001d0b10();
s32 func_001d0b68();
s32 func_001d0b90();
s32 func_001d0dd0();
s32 func_001d1010();
s32 func_001d1230();
s32 func_001d12b8();
s32 func_001d1348();
s32 func_001d1380();
s32 func_001d13c0();
s32 func_001d13e0();
s32 func_001d1400();
s32 func_001d1418();
s32 func_001d1428();
s32 func_001d1450();
s32 func_001d1478();
s32 func_001d14a0();
s32 func_001d14c8();
s32 func_001d14f0();
s32 func_001d1640();
s32 func_001d16a8();
s32 func_001d16c8();
s32 func_001d1728();
s32 func_001d1790();
s32 func_001d17d0();
s32 func_001d1890();
s32 func_001d1948();
s32 func_001d1a28();
s32 func_001d1b00();
s32 func_001d1bf8();
s32 func_001d1ce0();
s32 func_001d1df0();
s32 func_001d1ef0();
s32 func_001d1f48();
s32 func_001d1fb0();
s32 func_001d2018();
s32 func_001d2080();
s32 func_001d2088();
s32 func_001d2090();
s32 func_001d2270();
s32 func_001d2468();
s32 func_001d24b0();
s32 func_001d24f8();
s32 func_001d2540();
s32 func_001d2588();
s32 func_001d25d8();
s32 func_001d2628();
s32 func_001d2668();
s32 func_001d2708();
s32 func_001d2720();
s32 func_001d2768();
s32 func_001d2860();
s32 func_001d2958();
s32 func_001d2ab8();
s32 func_001d2b58();
s32 func_001d2c08();
s32 func_001d2c68();
s32 func_001d2fd8();
s32 func_001d3040();
s32 func_001d3078();
s32 func_001d30e0();
s32 func_001d3118();
s32 func_001d31d8();
s32 func_001d3228();
s32 func_001d3248();
s32 func_001d3268();
s32 func_001d32a8();
s32 func_001d32f0();
s32 func_001d3338();
s32 func_001d3380();
s32 func_001d33c8();
s32 func_001d3430();
s32 func_001d3468();
s32 func_001d3490();
s32 func_001d34b0();
s32 func_001d3558();
s32 func_001d35a0();
s32 func_001d3610();
s32 func_001d3710();
s32 func_001d3828();
s32 func_001d3858();
s32 func_001d38d0();
s32 func_001d3948();
s32 func_001d39b0();
s32 func_001d3a28();
s32 func_001d3a48();
s32 func_001d3a78();
s32 func_001d3aa8();
s32 func_001d3b20();
s32 func_001d3b80();
s32 func_001d3bb0();
s32 func_001d3be8();
s32 func_001d3c28();
s32 func_001d3c70();
s32 func_001d3cb8();
s32 func_001d3d08();
s32 func_001d3d58();
s32 func_001d3da8();
s32 func_001d3de8();
s32 func_001d3e08();
s32 func_001d3ff0();
s32 func_001d40b0();
s32 func_001d40f0();
s32 func_001d4168();
s32 func_001d41e0();
s32 func_001d4258();
s32 func_001d42f0();
s32 func_001d4358();
s32 func_001d43d8();
s32 func_001d4448();
s32 func_001d44b8();
s32 func_001d44f8();
s32 func_001d4538();
s32 func_001d4578();
s32 func_001d4610();
s32 func_001d4690();
s32 func_001d4710();
s32 func_001d4798();
s32 func_001d4ac8();
s32 func_001d4b38();
s32 func_001d4b60();
s32 func_001d4c08();
s32 func_001d4cb8();
s32 func_001d4d68();
s32 func_001d4de0();
s32 func_001d4e10();
s32 func_001d4e38();
s32 func_001d4e60();
s32 func_001d4f10();
s32 func_001d4fc0();
s32 func_001d5010();
s32 func_001d5090();
s32 func_001d5118();
s32 func_001d5168();
s32 func_001d5278();
s32 func_001d52c0();
s32 func_001d5308();
s32 func_001d5330();
s32 func_001d5350();
s32 func_001d5388();
s32 func_001d5408();
s32 func_001d5458();
s32 func_001d54a8();
s32 func_001d54d8();
s32 func_001d5500();
s32 func_001d5528();
s32 func_001d5550();
s32 func_001d5578();
s32 func_001d55a0();
s32 func_001d55c8();
s32 func_001d55f0();
s32 func_001d5618();
s32 func_001d56a8();
s32 func_001d56f0();
s32 func_001d5738();
s32 func_001d5780();
s32 func_001d57d0();
s32 func_001d5828();
s32 func_001d5850();
s32 func_001d5878();
s32 func_001d58a0();
s32 func_001d58c8();
s32 func_001d5978();
s32 func_001d59a0();
s32 func_001d5a50();
s32 func_001d5b00();
s32 func_001d5b58();
s32 func_001d5ed8();
s32 func_001d5f18();
s32 func_001d5f58();
s32 func_001d5f80();
s32 func_001d5fa8();
s32 func_001d5ff0();
s32 func_001d6038();
s32 func_001d6080();
s32 func_001d60c0();
s32 func_001d6100();
s32 func_001d6128();
s32 func_001d6180();
s32 func_001d61c8();
s32 func_001d6210();
s32 func_001d6230();
s32 func_001d6250();
s32 func_001d6348();
s32 func_001d63e8();
s32 func_001d64f8();
s32 func_001d6558();
s32 func_001d65b8();
s32 func_001d6600();
s32 func_001d6628();
s32 func_001d6658();
s32 func_001d66b8();
s32 func_001d66d8();
s32 func_001d66f8();
s32 func_001d6718();
s32 func_001d6760();
s32 func_001d6780();
s32 func_001d67c8();
s32 func_001d6810();
s32 func_001d6858();
s32 func_001d68a0();
s32 func_001d68e8();
s32 func_001d6930();
s32 func_001d6958();
s32 func_001d6978();
s32 func_001d69d0();
s32 func_001d6a20();
s32 func_001d6a40();
s32 func_001d6a60();
s32 func_001d6bf8();
s32 func_001d6c08();
s32 func_001d6c20();
s32 func_001d6c48();
s32 func_001d6c80();
s32 func_001d6cf0();
s32 func_001d6d60();
s32 func_001d6db0();
s32 func_001d6dd0();
s32 func_001d6df0();
s32 func_001d6e10();
s32 func_001d6e30();
s32 func_001d6e50();
s32 func_001d6e70();
s32 func_001d6ef0();
s32 func_001d6f38();
s32 func_001d6f60();
s32 func_001d6f70();
s32 func_001d6f90();
s32 func_001d6fb0();
s32 func_001d6ff8();
s32 func_001d7040();
s32 func_001d7118();
s32 func_001d7220();
s32 func_001d7238();
s32 func_001d7258();
s32 func_001d72e0();
s32 func_001d7320();
s32 func_001d7438();
s32 func_001d74b8();
s32 func_001d7520();
s32 func_001d7548();
s32 func_001d75d0();
s32 func_001d7678();
s32 func_001d76c8();
s32 func_001d76e8();
s32 func_001d7798();
s32 func_001d7820();
s32 func_001d7840();
s32 func_001d7b88();
s32 func_001d7ef8();
s32 func_001d8400();
s32 func_001d85a8();
s32 func_001d85f0();
s32 func_001d8638();
s32 func_001d8660();
s32 func_001d8680();
s32 func_001d86e0();
s32 func_001d8738();
s32 func_001d8760();
s32 func_001d87b8();
s32 func_001d87d8();
s32 func_001d8838();
s32 func_001d88c8();
s32 func_001d8910();
s32 func_001d8958();
s32 func_001d89a0();
s32 func_001d8a00();
s32 func_001d8a60();
s32 func_001d8ac0();
s32 func_001d8b08();
s32 func_001d8b28();
s32 func_001d8b48();
s32 func_001d8b68();
s32 func_001d8b98();
s32 func_001d8be0();
s32 func_001d8c00();
s32 func_001d8c30();
s32 func_001d8c80();
s32 func_001d8cc8();
s32 func_001d8d18();
s32 func_001d8d70();
s32 func_001d8db8();
s32 func_001d8e10();
s32 func_001d8e60();
s32 func_001d8eb0();
s32 func_001d8ef8();
s32 func_001d8f18();
s32 func_001d9100();
s32 func_001d9268();
s32 func_001d9480();
s32 func_001d95f0();
s32 func_001d9728();
s32 func_001d9750();
s32 func_001d9780();
s32 func_001d9830();
s32 func_001d9850();
s32 func_001d9880();
s32 func_001d98d0();
s32 func_001d9950();
s32 func_001d99d0();
s32 func_001d99f8();
s32 func_001d9a50();
s32 func_001d9aa0();
s32 func_001d9af8();
s32 func_001d9b58();
s32 func_001d9bb0();
s32 func_001d9c08();
s32 func_001d9c60();
s32 func_001d9cb0();
s32 func_001d9d30();
s32 func_001d9d90();
s32 func_001d9dd0();
s32 func_001d9df0();
s32 func_001d9e40();
s32 func_001d9e90();
s32 func_001d9eb8();
s32 func_001d9ee0();
s32 func_001d9f20();
s32 func_001d9f88();
s32 func_001d9fb0();
s32 func_001d9ff8();
s32 func_001da040();
s32 func_001da088();
s32 func_001da0e8();
s32 func_001da108();
s32 func_001da128();
s32 func_001da178();
s32 func_001da1a8();
s32 func_001da1d0();
s32 func_001da260();
s32 func_001da2c8();
s32 func_001da3b8();
s32 func_001da400();
s32 func_001da490();
s32 func_001da520();
s32 func_001da5b0();
s32 func_001da628();
s32 func_001da6d0();
s32 func_001da740();
s32 func_001da7b8();
s32 func_001da808();
s32 func_001da860();
s32 func_001da8b8();
s32 func_001da910();
s32 func_001da968();
s32 func_001da9f0();
s32 func_001daa00();
s32 func_001daa18();
s32 func_001daad8();
s32 func_001dab20();
s32 func_001dab48();
s32 func_001dab98();
s32 func_001dabc0();
s32 func_001dabe8();
s32 func_001dac40();
s32 func_001dacc8();
s32 func_001dad30();
s32 func_001dad58();
s32 func_001db018();
s32 func_001db060();
s32 func_001db080();
s32 func_001db0d0();
s32 func_001db140();
s32 func_001db198();
s32 func_001db208();
s32 func_001db278();
s32 func_001db2e0();
s32 func_001db348();
s32 func_001db3b8();
s32 func_001db408();
s32 func_001db458();
s32 func_001db4a8();
s32 func_001db500();
s32 func_001db550();
s32 func_001db5a0();
s32 func_001db5c0();
s32 func_001db5e0();
s32 func_001db600();
s32 func_001db658();
s32 func_001db718();
s32 func_001db888();
s32 func_001db8e0();
s32 func_001db950();
s32 func_001db9c0();
s32 func_001db9f8();
s32 func_001dba30();
s32 func_001dba88();
s32 func_001dbae0();
s32 func_001dbb00();
s32 func_001dbb20();
s32 func_001dbb40();
s32 func_001dbb60();
s32 func_001dbba0();
s32 func_001dbbf0();
s32 func_001dbc10();
s32 func_001dbc38();
s32 func_001dbc90();
s32 func_001dbcd8();
s32 func_001dbd20();
s32 func_001dbd68();
s32 func_001dbdc8();
s32 func_001dbe50();
s32 func_001dbe78();
s32 func_001dbec0();
s32 func_001dbf20();
s32 func_001dbf68();
s32 func_001dbfb8();
s32 func_001dc000();
s32 func_001dc100();
s32 func_001dc120();
s32 func_001dc140();
s32 func_001dc280();
s32 func_001dc2e0();
s32 func_001dc308();
s32 func_001dc358();
s32 func_001dc3c0();
s32 func_001dc470();
s32 func_001dc520();
s32 func_001dc7c0();
s32 func_001dc800();
s32 func_001dc868();
s32 func_001dc8c8();
s32 func_001dc9a0();
s32 func_001dca00();
s32 func_001dca48();
s32 func_001ddc78();
s32 func_001dde08();
s32 func_001ddf98();
s32 func_001ddfb8();
s32 func_001de030();
s32 func_001de0b0();
s32 func_001de130();
s32 func_001de1e0();
s32 func_001de290();
s32 func_001de328();
s32 func_001de420();
s32 func_001de4e8();
s32 func_001de558();
s32 func_001de5b0();
s32 func_001de6a8();
s32 func_001de778();
s32 func_001de848();
s32 func_001de910();
s32 func_001de9e0();
s32 func_001deaf8();
s32 func_001dec10();
s32 func_001ded08();
s32 func_001def20();
s32 func_001df130();
s32 func_001df170();
s32 func_001df1d8();
s32 func_001df268();
s32 func_001df2a8();
s32 func_001df310();
s32 func_001df3a8();
s32 func_001df4a0();
s32 func_001df568();
s32 func_001df5d8();
s32 func_001df630();
s32 func_001df708();
s32 func_001df7e0();
s32 func_001df890();
s32 func_001df940();
s32 func_001df9c0();
s32 func_001dfa38();
s32 func_001dfaa0();
s32 func_001dfb20();
s32 func_001dfbb8();
s32 func_001dfcb0();
s32 func_001dfd78();
s32 func_001dfde0();
s32 func_001dfe50();
s32 func_001dfea8();
s32 func_001dffa0();
s32 func_001e0010();
s32 func_001e0078();
s32 func_001e0220();
s32 func_001e0318();
s32 func_001e0338();
s32 func_001e0498();
s32 func_001e0528();
s32 func_001e16b0();
s32 func_001e1748();
s32 func_001e17e0();
s32 func_001e24c8();
s32 func_001e25c8();
s32 func_001e25e8();
s32 func_001e2628();
s32 func_001e2668();
s32 func_001e26b8();
s32 func_001e3770();
s32 func_001e38b0();
s32 func_001e3dd0();
s32 func_001e3ed0();
s32 func_001e4790();
s32 func_001e4868();
s32 func_001e5d78();
s32 func_001e7488();
s32 func_001e79a0();
s32 func_001e7ad8();
s32 func_001e7e00();
s32 func_001e7ea8();
s32 func_001e7f08();
s32 func_001e80d0();
s32 func_001e8238();
s32 func_001e82e0();
s32 func_001e83f8();
s32 func_001e8560();
s32 func_001e8608();
s32 func_001e8770();
s32 func_001e87b8();
s32 func_001e8800();
s32 func_001e88e0();
s32 func_001e89c0();
s32 func_001e89e0();
s32 func_001e8a10();
s32 func_001e8a30();
s32 func_001e8a50();
s32 func_001e8b08();
s32 func_001e8b50();
s32 func_001e8bc0();
s32 func_001e8bd8();
s32 func_001e8c88();
s32 func_001e8cf0();
s32 func_001e8d40();
s32 func_001e8da0();
s32 func_001e8de8();
s32 func_001e8f68();
s32 func_001e9028();
s32 func_001e9048();
s32 func_001e90c8();
s32 func_001e90d0();
s32 func_001e9108();
s32 func_001e9150();
s32 func_001e9170();
s32 func_001e9190();
s32 func_001e91c0();
s32 func_001e91f0();
s32 func_001e9238();
s32 func_001e9288();
s32 func_001e9310();
s32 func_001ea438();
s32 func_001ea470();
s32 func_001ea580();
s32 func_001ea5f8();
s32 func_001ea658();
s32 func_001ea6b8();
s32 func_001ea760();
s32 func_001ea808();
s32 func_001ea888();
s32 func_001ea908();
s32 func_001ea9c8();
s32 func_001eaa88();
s32 func_001eab78();
s32 func_001eb140();
s32 func_001eb1d8();
s32 func_001eb278();
s32 func_001eb380();
s32 func_001eb4b8();
s32 func_001eb558();
s32 func_001eb698();
s32 func_001eb7b0();
s32 func_001eb910();
s32 func_001eba80();
s32 func_001ebb10();
s32 func_001ebba0();
s32 func_001ebd48();
s32 func_001ebde0();
s32 func_001ebf18();
s32 func_001ebf48();
s32 func_001ebf98();
s32 func_001ebff0();
s32 func_001ec040();
s32 func_001ec0d8();
s32 func_001ec1a0();
s32 func_001ec3b0();
s32 func_001ec3f8();
s32 func_001ec468();
s32 func_001ec678();

VmLibFn D_003D9FE0[0x2fb] ALIGNED(32) = {
    func_001cbbd0, func_001cb960, func_001cae78, func_001cc260,
    func_001cc2c8, func_001cc330, func_001cc380, func_001cc420,
    func_001cd280, func_001cd2c0, func_001ea580, func_001cd2d8,
    func_001cd600, func_001cd6b8, func_001cd740, func_001cd7e0,
    func_001cd8b0, func_001cd8e0, func_001cd910, func_001cd940,
    func_001cd9e8, func_001cda18, func_001cda60, func_001cdaa8,
    func_001cdaf0, func_001cdb38, func_001cdb80, func_001cdd18,
    func_001cdd60, func_001cdda8, func_001cddf0, func_001cde38,
    func_001cded0, func_001cc470, func_001c6d08, func_001c8168,
    func_001c8260, func_001c8308, func_001c83c8, func_001c8420,
    func_001c8478, func_001c84c8, func_001c8518, func_001c8568,
    func_001c85d8, func_001c8648, func_001c86b8, func_001c8708,
    func_001ddfb8, func_001c8878, func_001c8a00, func_001c8c90,
    func_001c8d98, func_001cdbc8, func_001ea5f8, func_001ea658,
    func_001cdc58, func_001cdcb8, func_001cdf00, func_001cdf98,
    func_001ce150, func_001ce298, func_001ce2e8, func_001ce320,
    func_001ce358, func_001ce390, func_001ce3c0, func_001ce400,
    func_001ce440, func_001ce5f0, func_001ce750, func_001ce880,
    func_001ce9b0, func_001ceac0, func_001ceb08, func_001ceb78,
    func_001cec68, func_001ceda0, func_001cede8, func_001cee90,
    func_001cc170, func_001cc1c0, func_001cc210, func_001cc3d0,
    func_001ceee8, func_001cef80, func_001cf018, func_001cf0c8,
    func_001cac98, func_001cae00, func_001cf110, func_001cf300,
    func_001cf478, func_001cf728, func_001cf7a0, func_001cf838,
    func_001cf890, func_001cf8e8, func_001cf940, func_001cf960,
    func_001cfa58, func_001cfa78, func_001c91e8, func_001cfad0,
    func_001cfb00, func_001cfb48, func_001c92e8, func_001cc508,
    func_001cfb90, func_001cfc28, func_001cfd30, func_001cfdd8,
    func_001cfe98, func_001cfeb8, func_001cfed8, func_001cff08,
    func_001cff80, func_001d0070, func_001d0138, func_001d0170,
    func_001d01a8, func_001d01c8, func_001d01e8, func_001d02d0,
    func_001e0338, func_001e0498, func_001d0380, func_001d0440,
    func_001d0468, func_001d0490, func_001ce1a8, func_001ce240,
    func_001d04b8, func_001d0500, func_001d0548, func_001d05a0,
    func_001d0680, func_001d06b8, func_001d06f0, func_001d07a8,
    func_001d07e0, func_001d0818, func_001d0908, func_001d09d8,
    func_001d0a38, func_001d0a80, func_001d0ac8, func_001c71e8,
    func_001c7700, func_001d0b68, func_001d0b90, func_001d0dd0,
    func_001d1010, func_001cc548, func_001ca0f8, func_001cea38,
    func_001ca368, func_001d1230, func_001d1348, func_001d1380,
    func_001d13c0, func_001d13e0, func_001df130, func_001df1d8,
    func_001df268, func_001ddc78, func_001ddf98, func_001df310,
    func_001d1400, func_001d1418, func_001d1428, func_001d1450,
    func_001d1478, func_001d14c8, func_001c7c18, func_001d14f0,
    func_001cc628, func_001cbfc0, func_001def20, func_001cc640,
    func_001ccbd8, func_001d1640, func_001d16a8, func_001d16c8,
    func_001d1728, func_001d1790, func_001df170, func_001df2a8,
    func_001de290, func_001de5b0, func_001e8bd8, func_001e8cf0,
    func_001d17d0, func_001d1948, func_001d1b00, func_001d1ce0,
    func_001dec10, func_001d1ef0, func_001d1f48, func_001d1fb0,
    func_001d2080, func_001d2088, func_001d2090, func_001d2270,
    func_001d2468, func_001d24f8, func_001d2588, func_001d25d8,
    func_001d2628, func_001d2668, func_001d2708, func_001d2720,
    func_001d2768, func_001d2860, func_001cf5d0, func_001e16b0,
    func_001e1748, func_001e17e0, func_001d2958, func_001d2ab8,
    func_001d2b58, func_001d2c08, func_001e3770, func_001e3ed0,
    func_001d2c68, func_001d2fd8, func_001d3040, func_001d3078,
    func_001d30e0, func_001d3118, func_001d31d8, func_001d3228,
    func_001d3248, func_001d3268, func_001d32f0, func_001d3338,
    func_001d33c8, func_001d3430, func_001d3468, func_001d3490,
    func_001d34b0, func_001d3558, func_001d32a8, func_001d35a0,
    func_001e24c8, func_001e25c8, func_001e25e8, func_001e2668,
    func_001e26b8, func_001e83f8, func_001e8608, func_001e7ea8,
    func_001e8770, func_001d3610, func_001de4e8, func_001df568,
    func_001e0220, func_001e0318, func_001d3858, func_001d38d0,
    func_001d39b0, func_001d3a28, func_001d3a48, func_001d3a78,
    func_001d3aa8, func_001d3b20, func_001d3b80, func_001d3bb0,
    func_001e4790, func_001d3c28, func_001d3c70, func_001d3cb8,
    func_001d3d08, func_001d3d58, func_001d3da8, func_001e79a0,
    func_001e7ad8, func_001e7e00, func_001d3de8, func_001d3e08,
    func_001d3ff0, func_001d40b0, func_001e2628, func_001e9310,
    func_001d40f0, func_001d4168, func_001d41e0, func_001d4258,
    func_001d42f0, func_001d4358, func_001d44b8, func_001d44f8,
    func_001d4538, func_001d4578, func_001d4610, func_001d4690,
    func_001d24b0, func_001d2540, func_001d4710, func_001d4798,
    func_001ea438, func_001ea470, func_001d0600, func_001d0660,
    func_001d4ac8, func_001d4b38, func_001d4b60, func_001d4c08,
    func_001d4cb8, func_001d4d68, func_001d4de0, func_001ca5f8,
    func_001ca680, func_001ca708, func_001d4e10, func_001d4e60,
    func_001d4f10, func_001d4fc0, func_001d5010, func_001d5168,
    func_001d5278, func_001d52c0, func_001d5350, func_001d5408,
    func_001d5458, func_001d54a8, func_001d54d8, func_001d5500,
    func_001d5528, func_001d5550, func_001d5578, func_001d55a0,
    func_001d3380, func_001d5618, func_001d56a8, func_001ea808,
    func_001ea888, func_001d56f0, func_001d5738, func_001d5780,
    func_001d57d0, func_001d5828, func_001d5850, func_001d5878,
    func_001d58c8, func_001d5978, func_001d5a50, func_001d59a0,
    func_001df630, func_001df708, func_001d5b00, func_001d5b58,
    func_001d5ed8, func_001e8c88, func_001d5f18, func_001d5f58,
    func_001d5f80, func_001d5fa8, func_001cb738, func_001cb7d0,
    func_001d5ff0, func_001d6038, func_001d6080, func_001d60c0,
    func_001d6100, func_001ccbf8, func_001d6128, func_001d6180,
    func_001d61c8, func_001d6210, func_001d6230, func_001de328,
    func_001de420, func_001df3a8, func_001df4a0, func_001ea908,
    func_001ea9c8, func_001ea6b8, func_001ea760, func_001d3948,
    func_001de558, func_001df5d8, func_001d6250, func_001d6348,
    func_001e8f68, func_001e9028, func_001d63e8, func_001d64f8,
    func_001d6558, func_001d65b8, func_001e90d0, func_001e9108,
    func_001d6600, func_001d3be8, func_001ca790, func_001ca7c8,
    func_001d6658, func_001d66b8, func_001d66d8, func_001d66f8,
    func_001d6718, func_001d6760, func_001d6780, func_001d67c8,
    func_001d5388, func_001e80d0, func_001e82e0, func_001d6810,
    func_001d6858, func_001e9048, func_001e89c0, func_001d6978,
    func_001d69d0, func_001d6a20, func_001d6a40, func_001e89e0,
    func_001d6a60, func_001d6bf8, func_001d6c08, func_001d1890,
    func_001d1a28, func_001d1bf8, func_001d1df0, func_001d6c20,
    func_001d6c48, func_001e9190, func_001d6c80, func_001e8a50,
    func_001d6d60, func_001d6db0, func_001d6dd0, func_001d6df0,
    func_001d6e10, func_001d6e30, func_001d6e50, func_001e9150,
    func_001e9170, func_001d6e70, func_001d6ef0, func_001d6f38,
    func_001d6f60, func_001d6f70, func_001d6f90, func_001e0528,
    func_001d6fb0, func_001d6ff8, func_001de910, func_001ded08,
    func_001d7040, func_001d7118, func_001d7220, func_001d7238,
    func_001d7258, func_001d7320, func_001d7438, func_001d7520,
    func_001e5d78, func_001d7548, func_001d75d0, func_001d76c8,
    func_001d76e8, func_001d7798, func_001d7820, func_001d7840,
    func_001d7b88, func_001d7ef8, func_001d85a8, func_001d85f0,
    func_001d8638, func_001d8660, func_001d8680, func_001d86e0,
    func_001d4e38, func_001d8738, func_001d8760, func_001cccf0,
    func_001d87b8, func_001d87d8, func_001d8838, func_001d88c8,
    func_001d8910, func_001d8958, func_001d89a0, func_001d8a00,
    func_001d8a60, func_001d8ac0, func_001d8b08, func_001d8b28,
    func_001d8b48, func_001d8be0, func_001d8c00, func_001d8c30,
    func_001d8c80, func_001d8cc8, func_001d8d18, func_001d8d70,
    func_001ce020, func_001d6628, func_001d74b8, func_001d8db8,
    func_001d8e10, func_001d8e60, func_001d8eb0, func_001d7678,
    func_001e8b08, func_001e8b50, func_001e8bc0, func_001d8ef8,
    func_001d8f18, func_001d9100, func_001d9268, func_001cd748,
    func_001cd7e8, func_001cd778, func_001cd830, func_001d9480,
    func_001d95f0, func_001d0b10, func_001eb140, func_001eb278,
    func_001eb380, func_001eb4b8, func_001eb698, func_001eb910,
    func_001eba80, func_001ebba0, func_001ebd48, func_001ebde0,
    func_001d9728, func_001eb1d8, func_001ebb10, func_001eb7b0,
    func_001c9db0, func_001c9e20, func_001d9750, func_001df7e0,
    func_001df940, func_001df9c0, func_001dfa38, func_001d9780,
    func_001d9830, func_001d9850, func_001d9880, func_001d98d0,
    func_001d9950, func_001d99d0, func_001d99f8, func_001d9a50,
    func_001d9aa0, func_001d9af8, func_001d9b58, func_001d9bb0,
    func_001d9c08, func_001d9c60, func_001d9cb0, func_001d9d30,
    func_001d9d90, func_001d9dd0, func_001d9df0, func_001d9e40,
    func_001d9e90, func_001d9eb8, func_001d9ee0, func_001d9f88,
    func_001d55c8, func_001d55f0, func_001e8560, func_001e8238,
    func_001d9fb0, func_001d9ff8, func_001da040, func_001da088,
    func_001da0e8, func_001da108, func_001da128, func_001e8da0,
    func_001da178, func_001e90c8, func_001e91f0, func_001e9288,
    func_001e91c0, func_001de030, func_001da1a8, func_001da1d0,
    func_001d8b98, func_001d8b68, func_001ebf98, func_001ebf48,
    func_001d68a0, func_001d68e8, func_001d6930, func_001d6958,
    func_001eaa88, func_001eab78, func_001ec040, func_001ebff0,
    func_001da260, func_001dfaa0, func_001dfb20, func_001dfbb8,
    func_001dfcb0, func_001dfd78, func_001dfde0, func_001dfe50,
    func_001dfea8, func_001cb120, func_001da2c8, func_001e9238,
    func_001df890, func_001dffa0, func_001e0010, func_001e0078,
    func_001ce0b8, func_001da3b8, func_001da400, func_001da490,
    func_001da520, func_001da5b0, func_001da628, func_001de848,
    func_001d6cf0, func_001cdea8, func_001da740, func_001cef20,
    func_001cefb8, func_001d2018, func_001da7b8, func_001da808,
    func_001e38b0, func_001e4868, func_001da860, func_001da8b8,
    func_001da910, func_001ec0d8, func_001ec1a0, func_001d9f20,
    func_001da968, func_001de130, func_001eb558, func_001d5308,
    func_001d5330, func_001d12b8, func_001da9f0, func_001daa00,
    func_001daa18, func_001daad8, func_001dab20, func_001dab48,
    func_001ebf18, func_001dab98, func_001dabc0, func_001e8800,
    func_001e7f08, func_001dabe8, func_001de6a8, func_001de9e0,
    func_001dac40, func_001dacc8, func_001dad30, func_001e8d40,
    func_001dad58, func_001db060, func_001d0a28, func_001db080,
    func_001db0d0, func_001db140, func_001db198, func_001db208,
    func_001db278, func_001db2e0, func_001db348, func_001db3b8,
    func_001db408, func_001e3dd0, func_001db458, func_001db4a8,
    func_001db500, func_001db550, func_001db5a0, func_001db5c0,
    func_001db5e0, func_001ec3f8, func_001ec468, func_001db600,
    func_001db658, func_001db718, func_001db888, func_001db950,
    func_001db9c0, func_001db9f8, func_001dba30, func_001dba88,
    func_001e7488, func_001d8400, func_001db8e0, func_001cb440,
    func_001d43d8, func_001d4448, func_001de0b0, func_001de1e0,
    func_001dbae0, func_001dbb00, func_001dbb20, func_001dbb40,
    func_001d72e0, func_001da6d0, func_001de778, func_001deaf8,
    func_001dbb60, func_001dbba0, func_001dbbf0, func_001dbc10,
    func_001dbc38, func_001dbc90, func_001dbcd8, func_001dbd68,
    func_001dbdc8, func_001dbe50, func_001dbe78, func_001e8a10,
    func_001e8a30, func_001dbec0, func_001dbf20, func_001dbf68,
    func_001dbd20, func_001e87b8, func_001e88e0, func_001dbfb8,
    func_001ec3b0, func_001cf210, func_001e8de8, func_001dc000,
    func_001dc100, func_001dc120, func_001dde08, func_001dc140,
    func_001dc280, func_001d14a0, func_001d0868, func_001d0938,
    func_001ec678, func_001cb3c0, func_001dc2e0, func_001db018,
    func_001dc308, func_001dc358, func_001d58a0, func_001d3828,
    func_001dc3c0, func_001dc470, func_001dc520, func_001dc7c0,
    func_001d3710, func_001ccda8, func_001ccdf0, func_001dc800,
    func_001d5090, func_001d5118, func_001dc868, func_001dc8c8,
    func_001dc9a0, func_001dca00, func_001dca48,
};

s32 func_001dcad0(VmRec *vm, s32 k) {
    return D_003D9FE0[k](vm);
}
