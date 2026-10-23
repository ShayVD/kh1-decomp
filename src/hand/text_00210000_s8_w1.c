#include "common.h"
#include "data/bss_0064.h"
typedef struct Obj { u8 pad[0x10]; struct Obj *x10; u8 p14[0x10]; union { struct Obj *p; s32 i; s16 h; } x24; s32 x28; u8 p2c[0xBA - 0x2C]; s16 xba; u8 pbc[0xCC - 0xBC]; s16 xcc; s16 xce; s16 xd0; s16 xd2; } Obj;
#include "data/pieces/D_00425BC8.h"
typedef struct { u8 pad[0x40]; u8 items[0x30]; } Sub;
typedef struct { u8 pad[4]; Sub sub; } Rec74;
#include "data/pieces/D_00304BE8_s.h"
typedef Save_304be8 S4BE8;
typedef struct { s32 *p; s32 n; } PN;
#include "data/pieces/D_003F34B8.h"
typedef union { s32 i; u16 h; } U32H;
#include "data/pieces/D_003E3D68.h"
extern void *D_00642C90;
extern s32 D_00642C94;
extern s32 D_00642C98;
extern s32 D_00642CCC;
extern u16 D_00642CD0; /* src/data/bss_0064.c: s32 D_00642CD0 */
extern s32 D_00642CD8;
extern U32H D_00642CDC; /* src/data/bss_0064.c: s32 D_00642CDC */
extern U32H D_00642CE0; /* src/data/bss_0064.c: s32 D_00642CE0 */
extern PN D_003F40F8[];
extern s32 D_003F43F0[];
extern u8 D_003F44E0[];
extern u8 D_003F44A0[];
extern u8 D_003F4580[];
extern u8 D_003F4550[];
extern u8 D_003F4520[];
s32 func_001f42b8(void *);
s32 func_001f3758(void *);
void func_0011d768(s32);
void func_001fd858(void *);
void func_0020bd18(void *, s32);
s32 func_001fd518(void *);
s32 func_001fe570(void *);
void func_001f3d58(void *, s32);
Obj *func_001f31a8(u8 *, s32);
void func_001f3e48(Obj *, Obj *);
void func_001f3dc0(Obj *);
s32 func_001ee5f0(s32);
void func_00207870(void *, s32, s32, s32, s32, s32, s32);

/* The table base is read into a pointer first (t, then tn = &t->n) so its lui is the
   earliest insn after the func_001f3d58 call: sched issues the lowest-LUID insn made
   ready by a call in the call's own cycle. */
void func_002177c8(Obj *a) {
    Obj *o[3];
    Obj *p;
    s32 *pc;
    u32 i;
    s32 sel, y;
    if (func_001f42b8(a)) {
        if (D_00425BC8->x8 & 0x4000) {
            func_001f3758(D_00642C90);
            func_0011d768(3);
        } else {
            func_001fd858(a);
            func_0020bd18(a, 8);
            sel = func_001fd518(a);
            pc = &D_00642CCC;
            *pc = sel;
            if (func_001fe570(a)) {
                func_001f3d58(a, 5);
                p = a->x10->x10;
                func_001f3d58(p, 0);
                func_001f3758(a);
                if (*pc == 0) {
                    D_00642C94 = 1;
                    D_00642C98 = D_00304BE8->x48e[0];
                    if ((o[0] = func_001f31a8(D_003F44E0, 0))) {
                        func_001f3e48(o[0], p);
                        func_001f3d58(o[0], 6);
                        o[0]->xd2 = D_00642CD0 << 4;
                        if ((o[1] = func_001f31a8(D_003F44A0, 6))) {
                            func_001f3e48(o[1], o[0]);
                            func_001f3dc0(o[0]);
                        }
                    }
                } else {
                    if ((o[0] = func_001f31a8(D_003F4580, 0))) {
                        S4BE8 **b;
                        s32 *pd;
                        func_001f3e48(o[0], p);
                        b = &D_00304BE8;
                        func_001f3d58(o[0], 6);
                        pd = &D_00642CD8;
                        *pd = D_003F34B8->a[D_00304BE8->x48e[D_00642CCC]];
                        if ((o[1] = func_001f31a8(D_003F4550, 6))) {
                            func_001f3e48(o[1], o[0]);
                            o[1]->x24.i = D_003F43F0[*pd];
                            if ((o[2] = func_001f31a8(D_003F4520, 0))) {
                                u8 *q;
                                U32H *pdc;
                                PN *t;
                                s32 *tn;
                                func_001f3e48(o[2], o[1]);
                                func_001f3d58(o[2], 6);
                                t = D_003F40F8;
                                tn = &t->n;
                                pdc = &D_00642CDC;
                                q = (u8 *)(*pc + (u32)*b) + 0x48e;
                                o[2]->xba = tn[*q * 2] * 416;
                                o[2]->xcc = tn[*q * 2];
                                o[2]->xce = tn[*q * 2];
                                pdc->i = 0;
                                D_00642CE0.i = 0;
                                o[2]->xd2 = pdc->h << 4;
                                o[0]->x24.p = o[2];
                                o[2]->x24.p = o[0];
                                func_001f3dc0(o[0]);
                            }
                        }
                    }
                }
            }
        }
    }
    sel = func_001fd518(a);
    y = 0;
    for (i = 0; i < D_003E3D68; i++) {
        func_00207870(a, i == sel, 2, 0, y, 122, func_001ee5f0(D_00304BE8->x48e[i]));
        y += 28;
    }
}
#include "data/data_003F.h"
