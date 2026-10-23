#include "common.h"
#include "vm/script_vm.h"
#include "vm/vm_find.h"
#include "data/bss_0062.h"
#include "data/bss_0063.h"

/* Menu window (0xb0 bytes); D_0062F6E0/D_0062F790/D_0062F840 and
 * D_00630300/D_006303B0/D_00630460 are runs of these. */
#include "data/types/text_001e0000_h45.h"

#include "data/types/text_001e0000_h45_p.h"
typedef struct Actor { s32 x0; u8 pad4[0x5c]; f32 f60; f32 f64; } Obj26;
typedef struct { u8 pad0[0x3070]; u64 f3070; u64 f3078; u8 pad3080[0x450]; s32 f34d0; } Big20;
typedef struct { f32 x, y, z; } Vec3;
typedef struct { s32 x0; s32 id; } Ent88;

/* Message passed to func_001c4640. */

extern Big20 D_00389C90;
extern E212 D_003DB078[];
extern E212 D_003DB718[];
#include "data/pieces/D_002E26A0.h"
extern s32 D_002BCDE4;
#include "data/pieces/D_0037A378.h"
#include "data/pieces/D_003DABD4.h"
extern s32 D_003DD258;
extern s32 D_003DD28C;
extern s32 D_003F7A68;
#include "data/pieces/D_003DBA68.h"
#include "data/pieces/D_003DC390.h"
#include "data/pieces/D_003DCD70.h"
extern u8 D_003DD320[];

Ent88 *func_001230a0(Ent88 *);
s32 func_00123618(s32);
void func_001caf58(void);

/* func_001e31b8, func_001e3600, func_001e3770, func_001e38b0, func_001e3b40, func_001e3c70, func_001e3dd0, func_001e3f20, func_001e4790, func_001e4868 are in src/shop/shop.c. */


/* func_001e4990, func_001e4b08, func_001e4c20, func_001e5810, func_001e6ba8, func_001e6d20, func_001e7800 are in src/list/list.c. */


/* func_001e7f08, func_001e8238, func_001e8560, func_001e8800, func_001e88e0, func_001e8a50, func_001e8bd8, func_001e8f68 are in src/event/sound.c. */


/* func_001e9310 is in src/screen/wave.c. */

void func_001e9fe8(Vec3 *out, Vec3 *in) {
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    while (1) {
        if (out->x > 3.1415928f) out->x -= 6.2831855f;
        else if (out->x < -3.1415928f) out->x += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->y > 3.1415928f) out->y -= 6.2831855f;
        else if (out->y < -3.1415928f) out->y += 6.2831855f;
        else break;
    }
    while (1) {
        if (out->z > 3.1415928f) out->z -= 6.2831855f;
        else if (out->z < -3.1415928f) out->z += 6.2831855f;
        else break;
    }
}

void func_001ea498(s32 a) {
    Obj26 *p = D_002E26A0[0];
    p->f60 = 1.0f;
    p->f64 = 0.0f;
    p->x0 |= 1;
    func_001caf58();
    D_00389C90.f34d0 = a;
    if (!((D_00389C90.f3070 >> 54) & 1)) {
        D_00389C90.f3070 |= 0x10000000000LL;
        func_001c4198((s8 *)D_003DD320, 0);
        {
            s32 *q = &D_0037A378;
            D_00389C90.f3070 &= ~0x800000000000000LL;
            *q |= 2;
        }
    } else {
        func_001c2ec8((s8 *)D_002BCDE4, 99);
    }
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
    Ent88 *p = func_001230a0(0);
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
    Ent88 *p = func_001230a0(0);
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

/* func_001eb698 is in src/save/flags.c. */

#include "data/bss_0063_typed.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_003D.h"
#include "data/data_003F.h"
#include "data/data_0049.h"
#include "data/pieces/D_003DD258.h"
#include "data/pieces/D_003DD28C.h"
#include "data/pieces/D_003F7A68.h"
#include "data/pieces/D_003DB078.h"
#include "data/pieces/D_003DB718.h"
