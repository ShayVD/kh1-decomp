/* xl_limit.x func_00f22a70: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; s32 f4; s32 f8; s32 pad[5]; } Ent;
typedef struct { u64 f0; s32 f8; } Obj;
typedef struct { u8 pad[0x370]; u64 f370; } Act;
void func_00176310(s32);
void func_00f22968(s32);
void func_00106a58(s32);
Obj *func_0014a4a8(void *, s32, s32);
s32 func_001477e0(s32);
void func_0014a898(Obj *, void *);
Act *func_001230a0(Act *);
void func_001354b8(Obj *, Act *);
extern s32 D_002C5958;
extern void *D_002E26A0;
extern s32 D_00F23208;
extern Ent D_00F23290[];
extern u8 D_00F23EB0[];
s32 func_00f22a70(void) {
    s32 i;
    Obj *o;
    Act *a;
    for (i = 0; i < 6; i++) {
        if (D_00F23290[i].f8 != 0) {
            func_00176310(D_00F23290[i].f8);
        }
    }
    func_00f22968(4);
    func_00106a58(30);
    D_002C5958 &= ~0x04000000;
    o = func_0014a4a8(D_002E26A0, 0, func_001477e0(16));
    o->f0 |= 0x800000;
    o->f8 = D_00F23208;
    func_0014a898(o, D_00F23EB0);
    o->f0 |= 0x40;
    a = 0;
    while ((a = func_001230a0(a)) != 0) {
        if (((a->f370 >> 37) & 3) == 2) {
            func_001354b8(o, a);
        }
    }
    return 1;
}
