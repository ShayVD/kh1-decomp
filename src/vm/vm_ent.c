/* The entity commands (docs/modules.md "Session 35"), 0x001ea438-0x001eac68.
 *
 * VM library entries (D_003D9FE0 2020-2032) after the vector and text
 * helpers: two script-manager flags (bit 54 of D_00389C90.f3070), the end
 * of a battle or event (func_001ea498: release the player, close the
 * windows and run the script D_003DD320, or restart D_002BCDE4), retarget a
 * VM at another entity (func_001ea580), and messages to the VM itself, to
 * the VM stk[sp] names (func_001e98d0) or to every party entity in range
 * (func_001eaa88 / func_001eab78): types 13 / 14, and 35 + 42 / 36 + 43. */
#include "common.h"
#include "data/types/vm_rec.h"
#include "vm/vm_mgr.h"
#include "vm/script_vm.h"
#include "vm/vm_find.h"
#include "msgwin/msgwin.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_0037A378.h"

/* The player (D_002E26A0[0]): h45's view. */
struct Actor { s32 x0; u8 pad4[0x5c]; f32 f60; f32 f64; };
/* An entity of the list func_001230a0 walks. */
typedef struct { s32 x0; s32 id; } VmEnt;

extern VmMgr D_00389C90;
extern s32 D_002BCDE4;
extern u8 D_003DD320[];

struct VmObj *func_00123488(s32);
VmEnt *func_001230a0(VmEnt *);
s32 func_00123618(s32);

s32 func_001ea438(void);
s32 func_001ea470(void);
void func_001ea498(s32 a);
s32 func_001ea580(VmRec *vm);
s32 func_001ea5f8(VmRec *e);
s32 func_001ea658(VmRec *e);
s32 func_001ea6b8(VmRec *vm);
s32 func_001ea760(VmRec *vm);
s32 func_001ea808(VmRec *e);
s32 func_001ea888(VmRec *e);
s32 func_001ea908(VmRec *vm);
s32 func_001ea9c8(VmRec *vm);
s32 func_001eaa88(void);
s32 func_001eab78(void);

s32 func_001ea438(void) {
    D_00389C90.f3070.x &= ~0x0040000000000000ULL;
    return 2;
}

s32 func_001ea470(void) {
    D_00389C90.f3070.x |= 0x8000LL << 39;
    return 2;
}

void func_001ea498(s32 a) {
    struct Actor *p = D_002E26A0[0];
    p->f60 = 1.0f;
    p->f64 = 0.0f;
    p->x0 |= 1;
    func_001caf58();
    D_00389C90.x34d0 = a;
    if (!((D_00389C90.f3070.x >> 54) & 1)) {
        D_00389C90.f3070.x |= 0x10000000000LL;
        func_001c4198((s8 *)D_003DD320, 0);
        {
            s32 *q = &D_0037A378;
            D_00389C90.f3070.x &= ~0x800000000000000LL;
            *q |= 2;
        }
    } else {
        func_001c2ec8((s8 *)D_002BCDE4, 99);
    }
}

s32 func_001ea580(VmRec *vm) {
    u8 k;

    vm->x0 = vm->stk[vm->sp];
    k = ((u8 *)&vm->x0)[2];     /* the id's kind byte */
    if (k == 1) {
        ((u8 *)&vm->x0)[2] = 0;
    } else if (k == 0) {
        ((u8 *)&vm->x0)[2] = 1;
    }
    vm->obj = func_00123488(vm->x0);
    vm->sp--;
    return 2;
}

s32 func_001ea5f8(VmRec *e) {
    VmMsg m;
    m.type = 13;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea658(VmRec *e) {
    VmMsg m;
    m.type = 14;
    m.val = 0;
    m.v[3] = 1.0f;
    m.v[0] = 0;
    m.v[1] = 0;
    m.v[2] = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea6b8(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 13;
        m.val = 0;
        m.v[3] = 1.0f;
        m.v[0] = 0;
        m.v[1] = 0;
        m.v[2] = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001ea760(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 14;
        m.val = 0;
        m.v[3] = 1.0f;
        m.v[0] = 0;
        m.v[1] = 0;
        m.v[2] = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001ea808(VmRec *e) {
    VmMsg m;
    m.type = 35;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    m.type = 42;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea888(VmRec *e) {
    VmMsg m;
    m.type = 36;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    m.type = 43;
    m.val = 0;
    m.x = e->x0;
    func_001c4640(&m);
    return 2;
}

s32 func_001ea908(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 35;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 42;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001ea9c8(VmRec *vm) {
    VmMsg m;
    VmRec *e = func_001e98d0(vm->fl.b.b5, vm->stk[vm->sp]);
    if (e) {
        m.type = 36;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
        m.type = 43;
        m.val = 0;
        m.x = e->x0;
        func_001c4640(&m);
    }
    vm->sp -= 1;
    return 2;
}

s32 func_001eaa88(void) {
    VmMsg m;
    VmEnt *p = func_001230a0(0);
    while (p) {
        if (func_00123618(p->id) >= 0 && func_00123618(p->id) < 10 && ((u8 *)p)[6] == 3) {
            m.type = 35;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
            m.type = 42;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
        }
        p = func_001230a0(p);
    }
    return 2;
}

s32 func_001eab78(void) {
    VmMsg m;
    VmEnt *p = func_001230a0(0);
    while (p) {
        if (func_00123618(p->id) >= 0 && func_00123618(p->id) < 10 && ((u8 *)p)[6] == 3) {
            m.type = 36;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
            m.type = 43;
            m.val = 0;
            m.x = p->id;
            func_001c4640(&m);
        }
        p = func_001230a0(p);
    }
    return 2;
}

