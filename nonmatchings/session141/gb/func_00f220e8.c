/* 4 words / score 7: only the 5-word struct copy at the top is scheduled differently (target loads +4 and +12 before storing +0). Tried all 120 field orders, *d = *src (gives ldl/sdl), f32 fields. GIF tag constants need the ad/tag locals and the mode read before the third tag. */
#include "ovl.h"

typedef struct {
    u64 *p;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 pad;
} GbDraw;
typedef struct {
    u8 pad0[0x10];
    GbDraw draws[1];
} GbStateDraws;
typedef struct {
    u8 pad0[0x10];
    GbDraw draws[4];
    u8 pad70[0x76 - 0x70];
    s16 mode;
    u8 pad78[0x8C - 0x78];
    s32 cur;
} GbState;
extern GbState *D_00F56DC0;
extern u8 D_00F60C00[];
void func_00f3fe80(s32, void *);
void func_00f3c168(GbDraw *);
u64 *func_00f3f9d0(u64 *);
u64 *func_00f3f9e8(u64 *);
u64 *func_00f3fa80(u64 *);
void func_00f3fa98(u64 *);

GbDraw *func_00f220e8(GbDraw *d) {
    GbDraw *src;
    u64 *q;
    s32 mode;
    u64 ad = 0x18;
    u64 tag = 0x740000007000;
    src = &D_00F56DC0->draws[D_00F56DC0->cur];
    func_00f3fe80(10000, D_00F60C00);
    d->b = src->b;
    d->c = src->c;
    d->a = src->a;
    d->d = src->d;
    d->p = src->p;
    func_00f3c168(d);
    q = func_00f3fa80(func_00f3f9d0(d->p));
    q[0] = tag;
    q[1] = ad;
    q += 2;
    q[0] = 0x30000;
    q[1] = 0x47;
    q += 2;
    func_00f3fa98(q);
    func_00f3fe80(10000, func_00f3f9e8(q));
    q = func_00f3fa80(func_00f3f9d0(q));
    q[0] = tag;
    q[1] = ad;
    q += 2;
    q[0] = 0x5000D;
    q[1] = 0x47;
    q += 2;
    q[0] = 0x44;
    q[1] = 0x42;
    q += 2;
    func_00f3fa98(q);
    func_00f3fe80(11840, func_00f3f9e8(q));
    q = func_00f3fa80(func_00f3f9d0(q));
    mode = D_00F56DC0->mode;
    q[0] = tag;
    q[1] = ad;
    q += 2;
    if (mode != 2) {
        q[0] = 0x30003;
        q[1] = 0x47;
        q += 2;
        q[0] = 0x46;
        q[1] = 0;
        q += 2;
        q[0] = 0x3F80000000000000;
        q[1] = 1;
        q += 2;
        q[0] = 0x74007000;
        q[1] = 5;
        q += 2;
        q[0] = 0x8C009000;
        q[1] = 5;
        q += 2;
    }
    q[0] = 0x5000D;
    q[1] = 0x47;
    q += 2;
    func_00f3fa98(q);
    func_00f3fe80(12560, func_00f3f9e8(q));
    d->p = q;
    return src;
}
