/* session 7 w2: pppKeThDraw (0x18c3f8). The mode switch assigns both t1 and t2 in every case (no shared defaults), which stops jump.c hoisting t1 = 66. */
#include "common.h"
#include "ppp.h"

#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))

typedef struct {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[4];
    f32 f2C;
} ThSub;

typedef struct {
    u8 pad0[0x10];
    ThSub s;          /* +0x10 */
    u8 pad[0x6C - 0x10 - sizeof(ThSub)];
    s32 f6C;
    u64 c[4];         /* +0x70 */
} ThWork;

typedef struct {
    u8 pad[0x54];
    u8 mode;
} ThKey;

typedef struct { f32 x, y; } ThV2;
#include "data/pieces/D_003701F0.h"
extern u8 D_00616080[];
extern u8 D_00616224[];

void func_001a8d78(ThWork *);
void func_001a8c40(ThWork *, void *, f32 *, ThSub *, void *, u64, u64);

void pppKeThDraw(void *obj, ThKey *k, PppEntry *e) {
    f32 v[2];
    ThWork *w;
    u64 t1;
    u64 t2;
    u8 m;
    w = PPP_WORK(ThWork, obj, e, 0);
    v[0] = D_003701F0[0];
    v[1] = D_003701F0[1];
    m = k->mode;
    switch (m) {
    case 0: t1 = 72; t2 = 0x51801; break;
    case 1: t1 = 66; t2 = 0x51801; break;
    default: t2 = 0x70000; t1 = 0x80000000a8ULL; break;
    }

    func_001a8c40(w, D_00616080, v, &w->s, D_00616224, t1, t2);
}

#include "data/bss_0061_mixed.h"
