/* Party helpers: a member's slot by id (func_0013daa8), the leader
 * (func_0013daf8), the per-class callback table D_00350DA4 (func_0013dfb8),
 * whether the party is together (func_0013dd40 sets bit 0 of D_002C5958),
 * and the name table D_00304BF0 (defined here). Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 53"). */
#include "common.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "m2c.h"
#include "actor.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304BE8.h"
#include "data/types/text_00130000_h7.h"

/* func_0013daa8 (from hand/text_00130000_h7.c). */
typedef struct {
    u8 pad00[0x48];
    s16 x48;
    s16 x4a;
    u16 x4c;
    u8 pad4e[0x54 - 0x4E];
    s8 x54;
    u8 pad55[0x5D - 0x55];
    u8 x5d;
} W7Info;
typedef struct Actor_3daa8 W7Obj;
struct Actor_3daa8 {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W7Info *info;
    u8 pad134[0x398 - 0x134];
    W7Obj *x398;
};
s32 func_0013daa8(u32 id) {
    s32 i;
    for (i = 0; i < 3; i++) {
        W7Obj *o = D_002E26A0[i];
        if (o && o->info->x4c == id) {
            return i;
        }
    }
    return -1;
}

/* func_0013daf8 (from auto/text_00130000_13.c). */
#define func_0013daa8 ((s32 (*)()) func_0013daa8)
s32 func_0013daf8(void) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = func_0013daa8();
    var_v0 = 0;
    if (temp_v0 < 0) {
        return var_v0;
    }
    var_v0 = ((M2C_UNK *)&D_002E26A0)[temp_v0];
    return var_v0;
}
#undef func_0013daa8

/* func_0013db30 (from hand/text_00130000_h7.c). */
typedef struct Actor_3db30 W7Obj_3db30;
struct Actor_3db30 {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W7Info *info;
    u8 pad134[0x398 - 0x134];
    W7Obj_3db30 *x398;
};
s32 func_00137618(W7Obj_3db30 *o);
s32 func_00130030(W7Obj_3db30 *o);
s32 func_0013db30(W7Obj_3db30 *o) {
    s32 r = 0;
    W7Obj_3db30 *p;
    if (func_00137618(o) || func_00130030(o)) {
        p = o->x398;
        if (p == 0 || (p = p->x398) == 0 || p->info->x54 != 10) {
            r = 1;
        }
    }
    return r;
}

/* func_0013dbb0 (from auto/text_00130000_4.c). */
extern M2C_UNK D_00304BF0[];
s32 func_0013dbb0(u32 arg0) {
    if (arg0 < 0xAU) {
        return *(M2C_UNK *)((s8 *)&D_00304BF0 + (arg0 * 4));
    }
    return 0;
}

/* func_0013dbe0 (from auto/text_00130000_4.c). */
extern M2C_UNK D_0052AE70;
s32 func_0013dbe0(void *arg0, s32 arg1) {
    return *(M2C_UNK *)((s8 *)&D_0052AE70 + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) * 4)) + (arg1 * 0x14);
}

/* func_0013df40 (from hand/text_00130000_h7.c). */
void func_0013df40(W7Ob *o, s32 f) {
    if (o->x14c && !(o->flags & 0x4000)) {
        o->x14c->c = -1;
        o->x14c->d = -1;
        o->x14c->e = -1;
        if (f) {
            o->x14c->f = -128;
        } else {
            o->x14c->f = -1;
        }
    }
    o->flags |= 0x4000;
}

/* func_0013dfa0 (from auto/text_00130000.c). */
void func_0013dfa0(Actor *arg0) {
    arg0->unk000 &= ~0x4000;
}

/* func_0013dfb8 (from hand/text_00130000_h7.c). */
extern W7Fn D_00350DA4[];
s32 func_0013dfb8(W7Ob *o, s32 a) {
    s32 r;
    s32 (*fn)(W7Ob *, s32);
    o->x3d0 = 0;
    fn = D_00350DA4[o->x70].fn;
    r = 0;
    if (fn) {
        r = fn(o, a);
    }
    return r;
}


/* Pointer table moved from auto/text_00130000_4.c (session 53; tools/shift/define_ptr_tables.py). */
extern u8 D_0048DDA0[];
extern u8 D_0048DDA8[];
extern u8 D_0048DDB8[];
extern u8 D_0048DDC0[];
extern u8 D_0048DDC8[];
extern u8 D_0048DDD0[];
extern u8 D_0048DDD8[];
extern u8 D_0048DDE0[];
extern u8 D_0048DDE8[];
extern u8 D_0048DDF0[];
M2C_UNK D_00304BF0[0xa] ALIGNED(16) = {
    (s32)D_0048DDF0, (s32)D_0048DDE8, (s32)D_0048DDE0, (s32)D_0048DDD8,
    (s32)D_0048DDD0, (s32)D_0048DDC8, (s32)D_0048DDC0, (s32)D_0048DDB8,
    (s32)D_0048DDA8, (s32)D_0048DDA0,
};
