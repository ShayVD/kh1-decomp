/* Object draw jobs: func_001371f0 queues a draw job on the task list
 * D_0052A100 (func_00136bc0 runs it) with a per-kind draw callback
 * (func_001368e8, func_001369e8, func_00136ab8), func_00136428 draws a model
 * with a colour and alpha, func_001372a0 resets the lists, func_00135ed0 uploads a texture through
 * GIF path 3 and func_00136d38 builds an object's matrix with a ground ray. Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "m2c.h"
#include "actor.h"
#include "vm/script_vm.h"
#include "common.h"
#include "data/bss_0052.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00350CE0.h"
#include "data/types/text_00130000_h32_p.h"
#include "data/pieces/D_00304AD8.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00304B84.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_00304BE8.h"

/* func_001366d8 (from auto/text_00130000_8.c). */
M2C_UNK func_00135df0(void *, void *);
M2C_UNK func_00136428(void *, s32, s32, void *, f32);
M2C_UNK func_00267548(void *, void *, s32);
f32 func_00135ca0(f32);
void func_001366d8(Actor *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    f32 temp_f20;

    temp_f20 = func_00135ca0(arg0->unk118);
    func_00135df0(arg0, sp);
    func_00267548(sp, sp, arg2);
    func_00136428(arg0, ~(1 << (arg1 - 1)), arg0->unk394, sp, temp_f20);
}

/* func_001368e8 (from hand/text_00130000_h32.c). */
typedef struct {
    u32 flags;
    u8 pad004[0x1C - 0x4];
    f32 x1c;
    u8 pad020[0x60 - 0x20];
    f32 x60;
    u8 pad064[0xA0 - 0x64];
    f32 xa0[4];
    u8 pad0b0[0xD0 - 0xB0];
    f32 xd0[4][4];
    f32 x110[2];
    f32 x118;
    f32 x11c;
    u8 pad120[0x154 - 0x120];
    s32 x154;
    u8 pad158[0x350 - 0x158];
    s32 tgt[4];
    u8 pad360[0x370 - 0x360];
    union {
        u64 x;
        u8 c[4];
    } u370;
    u8 pad378[0x38C - 0x378];
    s32 x38c;
    u8 pad390[0x394 - 0x390];
    s32 x394;
} W32Col;
void func_00122588(W32Col *o);
s32 func_00135bb0(W32Col *o);
void func_00128218(W32Col *o, f32 f);
extern f32 D_002C6450[4];
#define func_00267548 ((void (*)(f32 *d, f32 *a, f32 *b)) func_00267548)
#define func_00136428 ((void (*)(W32Col *o, s32 a, s32 b, f32 *c, f32 f)) func_00136428)
void func_001368e8(W32Col *o) {
    f32 v[4] __attribute__((aligned(16)));
    f32 k = func_00135ca0(o->x118);
    func_00122588(o);
    func_00135df0(o, v);
    func_00267548(v, v, D_002C6450);
    if (v[3] > 0.0f && func_00135bb0(o) && (o->flags & 1)) {
        if (D_002BC0A8.i & 1) {
            o->u370.x |= 1ULL << 35;
            if (o->x154 == 0) return;
            func_00136428(o, o->x38c, o->x394, v, k);
        }
    }
    if (o->flags & 2) func_00128218(o, v[3] * k * 3.063725307583809e-05f);
}
#undef func_00267548
#undef func_00136428

/* func_00136ab8 (from hand/text_00130000_h32.c). */
extern s32 D_002BC128;
extern s32 D_002BC130;
#define func_00136428 ((void (*)(W32Col *o, s32 a, s32 b, f32 *c, f32 f)) func_00136428)
void func_00136ab8(W32Col *o) {
    f32 v[4] __attribute__((aligned(16)));
    f32 k = func_00135ca0(o->x118);
    func_00122588(o);
    func_00135df0(o, v);
    if (v[3] > 0.0f && func_00135bb0(o) && (o->flags & 1)) {
        o->u370.x |= 1ULL << 35;
        if (o->x154 == 0) return;
        func_00136428(o, o->x38c, o->x394, v, k);
    }
    if (D_002BC128 == 1 && D_002BC130 == 5) return;
    if (o->flags & 2) func_00128218(o, v[3] * k * 3.063725307583809e-05f);
}
#undef func_00136428

/* func_00136bc0 (from hand/text_00130000_h32.c). */
CONTEXT_ONLY void func_00135d38(W32Col *o) {
    s32 i;
    if ((s32)(o->u370.x >> 46) & 1) {
        for (i = 0; i < 4; i++) {
            u8 *q = &o->u370.c[i];
            s32 cur = *q;
            s32 d = o->tgt[i] - cur;
            s32 c;
                        if (d >= -4) c = cur + (d < 5 ? d : 4);
            else c = cur - 4;
            *q = c;
        }
    } else {
        for (i = 0; i < 4; i++) o->u370.c[i] = o->tgt[i];
    }
    o->u370.x |= 1ULL << 46;
}
typedef struct {
    u8 pad00[0x10];
    W32Col *obj;
    void (*cb)(W32Col *o);
} W32Job;
extern u32 D_002C5958;
void func_00120ef0(f32 *a, void *b, f32 *c);
/* func_00135d38 moved to src/obj/objvis.c (session 53); this CONTEXT_ONLY copy keeps
   func_00136bc0 below matching (without it 3 words differ). */
s32 func_00136bc0(W32Job *j) {
    W32Col *o = j->obj;
    if ((s32)(o->u370.x >> 33) & 1) return 4;
    o->u370.x &= ~(1ULL << 35);
    o->x1c = 1.0f;
    func_00120ef0(o->x110, &D_002E2700, o->xd0[3]);
    o->x11c = 1.0f;
        if (((s32)(o->u370.x >> 34) & 1) && o->x154 != 0 && !((D_002C5958 >> 6) & 1)) {
        func_00135d38(o);
        j->cb(o);
    }
    return 0;
}

/* func_00136c98 (from auto/text_00130000_8.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
extern u8 D_0052A100[];
#define D_0052A100 (*(M2C_UNK (*)) &D_0052A100)
s32 func_00136c98(void) {
    func_0011f130(&D_0052A100, 0);
    return 0;
}
#undef D_0052A100

/* func_00136cc0 (from auto/text_00130000_13.c). */
M2C_UNK func_001318e8(void *, u16, void *);
M2C_UNK func_00267328(void *, void *, void *);
s32 func_00122ff8(void *);
void func_00136cc0(void *arg0) {
    s32 sp[16];
    void *temp_a0;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x3A0);
    if ((func_00122ff8(temp_s1) != 0) && ((s32) ((u64) M2C_FIELD(M2C_FIELD(arg0, void **, 0x3A0), u64 *, 0x370) >> 0x2B) & 1)) {
        func_001318e8(temp_s1, M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x50), sp);
        temp_a0 = arg0 + 0xD0;
        func_00267328(temp_a0, sp, temp_a0);
    }
}

/* func_001371f0 (from hand/text_00130000_h32.c). */
typedef struct {
    u8 pad00[6];
    u8 kind;
} W32Kind;
void *func_0011f090(void *a, s32 b, void *c);
void func_00136768(W32Col *o);
void func_001369e8(W32Col *o);
void func_001371f0(W32Kind *o) {
    W32Job *j = func_0011f090(D_0052A100, 0, func_00136bc0);
    j->obj = (W32Col *)o;
    switch (o->kind) {
    case 4:
    case 9:
        j->cb = func_001368e8;
        break;
    case 5:
    case 10:
        j->cb = func_001369e8;
        break;
    case 8:
        j->cb = func_00136ab8;
        break;
    default:
        j->cb = func_00136768;
        break;
    }
}

/* func_001372a0 (from auto/text_00130000_4.c). */
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK D_00529800[0x240] ALIGNED(64);  /* moved from auto/text_00130000_4.c (session 53) */
s32 func_0011ef38(M2C_UNK *);
#define D_0052A100 (*(M2C_UNK (*)) &D_0052A100)
void func_001372a0(void) {
    func_0011efa8(&D_0052A100, &D_00529800, 0x18, 0x60);
    if (func_0011ef38(&func_00136c98) == 0) {
        func_0011ef10(0x1FBD0, &func_00136c98);
    }
    D_0052A150 = 0;
}
#undef D_0052A100

