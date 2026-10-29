/* xs_mushu.x func_00f20550: near miss (session 141), 2 words: the original loads o->eff before D_00F21380 for the src store (ours the other way round). Round 3 (wwm2): a temp (`void *t = D_00F21380; o->eff->src = t;`) gets the load order right but swaps v0/a0 (3 words); store-order permutations, inline setters, casts and every flag mode give nothing better; permuter 10 min found nothing. */
#include "ovl.h"
typedef struct { s32 a, b; } MuPair;
typedef struct {
    u64 b0 : 2;
    u64 kind : 2;
    u64 b4 : 3;
    u64 b7 : 1;
    u64 b8 : 15;
    u64 b23 : 1;
    u64 b24 : 40;
} MuFlags;
typedef struct { MuFlags flags; f32 *src; f32 f12; OvlVec pos; } MuEff;
typedef struct {
    s32 state;
    f32 f4;
    u8 pad8[8];
    OvlVec pos;
    OvlVec v20;
    f32 **obj;
    MuPair pair;
    MuEff *eff;
} Mushu;
typedef struct { u8 pad[2]; u8 b2; } MuB;
extern void *D_00F21380;
extern void *D_00F21384;
extern u8 *D_00F21388;
extern s32 D_00F21390;
extern s32 D_002E31B8;
extern MuPair D_002E31B0;
extern f32 D_00304B7C;
extern MuB *D_00304B70;
void func_00f204e8(f32 *, f32 *, f32);
f32 **func_00147c98(void *, s32, s32);
s32 func_00122ff8(s32);
s32 func_001477e0(s32);
MuEff *func_0014a4a8(void *, s32, s32);
void func_00148968(void *, void *, s32);
void func_00f20550(Mushu *o) {
    s32 v;
    s32 n;
    o->state = 2;
    o->f4 = 30.0f;
    PlatVu0CopyVector(o->v20, D_00F21388 + 0x30);
    o->v20[3] = 0.0f;
    PlatVu0CopyVector(o->pos, D_00F21388 + 0x10);
    func_00f204e8(o->pos, o->v20, 26.881f);
    o->pos[1] += -15.074f;
    o->obj = func_00147c98(D_00F21380, 1, 20000);
    PlatVu0CopyVector(*o->obj, o->pos);
    v = D_002E31B8;
    switch (v) {
    case 0:
        o->pair.a = 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        if (D_002E31B0.a != 0 && func_00122ff8(D_002E31B0.a)) {
            o->pair.a = D_002E31B0.a;
            o->pair.b = D_002E31B0.b;
        }
        break;
    }
    D_00F21390 = !D_00F21390;
    if (D_00F21390)
        o->eff = func_0014a4a8(D_00F21384, 0, func_001477e0(1));
    else
        o->eff = func_0014a4a8(D_00F21384, 0, func_001477e0(2));
    o->eff->flags.kind = 1;
    o->eff->flags.b23 = 1;
    o->eff->flags.b7 = 1;
    o->eff->f12 = 20.0f;
    o->eff->src = D_00F21380;
    PlatVu0CopyVector(o->eff->pos, o->pos);
    func_00148968(D_00F21388, D_00F21380, 0);
    D_00304B7C -= D_00304B70->b2;
}
