/* func_00168618 near miss (nostrict, ~80 words): original never sets a0 before its 4 calls (a0 still = o from entry, o also copied to s1); we emit move a0,s0, which shifts every register (o/e swap s0/s1). Not solved. */
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
    if (o->x70 == 2) {
        if (!e->b8) return 0;
        if (!(o->x3B8 <= o->x3B0) && o->x164 != 6) return 0;
        if (D_002C5958 >> 5 & 1) {
            func_0014dcd8(o, e->x120);
            if (o->x70 != 8) return 0;
        } else {
            if ((u16)(o->x130->h4C - 1) >= 2) return 0;
            if (D_002E27C8 >> 8 & 1) func_0014c580(o);
            else if (D_002E27C8 >> 7 & 1) func_0014c530(o);
            else return 0;
            if (o->x70 != 21) return 0;
        }
        e->b8 = 0;
        return 1;
    } else {
        if (e->b8) return 0;
        if (!(D_002C5958 >> 5 & 1)) {
            if ((u16)(o->x130->h4C - 1) >= 2) return 0;
            if (!(D_002E27C8 >> 8 & 1) && !(D_002E27C8 >> 7 & 1)) return 0;
        }
        func_0013dfb8(o, e->x120);
        e->b8 = 1;
        return 0;
    }
}
