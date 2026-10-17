/* 00168618 hand/nostrict 37w (same size): only o/e s-reg swap (orig o=s1 e=s0) + local temp regs. Keys: no explicit 'return 0' after the || block (lets cse keep a0=o, so no 'move a0' before calls), else-half calls duplicated per path (crossjump merges), per-branch 'x = o->x70; k = 8/21' with shared 'if (x != k)'. */
#include "common.h"
typedef struct { u8 pad[0x4C]; u16 h4C; } Ch130;
typedef struct {
    u8 pad0[0x70];
    s32 x70;
    u8 pad74[0x130 - 0x74];
    Ch130 *x130;
    u8 pad134[0x164 - 0x134];
    s32 x164;
    u8 pad168[0x3B0 - 0x168];
    f32 x3B0;
    f32 x3B4;
    f32 x3B8;
} Obj18;
typedef struct {
    u8 pad0[0x38];
    u32 lo:8;
    u32 b8:1;
    u32 r9:23;
    u32 hi;
    u8 pad40[0x120 - 0x40];
    u8 x120[4];
} __attribute__((aligned(8))) Ent18;
extern u32 D_002C5958;
extern u32 D_002E27C8;
void func_0014dcd8(Obj18 *, void *);
void func_0014c580(Obj18 *);
void func_0014c530(Obj18 *);
void func_0013dfb8(Obj18 *, void *);

s32 func_00168618(Obj18 *o, Ent18 *e) {
    s32 k, x;
    if (o->x70 == 2) {
        if (!e->b8) return 0;
        if (o->x3B0 >= o->x3B8 || o->x164 == 6) {
            if (D_002C5958 >> 5 & 1) {
                func_0014dcd8(o, e->x120);
                x = o->x70; k = 8;
            } else {
                if ((u16)(o->x130->h4C - 1) >= 2) return 0;
                if (D_002E27C8 >> 8 & 1) func_0014c580(o);
                else if (D_002E27C8 >> 7 & 1) func_0014c530(o);
                else return 0;
                x = o->x70; k = 21;
            }
            if (x != k) return 0;
            e->b8 = 0;
            return 1;
        }
    } else {
        if (e->b8) return 0;
        if (D_002C5958 >> 5 & 1) { func_0013dfb8(o, e->x120); e->b8 = 1; return 0; }
        if ((u16)(o->x130->h4C - 1) >= 2) return 0;
        if (D_002E27C8 >> 8 & 1) { func_0013dfb8(o, e->x120); e->b8 = 1; return 0; }
        if (D_002E27C8 >> 7 & 1) { func_0013dfb8(o, e->x120); e->b8 = 1; return 0; }
    }
    return 0;
}
