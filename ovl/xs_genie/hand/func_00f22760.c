/* xs_genie.x func_00f22760: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad0[0x10]; OvlVec pos; u8 pad20[0x10]; OvlVec v30; u8 pad40[0x124]; s32 f164; u8 pad168[0x64]; u32 f1cc; } Act;
typedef struct { Act *act; s32 id; } Cur;
typedef struct { s32 f0; s32 kind; Act *act; Cur cur; } Cmd;
s32 func_00122ff8(Act *);
void func_0012ec60(Act *, s32, f32 *);
void func_00f22530(f32 *, f32 *, f32);
void func_001315c0(Act *, s32, f32 *, f32);
void func_00f221e0(f32 *, Cur *);
void func_00f221a0(f32 *, Cur *);
void func_00f22230(f32 *, Cur *);
void *func_00147ed8(void *, s32, s32, f32 *);
void func_00f21220(s32, f32 *, f32 *, Cur *);
extern Act *D_00F22E90;
extern void *D_00F22E98;
void func_00f22760(Cmd *c) {
    OvlVec hand;
    OvlVec tp;
    Cur *tc;

    if (func_00122ff8(c->cur.act)) {
        tc = &c->cur;
        func_0012ec60(tc->act, tc->id, tp);
    } else {
        tc = NULL;
        PlatVu0CopyVector(tp, c->act->pos);
        func_00f22530(tp, c->act->v30, 500.0f);
        tp[1] = D_00F22E90->pos[1];
    }
    if (!(c->act->f1cc & 0xF0000))
        return;
    switch (c->act->f164) {
    case 200:
    case 210:
    case 211:
    case 212:
    case 213:
    case 214:
        func_001315c0(c->act, 4198, hand, 0.0f);
        break;
    default:
        func_001315c0(c->act, 4117, hand, 0.0f);
        break;
    }
    switch (c->kind) {
    case 1:
        func_00f221e0(tp, tc);
        func_00147ed8(D_00F22E98, 13, 20000, hand);
        break;
    case 2:
        func_00f221a0(tp, tc);
        func_00147ed8(D_00F22E98, 16, 20000, hand);
        break;
    case 3:
        func_00f22230(tp, tc);
        func_00147ed8(D_00F22E98, 21, 20000, hand);
        break;
    case 4:
        func_00f21220(0, c->act->v30, hand, tc);
        func_00147ed8(D_00F22E98, 0, 20000, hand);
        break;
    case 5:
        func_00f21220(1, c->act->v30, hand, tc);
        func_00147ed8(D_00F22E98, 9, 20000, hand);
        break;
    case 6:
        func_00f21220(2, c->act->v30, hand, tc);
        func_00f21220(3, c->act->v30, hand, tc);
        func_00f21220(4, c->act->v30, hand, tc);
        func_00f21220(5, c->act->v30, hand, tc);
        func_00f21220(6, c->act->v30, hand, tc);
        func_00147ed8(D_00F22E98, 4, 20000, hand);
        break;
    }
    c->f0 = 0;
}
